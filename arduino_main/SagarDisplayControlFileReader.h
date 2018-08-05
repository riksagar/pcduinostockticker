#ifndef __SDCFILEREADER_H
#define __SDCFILEREADER_H

class SDCReader {
public:
	static SDCReader *loadBytes(unsigned char *data);
	unsigned short int getWidth();
	unsigned short int getHeight();
	unsigned long int const *get(int column);

	~SDCReader();

private:
	unsigned long int *data;
	SDCReader(unsigned short int width, unsigned short int height, unsigned long int payloadSize, unsigned long int *data);
	unsigned short int dispWidth;
	unsigned short int dispHeight;
	unsigned long int payloadSize;

	static SDCReader *loadBytesV0(unsigned char version, unsigned char f1, unsigned char f2, unsigned char f3, unsigned char *dataBytes);


};


#endif //ndef __SDCFILEREADER_H
