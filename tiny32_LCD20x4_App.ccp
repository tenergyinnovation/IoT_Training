#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <tiny32_v3.h>

tiny32_v3 mcu;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int count = 0; //กำหนดค่าตัวแปลในการนับ

void setup()
{
  lcd.init(); //กำหนดค่าเริ่มต้นให้กับ LCD 
  lcd.clear(); //ใช้ล้างหน้าจอ เมื่อมีตัวอักษรใดๆอยู่บนหน้าจอ จะถูกล้างออกทั้งหมด
  lcd.backlight(); //ให้แสงหน้าจอ LCD ติด


  lcd.setCursor(3,0); //ตำแหน่ง X=3, Y=0
  lcd.print("Hello, world!"); //ข้อความบรรทัดที่ 1


  lcd.setCursor(0,1); //ตำแหน่ง X=0, Y=1
  lcd.print("TINY32 (ESP32 WiFi)"); //ข้อความบรรทัดที่ 2
  mcu.buzzer_beep(2);
  delay(1000);
  lcd.clear(); //ใช้ล้างหน้าจอ เมื่อมีตัวอักษรใดๆอยู่บนหน้าจอ 
}


void loop()
{

  if(mcu.Sw1()) //ตัวสอบการกด SW1 สำหรับการแสดงผลหน้าจอ LCD
  {
    mcu.buzzer_beep(1);
    delay(500);
    count = count + 1; //บวกค่า count ไปอีก 1
    lcd.backlight(); //ให้แสงหน้าจอ LCD ติด
  
    if(count == 1)
    {
        lcd.setCursor(0,0); //ตำแหน่ง X=0, Y=0
        lcd.print("LCD20x4 ->  LINE # 1"); //ข้อความบรรทัดที่ 1
    }
    else if(count == 2)
    {
        lcd.setCursor(0,1); //ตำแหน่ง X=0, Y=1
        lcd.print("LCD20x4 ->  LINE # 2"); //ข้อความบรรทัดที่ 2
    }
    else if(count == 3)
    {
        lcd.setCursor(0,2); //ตำแหน่ง X=0, Y=2
        lcd.print("LCD20x4 ->  LINE # 3"); //ข้อความบรรทัดที่ 3
    }
    else if(count == 4)
    {
        lcd.setCursor(0,3); //ตำแหน่ง X=0, Y=3
        lcd.print("LCD20x4 ->  LINE # 4"); //ข้อความบรรทัดที่ 4
    }
  }


  if(mcu.Sw2()) //ตัวสอบการกด SW2 สำหรับการล้างหน้าจอ LCD
  {
    mcu.buzzer_beep(2);
    delay(500);
    count = 0; //กำหนดให้ตัวแปล count = 0
    lcd.clear(); //ใช้ล้างหน้าจอ เมื่อมีตัวอักษรใดๆอยู่บนหน้าจอ 
    lcd.noBacklight(); // ปิดไฟแบล็กไลค์
  }

  delay(100);

}
