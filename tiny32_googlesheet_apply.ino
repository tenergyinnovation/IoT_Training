#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <tiny32_v3.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Change SSID and password of WiFi router here
const char * ssid = "TENERGY-IOT";
const char * password = "L0vemel0vemydog";

String GOOGLE_SCRIPT_ID = "AKfycbyf0hzoyO_OUoFTrn-cJeygosmdtm2cJj-FYEVWHiAQgQ4RJCM5DiC8fxI7OsydhC_Y";  //Change Deployment ID here


const char * root_ca=\
"-----BEGIN CERTIFICATE-----\n" \
"MIIDujCCAqKgAwIBAgILBAAAAAABD4Ym5g0wDQYJKoZIhvcNAQEFBQAwTDEgMB4G\n" \
"A1UECxMXR2xvYmFsU2lnbiBSb290IENBIC0gUjIxEzARBgNVBAoTCkdsb2JhbFNp\n" \
"Z24xEzARBgNVBAMTCkdsb2JhbFNpZ24wHhcNMDYxMjE1MDgwMDAwWhcNMjExMjE1\n" \
"MDgwMDAwWjBMMSAwHgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMjETMBEG\n" \
"A1UEChMKR2xvYmFsU2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjCCASIwDQYJKoZI\n" \
"hvcNAQEBBQADggEPADCCAQoCggEBAKbPJA6+Lm8omUVCxKs+IVSbC9N/hHD6ErPL\n" \
"v4dfxn+G07IwXNb9rfF73OX4YJYJkhD10FPe+3t+c4isUoh7SqbKSaZeqKeMWhG8\n" \
"eoLrvozps6yWJQeXSpkqBy+0Hne/ig+1AnwblrjFuTosvNYSuetZfeLQBoZfXklq\n" \
"tTleiDTsvHgMCJiEbKjNS7SgfQx5TfC4LcshytVsW33hoCmEofnTlEnLJGKRILzd\n" \
"C9XZzPnqJworc5HGnRusyMvo4KD0L5CLTfuwNhv2GXqF4G3yYROIXJ/gkwpRl4pa\n" \
"zq+r1feqCapgvdzZX99yqWATXgAByUr6P6TqBwMhAo6CygPCm48CAwEAAaOBnDCB\n" \
"mTAOBgNVHQ8BAf8EBAMCAQYwDwYDVR0TAQH/BAUwAwEB/zAdBgNVHQ4EFgQUm+IH\n" \
"V2ccHsBqBt5ZtJot39wZhi4wNgYDVR0fBC8wLTAroCmgJ4YlaHR0cDovL2NybC5n\n" \
"bG9iYWxzaWduLm5ldC9yb290LXIyLmNybDAfBgNVHSMEGDAWgBSb4gdXZxwewGoG\n" \
"3lm0mi3f3BmGLjANBgkqhkiG9w0BAQUFAAOCAQEAmYFThxxol4aR7OBKuEQLq4Gs\n" \
"J0/WwbgcQ3izDJr86iw8bmEbTUsp9Z8FHSbBuOmDAGJFtqkIk7mpM0sYmsL4h4hO\n" \
"291xNBrBVNpGP+DTKqttVCL1OmLNIG+6KYnX3ZHu01yiPqFbQfXf5WRDLenVOavS\n" \
"ot+3i9DAgBkcRcAtjOj4LaR0VknFBbVPFd5uRHg5h6h+u/N5GJG79G+dwfCMNYxd\n" \
"AfvDbbnvRG15RjF+Cv6pgsH/76tuIMRQyV+dTZsXjAzlAcmgQWpzU/qlULRuJQ/7\n" \
"TBj0/VLZjmmx6BEP3ojY+x1J96relc8geMJgEtslQIxq/H5COEBkEveegeGTLg==\n" \
"-----END CERTIFICATE-----\n";

/**** Pre-define functon ****/
void sendData(String params);


/*** Define Object variable ***/
WiFiClientSecure client;
tiny32_v3 mcu;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 20chars 
uint8_t id = 1; //Address of XY-MD02 sensor module, You can change here if it differance

float temperature, humidity;


void setup() {
  Serial.begin(115200);
  Serial.println("**** googlesheet_record_apply ****"); 
  mcu.XY_MD02_begin(RXD2,TXD2); //กำหนด pin ที่ใช้ในการเชื่อมต่อ


  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Started");
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(500);
    Serial.print(".");
  }

  Serial.print("\r\nSSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Ready to go");
  
  /* LCD code */
  lcd.init(); //กำหนดค่าเริ่มต้นให้กับ LCD
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.backlight(); //จอ backlight ติด
  lcd.print("tiny32 Google Sheet");
  lcd.setCursor(0, 1);
  lcd.print("Start Program");


  vTaskDelay(3000);
  mcu.buzzer_beep(2);
  mcu.library_version();

}

void loop() {

  vTaskDelay(5000);
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

  //Record data to google sheet
  String DataString = "Temp="; //label of row don't have space bar (ชื่อหัวข้อต้องไม่มีเว้นช่องว่าง) *
  DataString += String(temperature,2);
  DataString += "&Humi=";   //ใช้เครื่องหมาย & เป็นตัวแบ่ง row
  DataString += String(humidity,2);
  sendData(DataString);
}

void sendData(String params) {
    mcu.buzzer_beep(1);
    HTTPClient http;
    String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
    Serial.print(url);
    Serial.print("Making a request");
    http.begin(url, root_ca); //Specify the URL and certificate
    int httpCode = http.GET();  
    http.end();
    Serial.println(": done "+httpCode);
}

