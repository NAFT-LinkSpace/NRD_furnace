// custumize file
#if !defined(CONTROL_PARAMETER)
#define CONTROL_PARAMETER

constexpr double MAX_OUTPUT_ENERGY_W = 200;  //[J/s]
constexpr unsigned long PWM_PERIOD_ms = 300;

// PID gain
// constexpr double Kp = 0.336;
// constexpr double Ki = 0.000171;
// constexpr double Kd = 6.72;

constexpr double Kp = 34;
constexpr double Ki = 0.017;
constexpr double Kd = 684;

struct inflectionPoint {
    double time_s;
    double temp_cels;
};

static constexpr inflectionPoint inflectionpoint_s[] = {{0, 20}, {20 * 60, 40}, {30 * 60, 40}, {50 * 60, 20}};
// static constexpr inflectionPoint inflectionpoint_s[] = {{0, 20}, {20 * 2, 40}, {30 * 2, 40}, {50 * 2, 20}};

// , {0, 80}, {0, 80}, {0, 0}, {0, 0}};
inline double linear(const inflectionPoint t1, const inflectionPoint t2, const double etime_s) {
    return (t2.temp_cels - t1.temp_cels) / (t2.time_s - t1.time_s) * (etime_s - t1.time_s) + t1.temp_cels;
}

inline double targetFunction(const double elapsed_time_s, bool& is_end) {
    is_end = false;
    if (elapsed_time_s < inflectionpoint_s[0].time_s) {
        return 0;
    }
    if (elapsed_time_s < inflectionpoint_s[1].time_s) {
        // return inflectionpoint_s[1].temp_cels;
        return linear(inflectionpoint_s[0], inflectionpoint_s[1], elapsed_time_s);
    }
    if (elapsed_time_s < inflectionpoint_s[2].time_s) {
        return linear(inflectionpoint_s[1], inflectionpoint_s[2], elapsed_time_s);
    }
    if (elapsed_time_s < inflectionpoint_s[3].time_s) {
        return linear(inflectionpoint_s[2], inflectionpoint_s[3], elapsed_time_s);
    }
    // if (elapsed_time_s < inflectionpoint_s[4].time_s) {
    //     return (inflectionpoint_s[4].temp_cels - inflectionpoint_s[3].temp_cels) / (inflectionpoint_s[4].time_s - inflectionpoint_s[3].time_s) + inflectionpoint_s[4].temp_cels;
    // }
    // if (elapsed_time_s < inflectionpoint_s[5].time_s) {
    //     return inflectionpoint_s[5].temp_cels;
    // }
    is_end = true;
    return 0.0;
}

// test PID control
inline double feedbackTemperature(const double T0, const double T1, const double T2, const double elasped_time_s) {
    bool b;
    return targetFunction(elasped_time_s, b) - 1.0;
}

//inline double feedbackTemperature(const double T0, const double T1, const double T2, const double elasped_time_s) {
//     return T0;
// }
#endif  // CONTROL_PARAMETER
