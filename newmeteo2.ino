#include <DS3231.h>
#include <GyverButton.h>
#include <Wire.h>            // для I2
#include <Button.h>          // для кнопок
#include <Adafruit_BME280.h>// для BME280
#include <LCD5110_Graph.h>
LCD5110 myGLCD(10, 9, 8, 2, 7);
DS3231  rtc(SDA, SCL);
#define LIGHT_PIN 3
#define BTN1 1     // Кнопка подсветки дисплея
Adafruit_BME280 bme;
Time t;
GButton butt1(BTN1);


extern uint8_t SmallFont[];
extern uint8_t RusFont[];
extern uint8_t MediumNumbers[];
int r = random(0,36);
int s2;
char *Dn = "  ";
boolean flag;
boolean led_flag = 0;
int   level_light = 128;      // Уровень подсветки
int v = 53;
float temp,temp_last;
float pres,press_last;
float hum,hum_last;
extern uint8_t cloud[];
extern uint8_t sun[];
extern uint8_t sun3[];
extern uint8_t react[];
extern uint8_t rain[];
extern const unsigned char bitmap_30x20[];
//Button buttonLight(BUTTON_LIGHT,18);
void setup() 
{
  pinMode(LIGHT_PIN, OUTPUT);
  myGLCD.InitLCD();
  myGLCD.drawBitmap(0, 0, react, 84,48);
  myGLCD.update();
  bme.begin();
  rtc.begin();
  bme.setSampling(Adafruit_BME280::MODE_NORMAL,
    Adafruit_BME280::SAMPLING_X4, // temperature
    Adafruit_BME280::SAMPLING_X4, // pressure
    Adafruit_BME280::SAMPLING_X4, // humidity
    Adafruit_BME280::FILTER_OFF,
    Adafruit_BME280::STANDBY_MS_500);
  delay(2000);
}

void loop() 
{
  
{
  t = rtc.getTime();
  pres = bme.readPressure()/133.322;   // Считывание давления
  temp = bme.readTemperature();        // Считывание температуры
  hum = bme.readHumidity();//Считывание влажности
  butt1.tick();  // обязательная функция отработки. Должна постоянно опрашиваться
  if (butt1.isPress() && flag == 0)
    { // одиночное нажатие
      flag = 1;                    // инкремент
      led_flag = !led_flag;
      digitalWrite(LIGHT_PIN, led_flag);  
    }
    if (butt1.isRelease() && flag == 1)
    { // одиночное нажатие
      flag = 0;                    // инкремент  
    }
  myGLCD.clrScr();
  if(pres>=730&&pres<740)
  {
  myGLCD.drawBitmap(50, 30, bitmap_30x20, 37,20);  //20,16
  myGLCD.setFont(RusFont);
  myGLCD.print("Jcflrb", RIGHT, 20);//Осадки
  }
  if(pres>=740&&pres<750)
    {
  myGLCD.drawBitmap(50, 30, cloud, 30,16);  
  myGLCD.setFont(RusFont);
  myGLCD.print("J,kfrf", RIGHT, 20);//Облака
    }
  if(pres>=750&&pres<=780)
  {
  myGLCD.setFont(RusFont);
  myGLCD.print("Zcyj", RIGHT, 20);//Ясно
  myGLCD.drawBitmap(63, 30, sun3, 22,22);
  }
  myGLCD.setFont(SmallFont);
  myGLCD.print("C", RIGHT, 0);
  myGLCD.print("mm", 36, 38);
  myGLCD.print("%", 28, 0);
  myGLCD.printNumF(hum,1, 10, 9);
  myGLCD.printNumF(temp,1, 60, 9);
    if((pres<(press_last-.2))||
     (pres>(press_last+.2))||
     (temp<(temp_last-.1))||(temp>(temp_last+.1))||(hum>(hum_last+1)||hum<(hum_last-1)))
     {
      press_last = pres;
      temp_last = temp;
      hum_last=hum;
     }
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(temp, 50, 0);
    myGLCD.printNumI(hum, LEFT, 0);
    myGLCD.printNumI(pres, LEFT, 30);
     {
  myGLCD.setFont(SmallFont);
  myGLCD.printNumI(t.hour, LEFT, 20);
  if(t.hour <10)
  {
    myGLCD.print("0", LEFT, 20);
    myGLCD.printNumI(t.hour, 6, 20);
  }
  else{
  myGLCD.printNumI(t.hour, LEFT, 20);
  }
  myGLCD.print(":", 12, 20);
  if(t.min <10)
  {
    myGLCD.print("0", 17, 20);
    myGLCD.printNumI(t.min, 23, 20);
  }
  else{
  myGLCD.printNumI(t.min, 17, 20);
  }
   myGLCD.setFont(RusFont);
   myGLCD.print(Dn, 31, 20);
   myGLCD.update();
    delay(50);
    }
}
switch(t.dow)
{
        case 1:{Dn = "DC"; break;}
        case 2:{Dn = "GY"; break;}
        case 3:{Dn = "DN"; break;}
        case 4:{Dn = "CH"; break;}
        case 5:{Dn = "XN"; break;}
        case 6:{Dn = "GN"; break;}
        case 7:{Dn = "C<"; break;}
}
if (t.sec % 10 == 0 && s2 != t.sec) {
    
    hum_last=hum;
  }
  }
  
