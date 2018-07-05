#include "Pin.h"

#define ARDUINO

#if defined(ARDUINO)
    #include "ArduinoPin.h"
    Pin *Pin::get(int pin){
        return new ArduinoPin(pin);
    }
#else
    #include "AbstractPin.h"
    Pin *Pin::get(int pin){
        return new AbstractPin();
    }
#endif

Pin::Pin(){
}
