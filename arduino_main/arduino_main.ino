
#include "SagarDisplay.h"

void setup(){
    printf("Entered setup()\n");

    SagarDisplay::setup();
/*

    pinMode(12, OUTPUT);
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);

    
    // HACK for testing - move the scan line to the last line :-)
    for (int i=0; i != 10; ++i){
        delay(10);
        digitalWrite(12, HIGH);
        delay(10);
        digitalWrite(12, LOW);
    }

*/
    printf(" - Finished setup()\n");
}

void loop(){
    SagarDisplay::loop();

/*
    digitalWrite(12, HIGH);
    delay(1);
    digitalWrite(12, LOW);
    delay(1);
*/
    
}
