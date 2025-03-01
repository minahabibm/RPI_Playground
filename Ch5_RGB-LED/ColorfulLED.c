#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define LedPinRed    0
#define LedPinGreen  1
#define LedPinBlue   2

void setupLedPin(void) {
    softPwmCreate(LedPinRed,  0, 100);
    softPwmCreate(LedPinGreen,0, 100);
    softPwmCreate(LedPinBlue, 0, 100);
}

// If you are using common anode RGBLED,it should be setLedColor(100-r,100-g,100-b)  
// If you want show red, it should be setLedColor(0,100,100) 
void setLedColor(int r, int g, int b) {
    softPwmWrite(LedPinRed,   r);
    softPwmWrite(LedPinGreen, g);
    softPwmWrite(LedPinBlue,  b);
}

int main(void) {
    printf("Program is starting...\n");

    wiringPiSetup();

    setupLedPin();

    int r, g, b;
    while(1) {
        r = random() % 100;
        g = random() % 100;
        b = random() % 100;
        setLedColor(r,g,b);
        printf("r=%d, g=%d, b=%d \n", r,g,b);
        delay(1000);
    }
    return 0;
}
