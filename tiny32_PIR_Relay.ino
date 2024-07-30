#include <tiny32_v3.h>
tiny32_v3 mcu;
#define PIR_PIN 26  //กำหนดขา tiny32 ที่จะนำไปเชื่อมต่อกับ PIR sensor
bool pir_status = 0; //ประกาศค่าตัวแปรเป็นชนิด  bool ที่จะนำมารับค่า PIR sensor


void setup()
{
  pinMode(PIR_PIN,INPUT); //กำหนดขาให้เป็นอินพุต*
  Serial.begin(115200);
  Serial.println("**** Example_9_PIR ****");
}

void loop()
{
  pir_status = digitalRead(PIR_PIN); //อ่านค่าจากเซนเซอร์ แล้วนำค่าที่ได้มาเก็บไว้ในตัวแปร
  Serial.printf("PIR Statsu => %d\r\n",pir_status); //ทำการแสดงค่าที่อ่านมาได้
  mcu.Relay(pir_status);
  vTaskDelay(500);
}