// custumize file
#if !defined(CONTROL_PARAMETER)
#define CONTROL_PARAMETER

const double MAX_OUTPUT_ENERGY_W = 200;  //[J/s]
const unsigned long PWM_PERIOD_ms = 100;

double feedbackTemperature(const double T0, const double T1, const double T2);
// PID gain
const double Kp = 0.0;
const double Ki = 0.0;
const double Kd = 0.0;

struct inflectionPoint {
    double time;
    double temp;
};

static constexpr inflectionPoint inflectionpoint_s[] = {{0, 80}, {0, 80}, {0, 80}, {0, 80}, {0, 0}, {0, 0}};

double targetFunction(const unsigned long elapsed_time_ms, bool& is_end);

#endif  // CONTROL_PARAMETER
