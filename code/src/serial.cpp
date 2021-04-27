#include "serial.hpp"

void setupSerial(const unsigned long baud) {
    Serial.begin(baud);
}

// SerialからStringもらう
String readSerial() {
        if (Serial.available() == 0) {
        return "";
    }

    String str = Serial.readString();
    rmCRLF(str);

    Serial.flush();
    return str;
}

void rmCRLF(String& s) {
    if (s.endsWith("\n")) {
        s = s.substring(0, s.length() - 1);
    }
    if (s.endsWith("\r")) {
        s = s.substring(0, s.length() - 1);
    }
}
