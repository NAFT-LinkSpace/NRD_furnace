#include "parse.hpp"

// if succeed return true,if not ()
// return size of assigned to dst
int split(const String src, String* dst, const int dstsize, const char delim) {
    int array_ind, char_ind;
    array_ind = char_ind = 0;

    const int srclen = src.length();
    for (; char_ind < srclen; char_ind++) {
        if (src[char_ind] == delim) {
            array_ind++;
        } else {
            if (array_ind < dstsize) {
                dst[array_ind] += src[char_ind];
            }
        }
    }
    return array_ind + 1;
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