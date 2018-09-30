#ifndef __SDCFILEREADER_H
#define __SDCFILEREADER_H

class SDCReader {
public:
	static SDCReader *loadBytes(unsigned char *data);
	unsigned short int getWidth();
	unsigned short int getHeight();
	unsigned long int const *get(int column);

	SDCReader(unsigned short int width, unsigned short int height, unsigned long int payloadSize, unsigned long int *data);
	~SDCReader();

private:
	unsigned long int *data;
	unsigned short int dispWidth;
	unsigned short int dispHeight;
	unsigned long int payloadSize;


};


#endif //ndef __SDCFILEREADER_H
