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

    bool parsable;
    void init() {
        operand_size = 0;
        parsable = false;
        for (unsigned int i = 0; i < max_operand_size; i++) {
            operand[i] = 0.0;
        }
    }
    String toString() {
        String s = "parseResult:";
        s += operator_ + " ";
        for (unsigned int i = 0; i < max_operand_size; i++) {
            s += String(operand[i]) + " ";
        }
        s += "oprandsize " + String(operand_size);
        return s;
    }
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
        parse_result.init();
    }

    // return operator ,operand as parameter
    const ParseResult<OPEAND_BUF_SIZE>& parse(const String src) {
        clearBuffer();
        Serial.println("src" + src);
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

   private:
    void clearBuffer() {
        parse_result.init();
        for (unsigned int i = 0; i < str_buf_size; i++) {
            str_buf[i] = "";
        }
    }
};
// return operator ,operand

// if succeed return true,if not ()
int split(const String src, String* dst, const int dstsize, const char delim);
bool strToDoubleError(const String, double&);

#endif  // PARSE_HEADER_FILE
