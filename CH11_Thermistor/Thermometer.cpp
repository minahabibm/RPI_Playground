#include <stdio.h>
#include <math.h>
#include <wiringPi.h>
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
        int adcValue = adc -> analogRead(0);                                                                // read the analog value from A0 pin using the ADC device
        int maxADCValue = 255;                                                                              // maximum ADC value
        float referenceVoltage = 3.3;                                                                       // reference voltage of the ADC
        float voltage = (float)adcValue / maxADCValue * referenceVoltage;                                   // calculate the ADC value to voltage
        
        float Rt = 10 * voltage / (referenceVoltage - voltage);                                             // calculate the resistance of the thermistor
        float R = 10;                                                                                       // resistance of the thermistor at 25 degrees Celsius
        float B = 3950;                                                                                     // B value of the thermal index of thermistor
        float T1 = 25;                                                                                      // reference temperature in Celsius

        float tempK = 1  / (1 / (273.15 + t1) + log(Rt / R) / B);                                           // calculate the temperature in Kelvin
        float tempC = tempK - 273.15;                                                                       // convert the temperature to Celsius
        float tempF = tempC * 9 / 5 + 32;                                                                   // convert the temperature to Fahrenheit

        printf("ADC value: %d, \tVoltage: %.2f V, \tTemperature_C : %.2fC, \tTemperature_F : %.2fC\n", adcValue, voltage, tempC, tempF);

        delay(100);
    }

    return 0;
}
