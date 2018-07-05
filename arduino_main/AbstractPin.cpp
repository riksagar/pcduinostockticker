
#include "AbstractPin.h"

AbstractPin::AbstractPin() {

}

void AbstractPin::setup(Pin::Mode mode){
}

void AbstractPin::digitalWrite(Pin::State value) {
    
}
Pin::State AbstractPin::digitalRead() {
    return Pin::low;
}
