#include <Arduino.h>
#include <tiny32_v3.h>

tiny32_v3 mcu; //define object

uint8_t id = 1; //Address of XY-MD02 sensor module, You can change here if it differance

float temperature, humidity;

void setup()
{
  Serial.begin(115200);
  Serial.printf("\r\n**** tiny32_XY-MD02_getParam ****\r\n");
  mcu.library_version();
  mcu.XY_MD02_begin(RXD2,TXD2); //กำหนด pin ที่ใช้ในการเชื่อมต่อ
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
    delay(1000);
}