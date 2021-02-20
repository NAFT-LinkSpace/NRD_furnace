#include "PID.hpp"

// MV:操作量
//
VelocityPID::VelocityPID() {
    init();
}
void VelocityPID::init() {
    Kp_ = Ti_ = Td_ = 0.0;
    pre_time_ms = 0.0;
    error_n_1 = error_n_2 = 0.0;
    pre_MV = 0.0;
    pre_deltaMV_d = 0.0;
}
void VelocityPID::setGain(double Kp, double Ki, double Kd) {
    Kp_ = Kp;
    Ti_ = Kp / Ki;
    Td_ = Kd / Kp;
}

double VelocityPID::output(const double error, const unsigned long now_ms) {
    double dt = (now_ms - pre_time_ms) / 1e3;

    double deltaMV_d = Td_ / (ita_cutoff * Td_ + dt) * (ita_cutoff * pre_deltaMV_d + error - 2 * error_n_1 + error_n_2);
    double MV = Kp_ * (error - error_n_1 + dt / Ti_ * error + deltaMV_d) + pre_MV;

    // update vals
    pre_time_ms = now_ms;
    error_n_2 = error_n_1;
    error_n_1 = error;
    pre_deltaMV_d = deltaMV_d;
    pre_MV = MV;

    return MV;
}