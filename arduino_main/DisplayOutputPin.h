#ifndef __DISPLAYOUTPUTPIN_H
#define __DISPLAYOUTPUTPIN_H

#include "Pin.h"

class DisplayOutputPin {

	public:
		DisplayOutputPin(unsigned long int const *dataword, unsigned short int mask, unsigned short int span, unsigned short int maxpos);
		~DisplayOutputPin();

		void resetPosition();
		bool incPosition();
		void setDataWord(unsigned long int const *dataword);
		unsigned short int getPosition();

		bool getCurrent();

		virtual void evaluate() = 0;
		virtual void set(Pin::State) = 0;


	private:
		unsigned long int const *data;
		unsigned short int pixelMask;
		unsigned short int pixelSpan;
		unsigned short int maxPosition;
		unsigned short int position;
		unsigned long int posPixelMask;
};



#endif //ndef __DISPLAYOUTPUTPIN_H
