#ifndef __SAGARDISPLAY_H
#define __SAGARDISPLAY_H

#include "SagarDisplayControlFileReader.h"
#include "Pin.h"
#include "DisplayOutputPin.h"

class SagarDisplay {
public:
	static bool setup();
	static void loop();


private:
	SagarDisplay(){}
	static SDCReader *data;
  static int row;
  static DisplayOutputPin **pixelPins;
  static bool displayOK;
  static Pin *clockPin;
  static const unsigned long clockDurationHighMicros;
  static const unsigned long clockDurationLowMicros;
  static const int resetDurationMillis;
  

                

 
};

#endif //ndef __SAGARDISPLAY_H
