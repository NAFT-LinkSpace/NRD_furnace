#ifndef PID_HEADER_FILE
#define PID_HEADER_FILE

// https://www.nikko-pb.co.jp/products/k_data/P12_13.pdf
// 速度型PID制御
// 不完全微分
// velocity type PID
// inexact differential
class VelocityPID {
   public:
    VelocityPID() {
        init();
    }

    void init() {
        Kp_ = Ti_ = Td_ = 0.0;
        error_n_1 = error_n_2 = 0.0;
        pre_MV = 0.0;
        pre_deltaMV_d = 0.0;
    }

    void setGain(double Kp, double Ki, double Kd) {
        Kp_ = Kp;
        Ti_ = Kp / Ki;
        Td_ = Kd / Kp;
    }
    // MV:操作量
    double output(const double error, const double elasped_time_s) {
        double dt = elasped_time_s;

        double deltaMV_d = Td_ / (ita_cutoff * Td_ + dt) * (ita_cutoff * pre_deltaMV_d + error - 2 * error_n_1 + error_n_2);
        double MV = pre_MV + Kp_ * (error - error_n_1 + dt / Ti_ * error + deltaMV_d);

        // update vals

        error_n_2 = error_n_1;
        error_n_1 = error;
        pre_deltaMV_d = deltaMV_d;
        pre_MV = MV;

        return MV;
    }

   private:
    double Kp_, Ti_, Td_;

    const double ita_cutoff = 0.125;
    double error_n_1, error_n_2;
    double pre_deltaMV_d;
    double pre_MV;
};
#endif