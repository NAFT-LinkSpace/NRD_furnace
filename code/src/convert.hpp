#if !defined(CONVERT_HEADER_FILE)
#define CONVERT_HEADER_FILE

#include "container.hpp"
#include "keyword.hpp"
#include "parse.hpp"
#include "state.hpp"

template <int N>
void changeState(const ParseResult<N>& parsed);

// client
void convert(const InputContainer& input);

#endif  // CONVERT_HEADER_FILE
