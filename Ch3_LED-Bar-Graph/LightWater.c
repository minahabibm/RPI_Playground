#include <stdio.h>
#include <wiringPi.h>

#define ledCounts 10
const int pins[ledCounts] = {0, 1, 2, 3, 4, 5, 6, 8, 9, 10};

void main(void) {
    printf("Program is starting ... \n");

    wiringPiSetup();
    
    for (int i = 0; i < ledCounts; i++) {
        pinMode(pins[i], OUTPUT);
    }
    
    while(1) {
        for(int i = 0; i < ledCounts; i++) {
            digitalWrite(pins[i], LOW);
            delay(100);
            digitalWrite(pins[i], HIGH);
        }

        for (int i = ledCounts - 1; i >= 0; i--) {
            digitalWrite(pins[i], LOW);
            delay(100);
            digitalWrite(pins[i], HIGH);
        }
    }
}
