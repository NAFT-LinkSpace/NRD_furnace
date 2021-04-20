// custumize file
#if !defined(CONTROL_PARAMETER)
#define CONTROL_PARAMETER

#include <Arduino.h>

constexpr double MAX_OUTPUT_ENERGY_W = 469.48;  //[J/s]
constexpr unsigned long PWM_PERIOD_ms = 300;

// PID gain

constexpr double Kp = 61.56308677317081;
constexpr double Ki = 0.030781543386585404;
constexpr double Kd = 1569.8587127158557;

struct inflectionPoint {
    double time_s;
    double temp_cels;
};

static constexpr inflectionPoint inflectionpoint_s[] = {{0, 20}, {30 * 60, 80}, {60 * 60, 80}, {82.5 * 60, 125}, {162.5 * 60, 125}};
static constexpr int inflectionPointSize = sizeof(inflectionpoint_s) / sizeof(inflectionPoint);

inline double linear(const inflectionPoint pre, const inflectionPoint next, const double etime_s) {
    return (next.temp_cels - pre.temp_cels) / (next.time_s - pre.time_s) * etime_s;
}

inline double targetFunction(const double elapsed_time_s, bool& is_end) {
    is_end = false;
    if (elapsed_time_s < inflectionpoint_s[0].time_s) {
        return 0.0;
    }
    for (int i = 1; i < inflectionPointSize; i++) {
        if (elapsed_time_s < inflectionpoint_s[i].time_s) {
            return linear(inflectionpoint_s[i - 1], inflectionpoint_s[i], elapsed_time_s);
        }
    }

    is_end = true;
    return 0.0;
}

// test PID control
// inline double feedbackTemperature(const double T0, const double T1, const double T2, const double elasped_time_s) {
//     bool b;
//     return targetFunction(elasped_time_s, b) - 1.0;
// }

inline double feedbackTemperature(const double T0, const double T1, const double T2, const double elasped_time_s) {
    return T1;
}
#endif  // CONTROL_PARAMETER
