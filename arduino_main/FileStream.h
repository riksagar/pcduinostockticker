#ifndef __SDFF_FILE_STREAM_HPP
#define __SDFF_FILE_STREAM_HPP

#include "SdffParser.h"

namespace sdff {
	class FileStream: public sdff::Stream {

		public: 
			virtual unsigned int getSize();
			virtual unsigned int getPosition();
			virtual void setPosition(unsigned int pos);
			virtual unsigned char getUint8();
	
			virtual ~FileStream();
			FileStream(const char *filename);

		private: 
			char *filename;
			unsigned int filesize;
			FILE *filehandle;
			char  *filebuffer;
			unsigned int filepos;
	};
} //namespace

#endif //ndef __SDFF_FILE_STREAM_HPP
