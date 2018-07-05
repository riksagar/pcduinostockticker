#define ARDUINO



#if defined(ARDUINO)
	#include "ArduinoDigitalDisplayOutputPin.h"
#else
	#include "ConsoleDisplayOutputPin.h"
#endif

#include "DisplayOutputPinFactory.h"

DisplayOutputPinFactory::DisplayOutputPinFactory(){

}

DisplayOutputPin *DisplayOutputPinFactory::getInstance(unsigned long int const *dataword, unsigned short int mask, unsigned short int span, unsigned short int maxpos, int lowVal, int highVal, int pin){
	#if defined(ARDUINO)
	return new ArduinoDop(dataword, mask, span, maxpos, lowVal, highVal, pin);
	#else
	return new ConsoleDop(dataword, mask, span, maxpos, lowVal, highVal);
	#endif
}

