#include "driver/temp_sensor.h"
#include "M5Dial.h"
M5Canvas img(&M5Dial.Display);

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

#include "Noto.h"
#include "smallFont.h"
#include "middleFont.h"
#include "bigFont.h"
#include "secFont.h"

#define color1 TFT_WHITE
#define color2  0x8410
#define color3 0x5ACB
#define color4 0x15B3
#define color5 0x00A3

volatile int counter = 0;
float VALUE;
float lastValue=0;

unsigned short grays[12];

double rad=0.01745;
float x[360];
float y[360];
float px[360];
float py[360];
float lx[360];
float ly[360];

int r=116;
int sx=120;
int sy=120;

#include <WiFi.h>
//#include <TimeLib.h>        // https://forum.arduino.cc/index.php?topic=415296.0
#include "time.h"

const char* ssid       = "<your_ssid>";
const char* password   = "<your_password>";
IPAddress ipadr;

const char* ntpServer = "ntp.jst.mfeed.ad.jp";
const long  gmtOffset_sec = 9 * 3600;  // JST = UTC + 9
const int   daylightOffset_sec = 0;
int hh, mm, ss;
int yy, mon, dd;
int retry = 5;

String cc[12]={"45","40","35","30","25","20","15","10","05","0","55","50"};
String days[]={"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
int start[12];
int startP[60];

int angle=0;
bool onOff=0;

String h="23";
String m="24";
String s="48";
String d1="0";
String d2="1";

String m1="2";
String m2="3";

int lastAngle=0;
float circle=100;
bool dir=0;
int rAngle=359;

long tCircle=0;

void setup()
{
  auto cfg = M5.config();
  M5Dial.begin(cfg, true, true);

  Serial.print("Connect to " + (String)ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time from ntp
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
// int tm_sec;   /* 秒 － [0, 60/61] */
// int tm_min;   /* 分 － [0, 59] */
// int tm_hour;  /* 時 － [0, 23] */
// int tm_mday;  /* 日 － [1, 31] */
// int tm_mon;   /* 1月からの月数 － [0, 11] */
// int tm_year;  /* 1900年からの年数 */
// int tm_wday;  /* 日曜日からの日数 － [0, 6] */
// int tm_yday;  /* 1月1日からの日数 － [0, 365] */
// int tm_isdst; /* 夏時間フラグ */

  for(int i = 0; i < retry; i++)
  {
    if(!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");
      if(i == retry - 1)
      {
        return;
      }
    }else{
      Serial.println("Connected to NTP Server!");
      break;
    }
  }
  
  yy = 1900 + timeinfo.tm_year;
  mon = timeinfo.tm_mon + 1;
  dd = timeinfo.tm_mday;
 
  hh = timeinfo.tm_hour;
  mm = timeinfo.tm_min;
  ss = timeinfo.tm_sec;

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  M5Dial.Rtc.setDateTime( { { yy, mon, dd }, { hh, mm, ss } } );
  sprite.createSprite(240,240);
   
  sprite.setSwapBytes(true);    
  sprite.setSwapBytes(true);
  sprite.setTextDatum(4);

  int b=0;
  int b2=0;

  for(int i=0;i<360;i++)
  {
    x[i]=((r-20)*cos(rad*i))+sx;
    y[i]=((r-20)*sin(rad*i))+sy;
    px[i]=(r*cos(rad*i))+sx;
    py[i]=(r*sin(rad*i))+sy;

    lx[i]=((r-6)*cos(rad*i))+sx;
    ly[i]=((r-6)*sin(rad*i))+sy;
       
    if(i%30==0)
    {
      start[b]=i;
      b++;
    }

    if(i%6==0)
    {
      startP[b2]=i;
      b2++;
    }
  }

  int co=210;
  for(int i=0;i<12;i++)
  {
    grays[i]=tft.color565(co, co, co);
    co=co-20;
  }
}

int inc=0;

void loop() {
  auto dt = M5Dial.Rtc.getDateTime();

  m1 = String((int)dt.date.month/10);
  m2 = String(dt.date.month%10);
  d1 = String((int)dt.date.date/10);
  d2 = String(dt.date.date%10);
  h = String((int)dt.time.hours/10) + String(dt.time.hours%10);
  m = String((int)dt.time.minutes/10) + String(dt.time.minutes%10);

  rAngle=rAngle-3;
  angle=dt.time.seconds*6; 

  if(dt.time.seconds<10){
    s="0"+String(dt.time.seconds);  
  }else{
    s=String(dt.time.seconds);
  }


  if(angle>=360) angle=0;

   if(rAngle<=0)
  {rAngle=359;  tCircle=millis();}


  if(dir==0)
  circle=circle+0.5;
  else
  circle=circle-0.5;
  
  if(circle>140)
  dir=!dir;

  if(circle<100)
  dir=!dir;



  if(angle>-1)
  {
     lastAngle=angle;      

     VALUE=((angle-270)/3.60)*-1;
     if(VALUE<0)
     VALUE=VALUE+100;
 
     
     
 sprite.fillSprite(TFT_BLACK);
sprite.setTextColor(TFT_WHITE,color5);
 
//sprite.drawString(days[now.dayOfTheWeek()],circle,120,2);
sprite.loadFont(secFont);
sprite.setTextColor(grays[1],TFT_BLACK);
sprite.drawString(s,sx,sy-42);
sprite.unloadFont();

sprite.loadFont(smallFont);

 sprite.fillRect(64,82,16,28,grays[8]);
 sprite.fillRect(84,82,16,28,grays[8]);
  sprite.fillRect(144,82,16,28,grays[8]);
 sprite.fillRect(164,82,16,28,grays[8]);

 sprite.setTextColor(0x35D7,TFT_BLACK);
 sprite.drawString("MON",80,72);
 sprite.drawString("DAY",160,72);
 sprite.unloadFont();

  sprite.loadFont(middleFont);
  sprite.setTextColor(grays[2],grays[8]);
  sprite.drawString(m1,71,99,2);
  sprite.drawString(m2,91,99,2);
  sprite.drawString(d1,150,99,2);
  sprite.drawString(d2,170,99,2);
  sprite.unloadFont();


   sprite.loadFont(bigFont);
   sprite.setTextColor(grays[0],TFT_BLACK);
   sprite.drawString(h+":"+m,sx,sy+32);
   sprite.unloadFont();

   sprite.loadFont(Noto);
   sprite.setTextColor(0xA380,TFT_BLACK);
   sprite.drawString("VOLOS",120,190);
   sprite.drawString("***",120,114);
   sprite.setTextColor(grays[3],TFT_BLACK);
 
  for(int i=0;i<60;i++)
  if(startP[i]+angle<360)
 sprite.fillSmoothCircle(px[startP[i]+angle],py[startP[i]+angle],1,grays[4],TFT_BLACK);
 else
 sprite.fillSmoothCircle(px[(startP[i]+angle)-360],py[(startP[i]+angle)-360],1,grays[4],TFT_BLACK);

  for(int i=0;i<12;i++)
 if(start[i]+angle<360){
 sprite.drawString(cc[i],x[start[i]+angle],y[start[i]+angle]);
 sprite.drawWedgeLine(px[start[i]+angle],py[start[i]+angle],lx[start[i]+angle],ly[start[i]+angle],2,2,grays[3],TFT_BLACK);
 }
 else
 {
 sprite.drawString(cc[i],x[(start[i]+angle)-360],y[(start[i]+angle)-360]);
 sprite.drawWedgeLine(px[(start[i]+angle)-360],py[(start[i]+angle)-360],lx[(start[i]+angle)-360],ly[(start[i]+angle)-360],2,2,grays[3],TFT_BLACK);
 }
 
   sprite.drawWedgeLine(sx-1,sy-82,sx-1,sy-70,1,5,0xA380,TFT_BLACK);
   sprite.fillSmoothCircle(px[rAngle],py[rAngle],4,TFT_RED,TFT_BLACK);
   M5Dial.Display.pushImage(0,0,240,240,(uint16_t*)sprite.getPointer());
   sprite.unloadFont();
 
}

}
