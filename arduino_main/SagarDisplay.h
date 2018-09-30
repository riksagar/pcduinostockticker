#ifndef __SAGARDISPLAY_H
#define __SAGARDISPLAY_H

#include "SagarDisplayControlFileReader.h"
#include "Pin.h"
#include "DisplayOutputPin.h"
#include "SdffParser.h"

class SagarDisplay {
public:
	static bool setup();
        static bool loadFromFile(char *filename);

	static void loop();


private:
	SagarDisplay(){}

        static bool load(sdff::Stream *);
        static int row;
        static DisplayOutputPin **pixelPins;
        static bool displayOK;
        static Pin *clockPin;
        static const unsigned long clockDurationHighMicros;
        static const unsigned long clockDurationLowMicros;
        static const int resetDurationMillis;
};

#endif //ndef __SAGARDISPLAY_H
