#if !defined(STATE_HEADER_FILE)
#define STATE_HEADER_FILE

#include "PID.hpp"
#include "Stringer.hpp"
#include "container.hpp"
#include "control_parameter.hpp"
#include "pincontrol.hpp"
#include "serial.hpp"

class State {
   public:
    State() {
        pinControlBegin();
    }

    virtual void output(const OutputContainer& out) {
        return;
    }
    virtual const String toString() const {
        return toStringHelper("State", "default");
    }
};

class Control : public State {
    // ControlTemperature controller;
    // static Control control;
    VelocityPID vpid;
    bool is_control_finished = false;
    // double targetTemp;
    // unsigned long control_start_ms_;

   public:
    Control() {
        is_control_finished = false;
        vpid.init();
        vpid.setGain(Kp, Ki, Kd);
    }

    void output(const OutputContainer& out) override {
        const double d = duty(out.common_.now_ms, out.skip_time_s, out.common_.current_tempT0, out.common_.current_tempT1, out.common_.current_tempT2);
        setLongPeriodPWM(d, PWM_PERIOD_ms, out.common_.now_ms);
    }
    const String toString() const override {
        return toStringHelper("State", "Control");
    }

   private:
    double duty(const unsigned long now_ms, const double skip_time_s, const double T0, const double T1, const double T2) {
        const double target_temp = targetFunction(now_ms - static_cast<unsigned long>(skip_time_s / 1e3), is_control_finished);
        if (is_control_finished) {
            Serial.print("end control");
            return 0.0;
        }
        const double out_W = vpid.output(target_temp - (feedbackTemperature(T0, T1, T2)), now_ms);
        const double duty_per = out_W / MAX_OUTPUT_ENERGY_W * 100;

        Serial.println("out_W" + String(out_W));
        Serial.println("duty" + String(duty_per));
        return duty_per;
    }
};

class ConstPWM : public State {
   public:
    void output(const OutputContainer& out) override {
        setLongPeriodPWM(out.duty_per, PWM_PERIOD_ms, out.common_.now_ms);
    }
    const String toString() const override {
        return toStringHelper("State", "ConstPWM");
    }
};
#endif  // STATE_HEADER_FILE
