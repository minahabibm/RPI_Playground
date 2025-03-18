#include <stdio.h>
#include <wiringPi.h>

#define buzzerPin 0
#define buttonPin 1

int main(void) {
    printf("Program is starting...\n");

    wiringPiSetup();

    pinMode(buzzerPin, OUTPUT);
    pinMode(buttonPin, INPUT);

    pullUpDnControl(buttonPin, PUD_UP);

    while(1) {
        // Check if the button is pressed (active-low configuration)
        if(digitalRead(buttonPin) == LOW) {
            digitalWrite(buzzerPin, HIGH);
            printf("Buzzer is on >>> \n");
        } else {
            digitalWrite(buzzerPin, LOW);
            printf("Buzzer is off <<< \n");
        }
    }

    return 0;
}