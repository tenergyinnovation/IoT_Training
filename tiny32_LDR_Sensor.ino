#include <Arduino.h>
#include <tiny32_v3.h>

tiny32_v3 mcu;
#define LDR_PIN 39

void setup()
{
    Serial.begin(115200);
    Serial.println("**** tiny32_LDR_Sensor ****"); 
    mcu.buzzer_beep(2);
}

void loop()
{
    int _adcValue = analogRead(LDR_PIN);
    float _voltage = (3.3 * _adcValue)/4095;
    Serial.printf("LDR ADC value = %d\r\n",_adcValue);
    Serial.printf("LDR Voltage value = %0.1f V\r\n",_voltage);
    Serial.println();
    vTaskDelay(1000);
}
