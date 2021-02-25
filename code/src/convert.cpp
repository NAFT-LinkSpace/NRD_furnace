#include "convert.hpp"

static Context state_manager;
// client
void convert(const InputContainer& input) {
    state_manager.update(input);
}