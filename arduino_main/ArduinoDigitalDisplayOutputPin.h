#ifndef __ARDDISPLAYOUTPUTPUT_H
#define __ARDDISPLAYOUTPUTPUT_H


#include "DisplayOutputPin.h"

class ArduinoDop: public DisplayOutputPin {
public:
	ArduinoDop(unsigned long int const *dataword, unsigned short int mask, unsigned short int span, unsigned short int maxpos, int lowVal, int highVal, int pin);
	~ArduinoDop();

	virtual void evaluate();
	virtual void set(Pin::State);

private:
	int lo;
	int hi;
	int pin;
};


#endif //ndef __ARDDISPLAYOUTPUTPUT_H
