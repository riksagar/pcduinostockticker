#include <stdio.h>
#include <Arduino.h>

#include "ArduinoDigitalDisplayOutputPin.h"

/*
int ArduinoDop::pin;
int ArduinoDop::hi;
int ArduinoDop::lo;
*/
ArduinoDop::ArduinoDop(unsigned long int const *dataword, unsigned short int mask, unsigned short int span, unsigned short int maxpos, int lowVal, int highVal, int digitalPin)
	:DisplayOutputPin(dataword,mask,span,maxpos)
	,lo(lowVal)
	,hi(highVal)
	,pin(digitalPin)
{
	pinMode(digitalPin, OUTPUT);
}


void ArduinoDop::evaluate(){
	bool current = getCurrent();

	int out = current?hi:lo;
	digitalWrite(pin, out);
}

void ArduinoDop::set(Pin::State state){
	digitalWrite(pin, (Pin::high == state)?hi:lo);
}

