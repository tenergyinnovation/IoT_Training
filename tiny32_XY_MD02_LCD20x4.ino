#include <Arduino.h>
#include <tiny32_v3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

tiny32_v3 mcu; //define object
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20chars and 4 line display

uint8_t id = 1; //Address of XY-MD02 sensor module, You can change here if it differance

float temperature, humidity;

void setup()
{
  Serial.begin(115200);
  Serial.printf("\r\n**** tiny32_XY-MD02_LCD20x4 ****\r\n");
  mcu.library_version();
  mcu.XY_MD02_begin(RXD2,TXD2); //กำหนด pin ที่ใช้ในการเชื่อมต่อ


  /* LCD code */
  lcd.init(); //กำหนดค่าเริ่มต้นให้กับ LCD
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.backlight(); //จอ backlight ติด
  lcd.print("tiny32 XY-MD02 + LCD");
  lcd.setCursor(0, 1);
  lcd.print("Start Program");


  mcu.buzzer_beep(2); //buzzer 2 beeps
}

void loop()
{
    //อ่านค่าจากเซนเซอร์ XY-MD02
    temperature = mcu.XY_MD02_tempeature(id); 
    humidity = mcu.XY_MD02_humidity(id);
 
    Serial.printf("Temperature[%d] => %.1f C\r\n",id,temperature);
    Serial.printf("Humidity[%d] => %.1f%c\r\n",id,humidity,37);
    Serial.println("-------------------------------");
    lcd.clear(); 
    lcd.setCursor(0, 0);
    lcd.printf("Temperature[%d] => %.1f C",id,temperature);
    lcd.setCursor(0, 1);
    lcd.printf("Humidity[%d] => %.1f%c",id,humidity,37);
    delay(1000);
}