
#include "SagarDisplay.h"
#include "FileCheck.h"

void setup(){
    printf("Entered setup()\n");

    SagarDisplay::setup();
    FileCheck::setup("/tmp/data");

    printf(" - Finished setup()\n");
}

void loop(){
    if (FileCheck::check()){
       printf("There's new data to display...\n"); 
       SagarDisplay::loadFromFile("/tmp/data");
       FileCheck::reset();
    }

    SagarDisplay::loop();
   
}
