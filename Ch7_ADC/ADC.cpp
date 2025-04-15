#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <ADCDevice.hpp>

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

    while (1) {
        int adcValue = adc -> analogRead(0);                                    // read the analog value from A0 pin
        int maxADCValue = 255;                                                  // maximum ADC value
        float referenceVoltage = 3.3;                                           // reference voltage of the ADC
        float voltage = (float)adcValue / maxADCValue * referenceVoltage;       // calculate the ADC value to voltage
        printf("ADC value: %d, \tVoltage: %.2f V\n", adcValue, voltage);         
        delay(100);
    }
}
