#ifndef TEMPERATURE_HEDDER_FILE
#define TEMPERATURE_HEDDER_FILE

#include <SPI.h>

#include "Adafruit_MAX31855.h"
#include "pin.hpp"

class Temperature {
   private:
    Adafruit_MAX31855 themocouple0;
    Adafruit_MAX31855 themocouple1;
    Adafruit_MAX31855 themocouple2;

   public:
    double T0, T1, T2;

    Temperature();
    void begin();
    void update();
    String toString(const String delim = ",");
};

#endif