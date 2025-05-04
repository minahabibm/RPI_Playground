#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <ADCDevice.hpp>

#define Z_PIN 1                         // pin for axis Z

ADCDevice *adc;

int main(void) {
    adc = new ADCDevice();
    printf("Program is starting...\n");

    if(adc -> detectI2C(0x48)) {
        delete adc;
        adc = new PCF8591();
    } else if (adc -> detectI2C(0x4B)) {
        delete adc;
        adc = new ADS7830();
    } else {
        printf("No correct I2C address found, \n"
                "Please use command 'i2cdetect -y 1' to check the I2C address! \n"
                "Program will exit. \n");
        return -1;
    }

    if (adc == nullptr) {
        printf("Error: ADC device initialization failed.\n");
        return -1;
    }

    wiringPiSetup();                                                          
    pinMode(Z_PIN, INPUT);                                                              // set the Z pin as input
    pullUpDnControl(Z_PIN, PUD_UP);                                                     // enable pull-up resistor on the Z pin

    while (1) {
        int val_Z = digitalRead(Z_PIN);                                                 // read the Z pin value
        int val_Y = adc -> analogRead(0);                                               // read the Y axis value from A1 pin using the ADC device
        int val_X = adc -> analogRead(1);                                               // read the X axis value from A0 pin using the ADC device

        printf("Joystick readings - X-axis: %d, Y-axis: %d, Z-button: %d\n", val_X, val_Y, val_Z);

        delay(100);
    }
    return 0;
}
