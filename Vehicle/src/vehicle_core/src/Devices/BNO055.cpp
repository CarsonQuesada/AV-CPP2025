#include "vehicle_core/Devices/BNO055.hpp"

BNO055::BNO055(std::shared_ptr<I2CBus> bus, uint8_t addr)
: I2CDevice("BNO055")
{
  if (!open(bus, addr)) {
    throw std::runtime_error("Failed to open BNO055");
  }
}

// ---- Init sequence
bool BNO055::init_ndof(bool ext_xtal) {
  uint8_t v;
  uint8_t zero = 0x00;

  // 1) CONFIG mode
  if (!writeReg8(0x3D, &zero, 1)) return false; // OPR_MODE = CONFIG (0x00)
  usleep(20000);

  // 2) Normal power
  if (!writeReg8(0x3E, &zero, 1)) return false; // PWR_MODE = Normal (0x00)
  usleep(10000);

  // 3) SI units
  if (!writeReg8(0x3B, &zero, 1)) return false; // UNIT_SEL = 0x00 (SI)
  usleep(1000);

  // 4) External crystal (optional)
  if (ext_xtal) {
    if (!readReg8(0x3F, &v, 1)) return false;   // SYS_TRIGGER
    v |= 0x80;                                  // EXT_CRYSTAL
    if (!writeReg8(0x3F, &v, 1)) return false;
    usleep(10000);
  }

  // 5) Switch to NDOF fusion mode
  uint8_t ndof = 0x0C; // OPR_MODE = NDOF
  if (!writeReg8(0x3D, &ndof, 1)) return false;
  usleep(20000); // datasheet suggests >=7ms; 20ms is safe

  // (optional) verify mode latched
  if (!readReg8(0x3D, &v, 1)) return false;
  return (v == ndof);
}

// ---- Reads
bool BNO055::read_quat(double& w, double& x, double& y, double& z) {
  uint8_t buf[8];
  if (!readReg8(0x20, buf, 8)) return false;
  int16_t w_raw = int16_t(buf[0] | (buf[1] << 8));
  int16_t x_raw = int16_t(buf[2] | (buf[3] << 8));
  int16_t y_raw = int16_t(buf[4] | (buf[5] << 8));
  int16_t z_raw = int16_t(buf[6] | (buf[7] << 8));
  const double scale = 1.0 / 16384.0;
  w = w_raw * scale; x = x_raw * scale; y = y_raw * scale; z = z_raw * scale;
  // (optional) normalize
  const double n = std::sqrt(w*w + x*x + y*y + z*z);
  if (n > 1e-6) { w /= n; x /= n; y /= n; z /= n; }
  return true;
}

bool BNO055::read_gyro_rad_s(double& gx, double& gy, double& gz) {
  uint8_t b[6];
  if (!readReg8(0x14, b, 6)) return false;
  auto s16 = [&](int i){ return int16_t(b[i] | (b[i+1] << 8)); };
  auto conv = [&](int16_t r){ return (double(r) / 16.0) * (M_PI / 180.0); };
  gx = conv(s16(0));
  gy = conv(s16(2));
  gz = conv(s16(4));
  return true;
}

bool BNO055::read_lin_acc_ms2(double& ax, double& ay, double& az) {
  uint8_t b[6];
  if (!readReg8(0x28, b, 6)) return false;
  auto s16 = [&](int i){ return int16_t(b[i] | (b[i+1] << 8)); };
  ax = s16(0) * 9.80665e-3;
  ay = s16(2) * 9.80665e-3;
  az = s16(4) * 9.80665e-3;
  return true;
}

bool BNO055::read_mag_uT(double& mx, double& my, double& mz) {
  uint8_t b[6];
  if (!readReg8(0x0E, b, 6)) return false;
  auto s16 = [&](int i){ return int16_t(b[i] | (b[i+1] << 8)); };
  // default: 1 LSB = 1/16 µT
  mx = double(s16(0)) / 16.0;
  my = double(s16(2)) / 16.0;
  mz = double(s16(4)) / 16.0;
  return true;
}

// calibration (0..3 each)
bool BNO055::read_calib(uint8_t& sys, uint8_t& gyro, uint8_t& accel, uint8_t& mag) {
  uint8_t v = 0;
  if (!readReg8(0x35, &v, 1)) return false;
  sys   = (v >> 6) & 0x03;
  gyro  = (v >> 4) & 0x03;
  accel = (v >> 2) & 0x03;
  mag   = (v >> 0) & 0x03;
  return true;
}
