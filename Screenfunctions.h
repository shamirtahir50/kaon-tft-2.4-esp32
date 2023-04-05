//#include <dummy_rp2040.h>

#include <TFT_eSPI.h>       
#include "OneButton.h"
// FONTS
#include "Fonts.h"

// IMAGES
#include "Screen1logotitle.h"
#include "logo.h"
#include "battary.h"
#include "signal.h"
#include "background.h"
#include "bottom.h" 
#include "dateback.h"
#include "timeback.h"
#include "triback.h" 
#include "pointimg.h" 
#include "s3_yesnoback.h" 
#include "flowvalueback.h" 
#include "flowrateback.h" 
#include "timehourback.h"
#include "volumeback.h"
#include "s5_setflowback.h" 
#include "setflowbackcc.h" 
#include "midscreenback.h" 
#include "minback.h" 
#include "hrback.h"
#include "secback.h"
#include "dayback.h" 
#include "monback.h"
#include "yearback.h"
#include "celback.h"
#include "fahback.h"
#include "battaryback.h"
#include "battaryimages.h"
#include "motionback.h"
#include "tempback.h"
#include "tempunitback.h"
#include "humback.h"
#include "motionback2.h"
#include "tempback2.h"
#include "tempunitback2.h"
#include "humback2.h"
#include "bpback.h"
#include "bpunit.h"
#include "screen14flowunit.h"
#include "delaytimeback.h"
#include "runtimeback.h"
#include "restartback.h"

// Colors
#define TFT_CYAN3 0x028B
#define TFT_GREY3 0x5269
#define TFT_CYAN1 0x871A


// Defination
TFT_eSPI tft = TFT_eSPI();  
//26,28,27
OneButton button1(27, true);
OneButton button2(26, true);
OneButton button3(28, true);
//SerialUART SerialCustom(uart0, 16, 17);

// BOOLEAN
volatile boolean Screen1 = true;
volatile boolean Screen2 = false;
volatile boolean Screen2_up = false;
volatile boolean Screen2_down = false;
volatile boolean Screenup = false;
volatile boolean Screendown = false;
volatile boolean Screenenter = false;
volatile boolean Screen2_enter = false;
volatile boolean Screen8_enter = false;
volatile boolean Screen3_yes = false;
volatile boolean Screen3_no = false;
volatile boolean Screen3 = false;
volatile boolean Screen3_1 = false;
volatile boolean Screen3_1_1 = false;
volatile boolean Screen3_2 = false;
volatile boolean Screen3_2_1 = false;
volatile boolean Screen3_T0  = false;
volatile boolean Screen3_T0_1 = false;
volatile boolean Screen3_T1 = false;
volatile boolean Screen3_T2 = false;
volatile boolean Screen4 = false;
volatile boolean Screen5 = false;
volatile boolean Screen5_1 = false;
volatile boolean Screen5_T0 = false;
volatile boolean Screen6 = false;
volatile boolean Screen6_1 = false;
volatile boolean Screen6_T0 = false;
volatile boolean Screen7 = false;
volatile boolean Screen7from3_2_1 = false;
volatile boolean Screen8 = false;
volatile boolean Screen9 = false;
volatile boolean Screen9_1 = false;
volatile boolean Screen10 = false;
volatile boolean Screen10_1 = false;
volatile boolean Screen10_h = false;
volatile boolean Screen10_m = false;
volatile boolean Screen10_s = false;
volatile boolean Screen10_d = false;
volatile boolean Screen10_mon = false;
volatile boolean Screen10_y = false;
volatile boolean Screen11 = false;
volatile boolean Screen11_1 = false;
volatile boolean Screen11_2 = false;
volatile boolean Screen11_3 = false;
volatile boolean Screen12 = false;
volatile boolean Screen12_1 = false;
volatile boolean Screen13 = false;
volatile boolean Screen14 = false;
volatile boolean Screen15 = false;
volatile boolean Screen15_1 = false;
volatile boolean Screen15error = false;
volatile boolean Screen_15R = false;
volatile boolean PERMISSIONCALIBRATE_yes = true;
volatile boolean PERMISSIONCALIBRATE_no = true;
volatile boolean PERMISSIONRUNTIME_yes = true;
volatile boolean PERMISSIONRUNTIME_no = true;
int yesnotransition = 0;
int flowyesnotransition = 0;
int startyesnotransition = 0;
int stopyesnotransition = 0;
int webyesnotransition = 0;
int confirmyesnotransition = 0;

double flow;
volatile float flowrate = 00.00;
volatile int pressed = 0;

float number = 00.00;

int time_hours = 26 , volume = 70;
volatile int transition = -1;
volatile int settings_transition = -1;
volatile int td_transition = 1;
volatile int screen11_transition = -1;

void down()
{
    if(Screen2 == true){
        transition++;
       if(transition >= 5){
       transition = 0;
      }
      
      Serial.println(transition);
    }
    Screendown = true;
      Screenup = false;
      Screenenter = false;
    if(Screen8 == true){
      settings_transition++;
    if(settings_transition >= 6){
     settings_transition = 0;
    }
     Serial.println(settings_transition);
    }
  
     if(Screen11 == true){
      screen11_transition++;
    if(screen11_transition >= 4){
     screen11_transition = 0;
    }
     Serial.println(screen11_transition);
    }
}
void up(){
//  static unsigned long last_interrupt_time = 0;
//  unsigned long interrupt_time = millis();
//  if (interrupt_time - last_interrupt_time > 200 && digitalRead(button2_pin) == LOW) 
//  {
    if (Screen2 == true){
      transition--;
    if(transition <= -1){
     transition = 4;
    }
    
    Serial.println(transition);
    }
    Screenup = true;
    Screendown = false;
    Screenenter = false;

    if (Screen8 == true){
      settings_transition--;
    if(settings_transition <= -1){
     settings_transition = 5;
    }
    Serial.println(settings_transition);
    }
     if (Screen11 == true){
      screen11_transition--;
    if(screen11_transition <= -1){
     screen11_transition = 3;
    }
    Serial.println(screen11_transition);
    }
//  }
//  last_interrupt_time = interrupt_time;
}
void enter(){
  
  Screenenter = true;
    Screenup = false;
    Screendown = false;
    Serial.println("Enter");
    if(Screen10 == true){
      td_transition++;
     if(td_transition > 6){
        td_transition = 1;
     }
     Serial.println(td_transition);
     Serial.println(Screen10);
    }
}
void click1() {
  Serial.println("Button 1 click.");
  down();
}
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
  down();
}
void longPressStart1() {
  Serial.println("Button 1 longPress start");
} 
void longPress1() {
  
  if(Screen2==true || Screen8==true || Screen5==true || Screen3_1_1==true || Screen11 == true){
    Serial.println("Button 1 longPress...");
  }
  else{
    Serial.println("Button 1 longPress...");
    down();
  }
  
} 
void longPressStop1() {
  Serial.println("Button 1 longPress stop");
}
void click2() {
  Serial.println("Button 2 click.");
  up();
} 
void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
  up();
} 
void longPressStart2() {
  Serial.println("Button 2 longPress start");
} 
void longPress2() {
    if(Screen2==true || Screen8==true || Screen5==true || Screen3_1_1==true || Screen11 == true){
  Serial.println("Button 2 longPress...");

  }
  else{
  Serial.println("Button 2 longPress...");
  up();
  }

} 
void longPressStop2() {
  Serial.println("Button 2 longPress stop");
} 
void click3() {
  Serial.println("Button 2 click.");
  enter();
} 
void doubleclick3() {
  Serial.println("Button 2 doubleclick.");
  enter();
} 
//void longPressStart3() {
//  Serial.println("Button 2 longPress start");
//} 
//void longPress3() {
//  Serial.println("Button 2 longPress...");
//  enter();
//}
//void longPressStop3() {
//  Serial.println("Button 2 longPress stop");
//}
void ISR_1(){
  button1.tick();
}
void ISR_2(){
  button2.tick();
}
void ISR_3(){
  button3.tick();
}

// Initialize screen
void Startup(){
  Serial.begin(115200);
//  Serial.begin(115200);
  Serial.begin(115200, SERIAL_8N1, 16,17);
  tft.begin();
  tft.setSwapBytes(true);
  tft.setRotation(1);
}
//Background
void background_display(){
  tft.pushImage(0, 0, 320, 240, background);
}
// Screen Header
void battary(int bat){
  
  if(bat == 5){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battaryfull);
  }
   if(bat == 4){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battary80);
  }
   if(bat == 3){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battary60);
  } if(bat == 2){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battary40);
  } if(bat == 1){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battarylow);
  }

}
void battarycharging(int bat){
  if(bat == 5){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battaryfullcharging);
  }
   if(bat == 4){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battary80charging);
  }
   if(bat == 3){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battary60charging);
  } if(bat == 2){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battary40charging);
  } if(bat == 1){
    tft.pushImage(255, 25, 45, 20, battaryback);
    tft.pushImage(255, 25, 45, 21, battarylowcharging);
  }

}
void headerunderline(){
    tft.drawWideLine(20,55,300,55,2,TFT_CYAN3 , TFT_CYAN3);
}
void footer(){
  tft.drawWideLine(20,215,300,215,2,TFT_CYAN3 , TFT_CYAN3);
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(105,230);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Kaon Kinetic K 51");
}
#include "Screen1.h"
#include "Screen2.h"
#include "Screen3.h"
#include "Screen4.h"
#include "Screen5.h"
#include "Screen6.h"
#include "Screen7.h"
#include "Screen8.h"
#include "Screen9.h"
#include "Screen10.h"
#include "Screen11.h"
#include "Screen12.h"
#include "Screen13.h"
#include "Screen14.h"
#include "Screen15.h"
