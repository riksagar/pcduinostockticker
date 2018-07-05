#include <stdio.h>

#include "DisplayOutputPin.h"

/*
unsigned long int *DisplayOutputPin::data;
unsigned short int DisplayOutputPin::pixelMask;
unsigned short int DisplayOutputPin::maxPosition;
unsigned short int DisplayOutputPin::position;
unsigned long int DisplayOutputPin::posPixelMask;
*/
DisplayOutputPin::DisplayOutputPin(unsigned long int const *dataword, unsigned short int mask, unsigned short int span, unsigned short int maxpos)
	:data(dataword)
	,pixelMask(mask)
	,pixelSpan(span)
	,maxPosition(maxpos)
	,position(0)
	,posPixelMask(mask)
{

}


void DisplayOutputPin::resetPosition(){
	position = 0;
	posPixelMask = pixelMask;
}

bool DisplayOutputPin::incPosition(){
	if (position == maxPosition) return false;

	++position;
	posPixelMask <<= pixelSpan;

	return true;
}

void DisplayOutputPin::setDataWord(unsigned long int const *dataword){
	data = dataword;
}

unsigned short int DisplayOutputPin::getPosition(){
	return position;
}

bool DisplayOutputPin::getCurrent(){
	bool ret = false;

	//printf("%08lx\n", posPixelMask);
	//printf("%08lx\n", *data);
	if ((posPixelMask & *data) == posPixelMask){
		ret = true;
	}

	return ret;
}


