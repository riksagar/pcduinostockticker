

#include <stdio.h>


#include "SagarDisplayControlFileReader.h"


SDCReader *SDCReader::loadBytes(unsigned char *dataBytes) {
	if (0 != *dataBytes++) return NULL; // version
	if (0 != *dataBytes++) return NULL; // flags
	if (0 != *dataBytes++) return NULL; // flags
	if (0 != *dataBytes++) return NULL; // flags

	unsigned short int width = *dataBytes++;
	unsigned short int height = *dataBytes++;
	unsigned long int size = *dataBytes++;
	size <<= 8;
	size |= *dataBytes++;

	// TODO use header to calcuate this...
	unsigned long int *initdata = new unsigned long int[width];

	int idx=0;
	for (int w = 0; w != width; ++w){
		initdata[w] = 0;
		for (int h = 0; h != 4; ++h){
			unsigned long int val = dataBytes[w*4+h];
			printf("%ix%i (%i) - %04x\n", w, h, w*4+h, val);
			initdata[w] <<= 8;
			initdata[w] |= val;
		}
	}

	return new SDCReader(width, height, size, initdata);
}


unsigned short int SDCReader::getWidth(){
	return dispWidth;
}

unsigned short int SDCReader::getHeight(){
	return dispHeight;
}

unsigned long int const *SDCReader::get(int column){
	return &data[column];
}



SDCReader::SDCReader(unsigned short int width, unsigned short int height, unsigned long int size, unsigned long int *d)
	:data(d)
	,dispWidth(width)
	,dispHeight(height)
	,payloadSize(size)
{

	printf("Width: %u; Height: %u; Payload: %lu\n", dispWidth, dispHeight, payloadSize);

	for (int i=0; i != dispWidth; ++i){
		printf("%i - %08lx\n", i, data[i]);
	}
}

SDCReader::~SDCReader(){
	delete [] data;
}

