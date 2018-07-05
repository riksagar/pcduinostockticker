#include "Pin.h"

class ArduinoPin: public Pin {
public:
    ArduinoPin(int pin);
    
    void setup(Pin::Mode mode);
    void digitalWrite(Pin::State state);
    Pin::State digitalRead();
private:
    int pin;
};
