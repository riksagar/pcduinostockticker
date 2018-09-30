#ifndef __SDSREADER_H
#define __SDSREADER_H

class SagarDisplayScriptDirector;

class SDSFileReader {
	public:
		static SagarDisplayScriptDirector *readScript();


	private:
		SDSFileReader(){}
		~SDSFileReader(){}
};

#endif //ndef __SDSREADER_H

