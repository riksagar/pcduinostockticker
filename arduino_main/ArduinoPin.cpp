

#include <Arduino.h>

#include "ArduinoPin.h"

ArduinoPin::ArduinoPin(int p)
    :Pin()  
    ,pin(p)
{

}

void ArduinoPin::setup(Pin::Mode mode){
    int m = (Pin::output == mode)?OUTPUT:INPUT;
    pinMode(pin, m);
}

void ArduinoPin::digitalWrite(Pin::State state) {
    int value = (Pin::low == state)?LOW:HIGH;
    ::digitalWrite(pin, value);
}
Pin::State ArduinoPin::digitalRead() {
    int value = ::digitalRead(pin);
    return (1 == value)?Pin::high:Pin::low;
}
