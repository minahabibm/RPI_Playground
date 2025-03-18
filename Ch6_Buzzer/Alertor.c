#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
#include <softTone.h>

#define buzzerPin 0
#define buttonPin 1

void alertor(int pin) {
    double sinVal, toneVal;
    const double baseTone = 2000;                   // Base frequency for the alertor tone in Hz
    for(int x=0; x<360; x++) {
        sinVal = sin(x * (M_PI / 180));             // calculate the sine value
        toneVal = baseTone + sinVal * 500;          // Adjust the resonant frequency and weighted sine wave.
        softToneWrite(pin, toneVal);                // output PWM
        delay(1);
    }
}

void stopAlertor(int pin) {
    softToneWrite(pin, 0);
}

int main(void) {
    printf("Program is starting...\n");

    wiringPiSetup();

    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT);

    softToneCreate(buzzerPin);
    pullUpDnControl(buttonPin, PUD_UP);

    while(1) {
        // Check if the button is pressed (active-low configuration)
        if(digitalRead(buttonPin) == LOW) {
            alertor(buzzerPin);
            printf("Alertor turned on >>> \n");
        } else {
            stopAlertor(buzzerPin);
            printf("Alertor turned off <<< \n");
        }
    }

    return 0;
}