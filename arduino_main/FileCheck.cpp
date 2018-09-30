
#if !defined(NARDUINO)
#include <Arduino.h>
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "FileCheck.h"

void FileCheck::setup(const char *fname){
	filename = new char[1+strlen(fname)];
	strcpy(filename, fname);

	checktime = 0;

}

bool FileCheck::check(){
	bool ret = false;
	unsigned long now = millis();

	bool doCheck = false;
	if (now < checktime){
		// overflow, just check now for simplicity
		doCheck = true;
	}
	else if ( now >= (checktime + FileCheck::CHECK_INTERVAL_MS) ) {
		doCheck = true;
	}

	if (doCheck){
printf("Checking file stats for %s\n", filename);
		checktime = now;
		struct stat st;  
                unsigned long statret = stat(filename, &st);
printf("Stat ret: %i\n", statret);                
		if (0 == statret){
			// file exists.  Need to go investigate
			ret = true;
		}
	}

	return ret;
}

void FileCheck::reset(){
    remove(filename);
  
}


char *FileCheck::filename;
unsigned long FileCheck::checktime;
const unsigned long FileCheck::CHECK_INTERVAL_MS = 5000;

