#if !defined(PARSE_HEADER_FILE)
#define PARSE_HEADER_FILE

#include <Arduino.h>

#include "keyword.hpp"

template <int OPERAND_BUF_SIZE>
struct ParseResult {
    String operator_;
    unsigned int operand_size;
    const unsigned int max_operand_size = OPERAND_BUF_SIZE;
    double operand[OPERAND_BUF_SIZE];

    bool parsable = false;
};

template <int OPEAND_BUF_SIZE>
class Parser {
   private:
    static const unsigned int str_buf_size = OPEAND_BUF_SIZE + 1;
    String str_buf[str_buf_size];
    ParseResult<OPEAND_BUF_SIZE> parse_result;
    char delim_;

   public:
    explicit Parser(const char delim) {
        delim_ = delim;
    }

    // return operator ,operand as parameter
    const ParseResult<OPEAND_BUF_SIZE>& parse(const String src) {
        // parse(const String src, String& operator_, double* operand, const int operand_bufsize) {

        unsigned int buf_assined_size = split(src, str_buf, str_buf_size, delim_);

        // check assigned size
        if (buf_assined_size > str_buf_size ||
            buf_assined_size > parse_result.max_operand_size + 1 ||
            buf_assined_size == 0) {
            parse_result.operator_ = "";
            parse_result.parsable = false;

            return parse_result;
        }
        parse_result.operator_ = str_buf[0];
        parse_result.operand_size = buf_assined_size - 1;
        for (unsigned int i = 0; i < parse_result.operand_size; i++) {
            if (!strToDoubleError(str_buf[i + 1], parse_result.operand[i])) {
                parse_result.parsable = false;
                return parse_result;
            }
        }

        parse_result.parsable = true;
        return parse_result;
    }
};
// return operator ,operand

// if succeed return true,if not ()
int split(const String src, String* dst, const int dstsize, const char delim);
bool strToDoubleError(const String, double&);

#endif  // PARSE_HEADER_FILE
