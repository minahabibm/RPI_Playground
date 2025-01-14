#include<stdio.h>
#include<wiringPi.h>

#define ledPin 0
#define buttonPin  1

int ledState=LOW;
int buttonState=HIGH;
int lastButtonState=HIGH;
long lastDebounceTimeMs;
long debounceDelayMs=50;
int currentButtonState;

int main(void) {
    printf("Program is starting ..\n");

    wiringPiSetup();

    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);

    pullUpDnControl(buttonPin, PUD_UP);

    while(1)  {
        currentButtonState = digitalRead(buttonPin);
        if(currentButtonState != lastButtonState) {
            lastDebounceTimeMs = millis();
        } 
        
        if(millis() - lastDebounceTimeMs > debounceDelayMs) {
            if(currentButtonState != buttonState) {
                buttonState = currentButtonState;
                if(buttonState == LOW) {
                    printf("Button is pressed!\n");
                    ledState = !ledState;
                    if(ledState) {
                        printf("turn on LED ... \n");
                    } else {
                        printf("turn off LED ... \n");
                    }
                } else {
                    printf("Button is released!\n");
                }
            }
        }

        digitalWrite(ledPin, ledState);
        lastButtonState = currentButtonState;    
    }

    return 0;
}
