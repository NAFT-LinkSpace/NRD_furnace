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

    void parseInput(const InputContainer& input) {
        if (input.message.length() == 0) {
            return;
        }
        auto parsed = parser_.parse(input.message);
        // out_.prompt += input.toString();

        if (!parsed.parsable) {
            out_.error += "not parsable";
            return;
        }

        if (parsed.operator_ == keyword::SET_DUTY) {
            if (parsed.operand_size == 1) {
                constpwm_.setDuty(parsed.operand[0]);

            } else {
                out_.error += "not parsable";
                return;
            }
            changeState(constpwm_);

        } else if (parsed.operator_ == keyword::START_CONTROL) {
            // out.control_on = true;
            if (parsed.operand_size == 0) {
                control_.startControl(input.common_.now_ms, 0.0);

            } else if (parsed.operand_size == 1) {
                control_.startControl(input.common_.now_ms, parsed.operand[0]);

            } else {
                out_.error += "not parsable";
                return;
            }

            changeState(control_);
        }
    }

   public:
    Context() : parser_(' ') {
        changeState(constpwm_);
    }
    void update(const InputContainer& input) {
        out_.init();
        parseInput(input);
        state_->setOutput(out_, input.common_);

        if (out_.error.length() != 0) {
            Serial.println(toStringHelper("error", out_.error));
        }
        if (input.message.length() != 0) {
            Serial.println(toStringHelper("message", "\"" + input.message + "\""));
        }
        if (input.common_.now_ms % 1000 < 5) {
            // Serial.print(input.toString());
            Serial.print(input.common_.toString());
            Serial.print(out_.message);

            Serial.println();
        }
    }
};
void convert(const InputContainer& input);

#endif  // CONVERT_HEADER_FILE
