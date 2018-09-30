
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "FileStream.h"

namespace sdff {


FileStream::~FileStream(){
	if (filename) delete [] filename;
	if (filehandle) fclose(filehandle);
	if (filebuffer) delete [] filebuffer;
}
FileStream::FileStream(const char *initFilename)
	:filepos(0)
	,filesize(0)
	,filename(NULL)
	,filehandle(NULL)
	,filebuffer(NULL)
{
	filename = new char[1+strlen(initFilename)];
	strcpy(filename, initFilename);

	struct stat st;
	if (0 == stat(filename, &st)){
		filesize = st.st_size;

		filehandle = fopen(filename, "rb");

		if (NULL != filehandle){
			filebuffer = new char[1024];
			setvbuf(filehandle, filebuffer, _IOFBF, 1024);
		}
	}
}

unsigned int FileStream::getSize(){
	printf("Read file size %u\n", filesize);
	return filesize;
}
unsigned int FileStream::getPosition(){
	printf("Read file position %u\n", filepos);
	return filepos;
}
void FileStream::setPosition(unsigned int pos){
	printf("Modified fileposition: %u - %u\n", filepos, pos);
	if (pos <= filesize){
		filepos = pos;
	}
}
unsigned char FileStream::getUint8(){
	int c = EOF;
	unsigned char ret;
	if (filepos >= filesize) {
		printf("Attempting to read past expected filelength\n");
	}
	else {
		c = fgetc(filehandle);
		if (EOF == c){
			printf("Unexpected EoF\n");
		}
		else {
			++filepos;
		}	
	}

	if (c != EOF) {
		ret = 0xff&c;
	}
	else {
		ret = 0;
	}
	printf("getUint8 returning %d\n", ret);

	return ret;
}

} //namespace sdff
