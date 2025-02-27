#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <tiny32_v3.h>

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

int B_var = 0;
int C_var = 0;
int D_var = 0;
float E_var = 0;
float F_var = 0;
float G_var = 0;


void setup() {
  Serial.begin(115200);
  Serial.println("**** googlesheet_record ****"); 


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
  
  vTaskDelay(3000);
  mcu.buzzer_beep(2);
  mcu.library_version();
}

void loop() {

  vTaskDelay(5000);

  //Record data to google sheet
  String DataString = "Row_B="; //label of row don't have space bar (ชื่อหัวข้อต้องไม่มีเว้นช่องว่าง) *
  DataString += String(B_var);
  DataString += "&Row_C=";   //ใช้เครื่องหมาย & เป็นตัวแบ่ง row
  DataString += String(C_var);
  DataString += "&Row_D=";
  DataString += String(D_var);
  DataString += "&Row_E=";
  DataString += String(E_var);
  DataString += "&Row_F=";
  DataString += String(F_var,1); //แสดงทศนิยม 1 ตำแหน่ง
  DataString += "&Row_G=";
  DataString += String(G_var,2); //แสดงทศนิยม 2 ตำแหน่ง
  sendData(DataString);
  
  //เพิ่มค่าตัวแปร
  B_var++;
  C_var+=5;
  D_var+=10;
  E_var+=0.1;
  F_var+=0.11;
  G_var+=0.22;
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

