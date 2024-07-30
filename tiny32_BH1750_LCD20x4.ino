
#include <Arduino.h>
#include <tiny32_v3.h>
#include <Wire.h>
#include <ErriezBH1750.h>
#include <LiquidCrystal_I2C.h>


// ADDR line LOW/open:  I2C address 0x23 (0x46 including R/W bit) [default]
// ADDR line HIGH:      I2C address 0x5C (0xB8 including R/W bit)
BH1750 sensor(LOW);
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
tiny32_v3 mcu;


void setup()
{
    Serial.begin(115200);

    Serial.println("**** tiny32_BH1750_LCD20x4 ****"); 

    // Initialize I2C bus
    Wire.begin();

    // Initialize sensor in continues mode, high 0.5 lx resolution
    sensor.begin(ModeContinuous, ResolutionMid);

    // Start conversion
    sensor.startConversion();
    
    /* LCD code */
    lcd.init(); //กำหนดค่าเริ่มต้นให้กับ LCD
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.backlight(); //จอ backlight ติด
    lcd.print("*  BH1750 LCD20x4  *");
    lcd.setCursor(0, 1);
    lcd.printf("Start Program");

    mcu.buzzer_beep(2);
}

void loop()
{
    uint16_t _lux;

    // Wait for completion (blocking busy-wait delay)
    if (sensor.isConversionCompleted()) {
        
        // Read light
        _lux = sensor.read();
        Serial.printf("Light = %d lux\r\n",_lux);

        // LCD display
        lcd.clear(); 
        lcd.setCursor(0, 0);
        lcd.print("** BH1750: **");
        lcd.setCursor(0, 1);
        lcd.printf("Light: %d",_lux);
    }

    vTaskDelay(1000);
}
