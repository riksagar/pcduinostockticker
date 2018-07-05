#ifndef __DISPLAY_OUTPUT_PIN_FACTORY_H
#define __DISPLAY_OUTPUT_PIN_FACTORY_H


#include "DisplayOutputPin.h"

class DisplayOutputPinFactory {
public:
	static DisplayOutputPin *getInstance(unsigned long int const *dataword, unsigned short int mask, unsigned short int span, unsigned short int maxpos, int lowVale, int highVal, int pin);


private:
	DisplayOutputPinFactory();
};


#endif //ndef __DISPLAY_OUTPUT_PIN_FACTORY_H
