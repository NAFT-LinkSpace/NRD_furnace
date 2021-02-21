#if !defined(CONVERT_HEADER_FILE)
#define CONVERT_HEADER_FILE

#include "container.hpp"
#include "keyword.hpp"
#include "parse.hpp"
#include "state.hpp"



// client
class Context {
   private:
    Parser<10> parser_;
    OutputContainer out_;

    Control control_;
    ConstPWM constpwm_;

    State* state_;

    void changeState(State& state) {
        state_ = &state;
    }

   public:
    Context() : parser_(' ')
    // , state_(constpwm_)
    {
        // state_ = &control_;
        changeState(constpwm_);
    }

    void update(const InputContainer& input) {
        out_.update(input);
        auto parsed = parser_.parse(input.message);
        Serial.println(toStringHelper("parsed", parsed.toString()));

        if (!parsed.parsable) {
            Serial.println("not parsable");
            return;
        }

        if (parsed.operator_ == keyword::SET_DUTY) {
            if (parsed.operand_size == 1) {
                out_.duty_per = parsed.operand[0];

            } else {
                return;
            }
            changeState(constpwm_);

        } else if (parsed.operator_ == keyword::START_CONTROL) {
            // out.control_on = true;
            if (parsed.operand_size == 0) {
                out_.skip_time_s = 0.0;

            } else if (parsed.operand_size == 1) {
                out_.skip_time_s = parsed.operand[0];

            } else if (parsed.operand_size == 2) {
                out_.skip_time_s = parsed.operand[0];
                // out.target_temp = parsed.operand[1];
            } else {
                Serial.println("not parsable");
                return;
            }
            out_.duty_per = 0.0;
            changeState(control_);
        }
    }
    void useState() {
        Serial.print(out_.common_.toString());
        // Serial.print(state_.toString());
        Serial.print(state_->toString());

        // Serial.print(input.toString());
        Serial.print(out_.toString());

        // state_.output(out_);
        state_->output(out_);
    }
};
void convert(const InputContainer& input);

#endif  // CONVERT_HEADER_FILE
