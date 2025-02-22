#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define LED_PIN 1

int main() {
    printf("Program is starting...\n");

    wiringPiSetup();

    softPwmCreate(LED_PIN, 0, 100);

    while(1) {
        for (int i = 0; i <= 100; i++) {
            softPwmWrite(LED_PIN, i);
            delay(20);
        }
        delay(300);
        for (int i = 100; i >= 0; i--) {
            softPwmWrite(LED_PIN, i);
            delay(20);
        }
        delay(300);
    }

    return 0;
}