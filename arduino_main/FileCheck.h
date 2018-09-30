#ifndef __FILECHECK_H
#define __FILECHECK_H

class FileCheck {

public:
	static void setup(const char *filename);

	static bool check();
        static void reset();    

private:
	static unsigned long checktime;
	static char *filename;
	static const unsigned long CHECK_INTERVAL_MS;
};

#endif //ndef __FILECHECK_H
