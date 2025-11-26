#include "vehicle_core/Autopilot/PurePursuit.hpp"

PurePursuit::PurePursuit(double wheelbase) : L_(wheelbase) {}

void PurePursuit::setPath(std::vector<Waypoint> path) {
  path_ = std::move(path);
  idx_hint_ = 0;
}

void PurePursuit::setLookaheadGains(double Ld_min, double Ld_max, double k) {
  Ld_min_ = Ld_min;
  Ld_max_ = Ld_max;
  k_ = k;
}

Command PurePursuit::update(const Pose2D& pose, double speed) {
  Command cmd{0.0, nominal_speed_, false};
  if (path_.size() < 2) return cmd;

  const double Ld = std::clamp(Ld_min_ + k_ * speed, Ld_min_, Ld_max_);

  // 1) find closest segment / progress (linear scan with hint; use KD-tree if big)
  idx_hint_ = findClosestIndex(pose, idx_hint_);
  // 2) march forward along path until cumulative distance >= Ld
  int tgt_idx = advanceToLookahead(idx_hint_, pose, Ld);

  // 3) compute steering to that point
  const auto& wp = path_[tgt_idx];
  double dx = wp.x - pose.x, dy = wp.y - pose.y;
  // transform into vehicle frame
  double s = std::sin(pose.yaw), c = std::cos(pose.yaw);
  double x_v =  c*dx + s*dy;
  double y_v = -s*dx + c*dy;
  double alpha = std::atan2(y_v, x_v);

  const double kappa = 2.0 * std::sin(alpha) / std::max(Ld, 1e-3);
  cmd.steering_rad = std::atan(L_ * kappa);
  cmd.reached_goal = (tgt_idx >= (int)path_.size() - 1) && (std::hypot(dx,dy) < goal_tol_);
  return cmd;
}

void PurePursuit::setNominalSpeed(double v) { nominal_speed_ = v; }

void PurePursuit::setGoalTolerance(double tol) { goal_tol_ = tol; }

size_t PurePursuit::findClosestIndex(const Pose2D& p, size_t hint) const {
  size_t best = hint, n = path_.size();
  double best_d = 1e18;
  size_t start = (hint > 5) ? hint - 5 : 0;
  size_t stop  = std::min(n, hint + 50); // limited window
  for (size_t i = start; i < stop; ++i) {
    double d = std::hypot(path_[i].x - p.x, path_[i].y - p.y);
    if (d < best_d) { best_d = d; best = i; }
  }
  return best;
}

int PurePursuit::advanceToLookahead(size_t i, const Pose2D& p, double Ld) const {
  if (i >= path_.size()) return (int)path_.size() - 1;
  double dsum = 0.0;
  double lastx = p.x, lasty = p.y;
  for (size_t k = i; k < path_.size(); ++k) {
    dsum += std::hypot(path_[k].x - lastx, path_[k].y - lasty);
    if (dsum >= Ld) return (int)k;
    lastx = path_[k].x; lasty = path_[k].y;
  }
  return (int)path_.size() - 1;
}
