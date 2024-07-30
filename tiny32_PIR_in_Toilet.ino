#include <tiny32.h>
tiny32 mcu;
#define PIR_PIN 26  //กำหนดขา tiny32 ที่จะนำไปเชื่อมต่อกับ PIR sensor
#define DELAY_TIME  10 //เวลาหน่วงของการเปิด relay (วินาที)
bool pir_status = 0; //ตัวแปรรับค่า PIR sensor
bool relay_status = 0; //ตัวแปรเก็บค่าสถานะ relay
int time_cnt = 0; //ตัวแปรนับเวลา


void setup()
{
  pinMode(PIR_PIN,INPUT); //กำหนดขาให้เป็นอินพุต*
  Serial.begin(115200);
  Serial.println("**** Example_10_PIR ****");
}

void loop()
{
  pir_status = digitalRead(PIR_PIN); //อ่านค่าจากเซนเซอร์ แล้วนำค่าที่ได้มาเก็บไว้ในตัวแปร

  //เช็คการหน่วงเวลาการ เปิด-ปิดไฟ
  if(time_cnt > DELAY_TIME)
  {
    relay_status = 0;
    mcu.Relay(relay_status);
  }
  else
  {
    relay_status = 1;
    mcu.Relay(relay_status);
  }

  //ตรวจสอบสถานะของ PIR และทำการรีเซตเวลาที่ใช้ในการหน่วง
  if(pir_status == 1)
  {
    time_cnt=0; //รีเซตเวลานับ
  }
  else
  {
    time_cnt++; //เพิ่มเวลานับ
  }
  
  Serial.printf("PIR Status => %d\r\n",pir_status); //แสดงค่าสถานะ PIR
  Serial.printf("Relay status => %d\r\n",relay_status); //แสดงสถานะ relay
  Serial.printf("Time count => %d sec\r\n",time_cnt); //แสดงการนับเวลา
  Serial.println("********************");

  vTaskDelay(1000);
}