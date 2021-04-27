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
            error_queue.push(toStringHelper("not parsable", input.message));
            return;
        }

        if (parsed.operator_ == keyword::SET_DUTY) {
            if (parsed.operand_size == 1) {
                constpwm_.setDuty(parsed.operand[0]);

            } else {
                error_queue.push(toStringHelper("not parsable", input.message));
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
                error_queue.push(toStringHelper("not parsable", input.message));
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
        normal_queue.clear();
        error_queue.clear();
        prompt_queue.clear();

        normal_queue.filter(input.common_.now_ms % 1000 < 5);
        error_queue.filter(true);
        prompt_queue.filter(true);

        parseInput(input);
        state_->setOutput(input.common_);

        if (input.message.length() != 0) {
            Serial.println("\"" + input.message + "\"");
        }
        error_queue.println("ERROR");
        prompt_queue.println();
        normal_queue.println();
    }
};
void convert(const InputContainer& input);

#endif  // CONVERT_HEADER_FILE
