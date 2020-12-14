#include "serial.hpp"

const int buflen = 5;

void setupSerial(const unsigned long baud) {
    Serial.begin(baud);
}
void readSerial(Container& con) {
    readSerialhelper(con);
    Serial.flush();

    // return con;
}
void readSerialhelper(Container& con) {
    String buf[buflen];

    if (Serial.available() == 0) {
        return;
    }
    String str = Serial.readString();
    rmCRLF(str);

    int l = split(str, str.length(), buf, buflen);

    // Serial.println("arrived:" + str);  //
    // for (int i = 0; i < buflen; i++) {
    //     Serial.print(buf[i].length());
    //     Serial.println("buf[]" + buf[i]);
    // }
    if (l > buflen) {
        return;
    }

    if (buf[0] == keyword::SET_TEMP) {
        con.command = keyword::SET_TEMP;
        con.target_temp = strTodError(buf[1]);

    } else if (buf[0] == keyword::SET_DUTY) {
        con.command = keyword::SET_DUTY;
        con.duty = strTodError(buf[1]);

    } else if (buf[0] == keyword::READ_TEMP) {
        con.command = keyword::READ_TEMP;
    }
}
void writeSerial(const String str) {
    Serial.println(str);
}

void rmCRLF(String& s) {
    if (s.endsWith("\n")) {
        s = s.substring(0, s.length() - 1);
    }
    if (s.endsWith("\r")) {
        s = s.substring(0, s.length() - 1);
    }
}
double strTodError(const String s) {
    char* tmperr;
    double tmp = strtod(s.c_str(), &tmperr);
    if (*tmperr == '\0') {
        return tmp;
    }
    Serial.println("strtodError");

    return 0.0;
}

// return dst assigned length
int split(const String s, const int slen, String* dst, const int dstsize, const char delim) {
    int i = 0;
    int j = 0;

    for (; j < slen; j++) {
        if (s[j] == delim) {
            i++;
        } else {
            if (i < dstsize) {
                dst[i] += s[j];
            }
        }
    }
    return i;
}