#if !defined(STRINGER_HEADER_FILE)
#define STRINGER_HEADER_FILE
#include <Arduino.h>

// const String toStringHelper(const String tag, const target variabel) ;

template <typename T>
const String toStringHelper(const String tag, const T t) {
    return tag + ":" + String(t) + ", ";
}

template <typename T>
const String toStringHelper(const String tag, const T* t, const unsigned int array_size) {
    String s = tag + "{";
    for (unsigned int i = 0; i < array_size; i++) {
        s += toStringHelper(String(i), t[i]);
    }
    s += "},";
    return s;
}

inline const String toStringHelper(const String tag, const String& ss) {
    return tag + ":" + ss + ",";
}

#endif  // STRINGER_HEADER_FILE
