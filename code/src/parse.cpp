#include "parse.hpp"

// template <int BUF_SIZE>
// Parser<BUF_SIZE>::Parser(const char delim) {
//     delim_ = delim;
// }

// return operator ,operand as parameter
// template <int bufsize>
// bool Parser<bufsize>::parse(const String src, String& operator_, double* operand, const int operand_bufsize) {
//     int buf_assined_size = split(src, buf, bufsize, delim_);
//     if (buf_assined_size > bufsize || buf_assined_size > operand_bufsize + 1) {
//         operator_ = "";
//         return false;
//     }
//     operator_ = buf[0];

//     for (int i = 0; i < operand_size && i + 1 < buf_assined_size; i++) {
//         if (!strTodError(buf[i + 1], operand[i])) {
//             return false;
//         }
//     }
//     return true;
// }
// if succeed return true,if not ()
// return size of assigned to dst
int split(const String src, String* dst, const int dstsize, const char delim) {
    int i, j = 0;

    const int srclen = src.length();
    for (; j < srclen; j++) {
        if (src[j] == delim) {
            i++;
        } else {
            if (i < dstsize) {
                dst[i] += src[j];
            }
        }
    }
    return i;
}
bool strToDoubleError(const String s, double& d) {
    char* tmperr;
    double tmp = strtod(s.c_str(), &tmperr);
    if (*tmperr == '\0') {
        d = tmp;
        return true;
    }

    return false;
}