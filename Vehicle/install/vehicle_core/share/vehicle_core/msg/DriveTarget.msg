# Percent 0..100 (clamped in arbiter)
uint8 brake_percent

# Signed linear speed in mm/s (negative -> reverse, zero -> coast/neutral)
int16 target_speed_mmps

# Signed steering in milliradians (-left, +right), clamped to steer.max_rad
int16 target_steer_millirad