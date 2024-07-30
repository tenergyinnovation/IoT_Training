#include <Arduino.h>
#include <tiny32_v3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

tiny32_v3 mcu;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27
#define LDR_PIN 39

void setup()
{
    Serial.begin(115200);
    Serial.println("**** tiny32_LDR_Sensor_LCD20x4 ****"); 

    /* LCD code */
    lcd.init(); //กำหนดค่าเริ่มต้นให้กับ LCD
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.backlight(); //จอ backlight ติด
    lcd.print(" LDR SENSOR LCD20x4 ");
    lcd.setCursor(0, 1);
    lcd.printf("Start Program");
    mcu.buzzer_beep(2);
}

void loop()
{
    int _adcValue = analogRead(LDR_PIN);
    float _voltage = (3.3 * _adcValue)/4095;
    Serial.printf("LDR ADC value = %d\r\n",_adcValue);
    Serial.printf("LDR Voltage value = %0.1f V\r\n",_voltage);
    Serial.println();
    
    //LCD display
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.printf("LDR ADC = %d",_adcValue);
    lcd.setCursor(0, 1);
    lcd.printf("LDR Voltage = %0.1fV",_voltage);
    vTaskDelay(1000);
}
