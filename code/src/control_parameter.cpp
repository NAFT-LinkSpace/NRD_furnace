#include "control_parameter.hpp"
double feedbackTemperature(const double T0, const double T1, const double T2) {
    return T0;
}

double targetFunction(const unsigned long elapsed_time_ms, bool& is_end) {
    const double etime = double(elapsed_time_ms / 1e3);
    is_end = false;
    if (etime < inflectionpoint_s[0].time) {
        return inflectionpoint_s[0].temp / inflectionpoint_s[0].time * etime;
    }
    if (etime < inflectionpoint_s[1].time) {
        return inflectionpoint_s[1].temp;
    }
    if (etime < inflectionpoint_s[2].time) {
        return (inflectionpoint_s[2].temp - inflectionpoint_s[1].temp) / (inflectionpoint_s[2].time - inflectionpoint_s[1].time) + inflectionpoint_s[2].temp;
    }
    if (etime < inflectionpoint_s[3].time) {
        return inflectionpoint_s[3].temp;
    }
    if (etime < inflectionpoint_s[4].time) {
        return (inflectionpoint_s[4].temp - inflectionpoint_s[3].temp) / (inflectionpoint_s[4].time - inflectionpoint_s[3].time) + inflectionpoint_s[4].temp;
    }
    // if (etime < inflectionpoint_s[5].time) {
    //     return inflectionpoint_s[5].temp;
    // }
    is_end = true;
    return 0.0;
}