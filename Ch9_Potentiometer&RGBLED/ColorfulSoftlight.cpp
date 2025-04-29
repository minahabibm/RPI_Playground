#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <ADCDevice.hpp>

#define ledRedPin 3
#define ledGreenPin 2
#define ledBluePin 0

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
    softPwmCreate(ledRedPin, 0, 100);                                                     
    softPwmCreate(ledGreenPin, 0, 100);
    softPwmCreate(ledBluePin, 0, 100);

    while (1) {
        int val_red   = adc -> analogRead(0);                                                                   // read the analog value from A0 pin using the ADC device
        int val_green = adc -> analogRead(1);                                                                   // read the analog value from A0 pin using the ADC device
        int val_blue  = adc -> analogRead(2);                                                                   // read the analog value from A0 pin using the ADC device
        int maxADCValue = 255;                                                                                  // maximum ADC value

        softPwmWrite(ledRedPin, val_red * 100 / maxADCValue);                                                   // set the brightness of the LED
        softPwmWrite(ledGreenPin, val_green * 100 / maxADCValue);                                               // set the brightness of the LED
        softPwmWrite(ledBluePin, val_blue * 100 / maxADCValue);                                                 // set the brightness of the LED
        printf("ADC value val_red: %d , \tval_green: %d , \tval_blue: %d\n", val_red, val_green, val_blue);

        delay(100);
    }
    return 0;
}
