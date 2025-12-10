#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <utility>

struct Waypoint { double x, y; };
struct Pose2D { double x, y, yaw; };
struct Command { double steering_rad; double target_speed; bool reached_goal; };

class PurePursuit {
public:
  // wheelbase in meters
  PurePursuit(double wheelbase);

  void setPath(std::vector<Waypoint> path);

  void setLookaheadGains(double Ld_min, double Ld_max, double k);

  Command update(const Pose2D& pose, double speed);

  void setNominalSpeed(double v);
  void setGoalTolerance(double tol);

private:
  size_t findClosestIndex(const Pose2D& p, size_t hint) const;
  int advanceToLookahead(size_t i, const Pose2D& p, double Ld) const;

  double L_, Ld_min_{1.0}, Ld_max_{4.0}, k_{0.4}, nominal_speed_{3.0}, goal_tol_{0.5};
  std::vector<Waypoint> path_;
  mutable size_t idx_hint_{0};
};
