#include "Pin.h"

class AbstractPin: public Pin {
public:
    AbstractPin();
    void setup(Pin::Mode mode);
    void digitalWrite(Pin::State value);
    Pin::State digitalRead();

private:
    int pin;
};