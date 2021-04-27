#if !defined(STATE_HEADER_FILE)
#define STATE_HEADER_FILE

#include "PID.hpp"
#include "Stringer.hpp"
#include "container.hpp"
#include "control_parameter.hpp"
#include "pincontrol.hpp"
#include "queue.hpp"
#include "serial.hpp"

class State {
   public:
    State() {
        pinControlBegin();
    }

    virtual void setOutput(const CommonContainer common) = 0;
    virtual const String toString() const = 0;
};

class Control : public State {
   private:
    VelocityPID pid;
    bool is_control_finished = false;
    unsigned long control_start_ms_;
    double skip_time_s_;

   public:
    Control() {
        is_control_finished = false;
        skip_time_s_ = 0.0;
        pid.init();
        pid.setGain(Kp, Ki, Kd);
    }

    void setOutput(const CommonContainer common) override {
        normal_queue.push(toString());

        const double duty_per = dutyPer(common.now_ms, common.current_tempT0, common.current_tempT1, common.current_tempT2);

        normal_queue.push(is_control_finished ? "control is end" : "");
        setLongPeriodPWM(duty_per, PWM_PERIOD_ms, common.now_ms);
    }

    const String toString() const override {
        return toStringHelper("State", "Control");
    }

    void startControl(const unsigned long start_ms, const double skip_time_s) {
        pid.init();
        is_control_finished = false;
        control_start_ms_ = start_ms;
        skip_time_s_ = skip_time_s;
    }

   private:
    const double dutyPer(const unsigned long now_ms, const double T0, const double T1, const double T2) {
        const double elasped_time_s = (now_ms - control_start_ms_) / 1e3 + skip_time_s_;
        const double target_temp = targetFunction(elasped_time_s, is_control_finished);

        if (is_control_finished) {
            return 0.0;
        }
        const double error = target_temp - feedbackTemperature(T0, T1, T2, elasped_time_s);  //error:target - current
        const double out_W = constrain(pid.output(error, elasped_time_s), 0.0, MAX_OUTPUT_ENERGY_W);

        pid.setPreMV(out_W);
        const double duty_per = constrain(out_W / MAX_OUTPUT_ENERGY_W * 100, 0, 100);

        normal_queue.push(
            toStringHelper("elasped[s]", elasped_time_s) +
            toStringHelper("e(t)", error) +
            toStringHelper("target[Cels]", target_temp) +
            toStringHelper("heat out[W]", out_W));

        return duty_per;
    }
};

class ConstPWM : public State {
   private:
    double duty_per_;

   public:
    ConstPWM() {
        duty_per_ = 0.0;
    }
    void setOutput(const CommonContainer common) override {
        setLongPeriodPWM(duty_per_, PWM_PERIOD_ms, common.now_ms);
    }
    void setDuty(const double duty_per) {
        duty_per_ = constrain(duty_per, 0, 100);
    }
    const String toString() const override {
        return toStringHelper("State", "ConstPWM");
    }
};
#endif  // STATE_HEADER_FILE
