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
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#include <tiny32_v3.h>
#include <WiFi.h>
#define BLYNK_TEMPLATE_ID "TMPL6esc3uv29" // *** แก้ไขตรงนี้ ***
#define BLYNK_TEMPLATE_NAME "TINY32" // *** แก้ไขตรงนี้ ***

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI

#include "BlynkEdgent.h"

tiny32_v3 mcu;

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
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
  mcu.buzzer_beep(2);
}

void loop() {
  BlynkEdgent.run();
}

