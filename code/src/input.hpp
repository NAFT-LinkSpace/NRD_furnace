#if !defined(INPUT_HEADER_FILE)
#define INPUT_HEADER_FILE

#include "container.hpp"
#include "serial.hpp"
#include "temperature.hpp"

void inputBegin();
const InputContainer& input();

#endif  // INPUT_HEADER_FILE
