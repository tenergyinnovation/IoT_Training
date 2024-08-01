/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6esc3uv29"
#define BLYNK_TEMPLATE_NAME "TINY32"
#define BLYNK_AUTH_TOKEN            "e9ZwFe_ALyyuhpgu1pjeOFecW_CsBIxZ"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <tiny32_v3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TENERGY-IOT";
char pass[] = "L0vemel0vemydog";
uint8_t id = 1; //Address of XY-MD02 sensor module, You can change here if it differance

float temperature, humidity;

tiny32_v3 mcu;
LiquidCrystal_I2C lcd(0x27,20,4); 

BLYNK_WRITE(V0)
{
  int _Relay = param.asInt();
  Serial.printf("_Relay = > %d\r\n",_Relay);
  mcu.Relay(_Relay);
}

BLYNK_WRITE(V1)
{
  int _Red_LED = param.asInt();
  Serial.printf("_Red_LED = > %d\r\n",_Red_LED);
  mcu.RedLED(_Red_LED);
}

BLYNK_WRITE(V2)
{
  int _Blue_LED = param.asInt();
  Serial.printf("_Blue_LED = > %d\r\n",_Blue_LED);
  mcu.BlueLED(_Blue_LED);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.printf("\r\n**** tiny32_XY-MD02_LCD20x4 BLYNK ****\r\n");
  mcu.library_version();
  mcu.XY_MD02_begin(RXD2,TXD2); //กำหนด pin ที่ใช้ในการเชื่อมต่อ


  /* LCD code */
  lcd.init(); //กำหนดค่าเริ่มต้นให้กับ LCD
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.backlight(); //จอ backlight ติด
  lcd.print(" XY_MD02+LCD+BLYNK ");
  lcd.setCursor(0, 1);
  lcd.print("Start Program");
  mcu.buzzer_beep(2);
}

void loop()
{
    static long _interval_time = 0;

    if ((millis() - _interval_time) > 1000)
    {
         //อ่านค่าจากเซนเซอร์ XY-MD02
          temperature = mcu.XY_MD02_tempeature(id); 
          humidity = mcu.XY_MD02_humidity(id);
      
          Serial.printf("Temperature[%d] => %.1f C\r\n",id,temperature);
          Serial.printf("Humidity[%d] => %.1f%c\r\n",id,humidity,37);
          Serial.println("-------------------------------");
          lcd.clear(); 
          lcd.setCursor(0, 0);
          lcd.printf("Temp[%d]: %.1fC",id,temperature);
          lcd.setCursor(0, 1);
          lcd.printf("Humi[%d]: %.1f%c",id,humidity,37);

          Blynk.virtualWrite(V3, temperature);
          Blynk.virtualWrite(V4, humidity);

          _interval_time = millis();
    } 

 
 
    Blynk.run();
}

