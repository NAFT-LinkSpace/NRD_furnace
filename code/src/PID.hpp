#ifndef PID_HEADER_FILE
#define PID_HEADER_FILE

// https://www.nikko-pb.co.jp/products/k_data/P12_13.pdf
// 速度型PID制御
// 不完全微分
// velocity type PID
// inexact differential
class VelocityPID {
   public:
    VelocityPID();
    void init();

    void setGain(double Kp, double Ki, double Kd);

    double output(const double error, const unsigned long now_ms);

   private:
    double Kp_, Ti_, Td_;

    const double ita_cutoff = 0.125;
    double pre_time_ms;
    double error_n_1, error_n_2;
    double pre_deltaMV_d;
    double pre_MV;
};
#endif