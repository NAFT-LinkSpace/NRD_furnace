#ifndef TEMPERATURE_HEDDER_FILE
#define TEMPERATURE_HEDDER_FILE

#include <SPI.h>

#include "Adafruit_MAX31855.h"
#include "pin.hpp"

class Temperature {
   private:
    Adafruit_MAX31855 themocouple0;
    Adafruit_MAX31855 themocouple1;

    // Adafruit_MAX31855 themocouple0(CLK, CS0, DO);
    // Adafruit_MAX31855 themocouple1(CLK, CS1, DO);

   public:
    double T1, T2;

    Temperature();

    void update();
    String toString();
};

#endif