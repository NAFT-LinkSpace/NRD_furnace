#include "convert.hpp"

static Parser<10> parser(' ');
static OutputContainer out;

// context
static Control control;
static ConstPWM constpwm;

static State& state = constpwm;

template <int N>
void changeState(const ParseResult<N>& parsed) {
    if (parsed.operator_ == keyword::SET_DUTY) {
        if (parsed.operand_size == 1) {
            out.duty_per = parsed.operand[0];
        } else {
            return;
        }

        state = constpwm;

    } else if (parsed.operator_ == keyword::START_CONTROL) {
        // out.control_on = true;
        if (parsed.operand_size == 0) {
            out.skip_time_s = 0.0;

        } else if (parsed.operand_size == 1) {
            out.skip_time_s = parsed.operand[0];

        } else if (parsed.operand_size == 2) {
            out.skip_time_s = parsed.operand[0];
            // out.target_temp = parsed.operand[1];
        } else {
            return;
        }

        state = control;
    }
}

// client
void convert(const InputContainer& input) {
    out.update(input.common_);

    auto parsed = parser.parse(input.message);

    if (parsed.parsable) {
        changeState(parsed);
    }
    Serial.print(input.toString());
    Serial.print(out.toString());
    Serial.println(out.common_.toString());

    state.output(out);
}