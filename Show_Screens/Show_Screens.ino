   //////////////////////////////////////////////////////////////
  //            2.4 inch TFT LCD ST7789 240 x 320             //
 //////////////////////////////////////////////////////////////
 
#include "Screenfunctions.h"
#include <EEPROM.h>

// define the number of bytes you want to access
#define EEPROM_SIZE 50
// 0,1 location are resserved for flow
//

//
//double flow;
double flow;
double calibrate = 0.00;
int runtimehours = 8;
int runtimeminutes = 0;
int timedelayhour = 0;
int timedelayminutes = 0;
int hour = 1,minute  = 1,sec  = 1,day  = 1,month  = 1, year  = 2000;
int updates;


int battarystrength = 0;
int signalstr = 0; 
boolean StartSampaling_yes = false ;
boolean StartSampaling_no = false;
boolean StopSampaling_yes = false ;
boolean StopSampaling_no = false;
boolean timesend = false;
boolean startsamplesend = false;
boolean stopsamplesend = false;
boolean startcalibrate = false;
boolean stopcalibrate = false;


String Displayflow = "15.00"; 
String DisplayBattary = "15.00"; 
String DisplayTemp  =  "50" ,DisplayHumidity = "32" ,DisplayMotion = "76";
String DisplayDate = "",DisplayYear;
String DisplayTime = "";
String DisplayBackPressure = "";
String TemperatureUnits="F",Flowrateunits="L/M",BackPressureUnits = "KPA";
String DisplayVolume="1150",DisplayTimeHours="4:50";
String DisplayErrorMsg,Displaydelaytime;
String FlowDisplay;
int delaytime=100;

int tempunitflag,flowunitflag,bpunitflag,screen15_flag,flowmode;

String StartSamplingSend;
String StopSamplingSend;
String SetTimeandDate;
String StartCalibrationSend;
String StopCalibrationSend;

const unsigned long DisplayInterval = 1000;
unsigned long DisplaypreviousTime = 0;
const unsigned long S14_DisplayInterval = 1000;
unsigned long S14_DisplaypreviousTime = 0;
const unsigned long calDisplayInterval = 500;
unsigned long calDisplaypreviousTime = 0;

double readflow(double f){
  int store1;
  int store2;
  
  double store;
  store1 = EEPROM.read(0);
  store2 = EEPROM.read(1);
   if(store2%5!=0){
    store2 = store2 + 1;
  }
//  Serial.print("store2 "); Serial.println(store2);
  double deci = (double)store2/100;
//  Serial.print("deci "); Serial.println(deci);
//  if(deci%5!=0){
//    deci = deci + 0.01;
//  }
  f = store1 + deci;
  
  Serial.print("Flow from EEPROM: "); Serial.println(f);
  return f;
}
void writeflow(double flow){
    int intpart = (int)flow;
    double decpart = flow - intpart;
    int decpart1;
    decpart1 = decpart * 100;
    Serial.print("deci"); Serial.println(decpart1);
    EEPROM.write(0,intpart);
    EEPROM.write(1,decpart1);
    EEPROM.commit();
    Serial.print("Flow written to EEPROM: "); Serial.println(flow);
}

double readcal(double f){
      int checksign = EEPROM.read(12);
      

  int store1;
  int store2;
  
  double store;
  store1 = EEPROM.read(2);
  store2 = EEPROM.read(3);
//  Serial.print("store2 "); Serial.println(store2);
  double deci = ((double)store2/100);
//  Serial.print("deci "); Serial.println(deci);
  f = store1 + deci;
  if(checksign==0){
      f = 0 - f;
  }
  Serial.print("CAL from EEPROM: "); Serial.println(f);
  return f;
}

void writecal(double flow){
    if(flow<0){
      EEPROM.write(12,0);
    }
    else{
      EEPROM.write(12,1);
    }
    flow = abs(flow);
    int intpart = (int)flow;
    Serial.print("intpart"); Serial.println(intpart);
    double decpart = flow - intpart;
    int decpart1;
    decpart1 = decpart * 100;
//    Serial.print("deci"); Serial.println(decpart1);
    EEPROM.write(2,intpart);
    EEPROM.write(3,decpart1);
    EEPROM.commit();
    Serial.print("CAL written to EEPROM: "); Serial.println(flow);
}
int readruntimehour(int h,int mem){
 
  h = EEPROM.read(mem);

  Serial.print("Flow from EEPROM: "); Serial.println(h);
  return h;
}
void writeruntimehour(int h,int mem){
    EEPROM.write(mem,h);
    EEPROM.commit();
    Serial.print("Flow written to EEPROM: "); Serial.println(h);
}

//void battarycharging(int battarystrength){
//    if(battarystrength == 120){
//      battarystrength = 20;
//    }
//    battary(battarystrength);
//}
String displaystring(int h,int m){
      String hours;
      String minutes;
      String fulltime;
      if(h < 10){
          Serial.print("runtimehours: "); Serial.println(h);
          hours = String(0) + String(h); 
          Serial.println(hours);
      }
      if(m < 10){
          minutes = "0" + String(m); 
      }
      if(h >= 10){
          hours = String(h); 
      }
      if(m >= 10){
          minutes = String(m); 
      }
      fulltime = hours + ":" + minutes;
      return fulltime;
}
String displaystringsec(int h,int m,int s){
      String hours;
      String minutes;
      String second;
      String fulltime;
      if(h < 10){
          Serial.print("runtimehours: "); Serial.println(h);
          hours = String(0) + String(h); 
          Serial.println(hours);
      }
      if(m < 10){
          minutes = "0" + String(m); 
      }
      if(s < 10){
          second = "0" + String(s); 
      }
      if(h >= 10){
          hours = String(h); 
      }
      if(m >= 10){
          minutes = String(m); 
      }
      if(s >= 10){
          second = String(s); 
      }
      fulltime = hours + ":" + minutes + ":" + second;
      return fulltime;
}
int hour_and_min_to_mins(int hour,int minute){
  if(hour==0){
    return minute;
  }
  else if(hour>0){
    int temphour = hour * 60;
    temphour = temphour+minute;
    return temphour;
  }
  return 0;
}
String min_to_hr_n_min(int minute){
  int hour;
  int hourminute;
  hour = minute / 60;
  hourminute = minute % 60;
  String delaytime = displaystring(hour,hourminute);
  return delaytime;
}
String min_to_hr_n_min_n_sec(int s){
  int hour;
  int hourminute;
  int second;
    
  hour = (s/3600); 
  
  hourminute = (s -(3600*hour))/60;
  
  second = (s -(3600*hour)-(hourminute*60));
  String delaytime = String(hour)+ ":" + String(hourminute) + ":" +String(second);
  return delaytime;
}
int confirmoptionflag = 0, enterflag=0;
void confirmscreen(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(60,120);
  tft.setTextSize(1);
  tft.print("CONFIRM CHANGES");
}
void confirmscreent1(){
   tft.pushImage(80,145,140, 20, s3_yesnoback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(95,160);
  tft.setTextSize(1);
  tft.print("YES");

  tft.fillRoundRect(170,145,45, 20, 1 , TFT_GREY3);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(180,160);
  tft.setTextSize(1);
  tft.print("NO");
}
void confirmscreent2(){
  tft.pushImage(80,145,140, 20, s3_yesnoback);
  tft.fillRoundRect(90,145,45, 20, 1 , TFT_GREY3);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(95,160);
  tft.setTextSize(1);
  tft.print("YES");

  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(180,160);
  tft.setTextSize(1);
  tft.print("NO"); 
}
// d{date},{time},{flow},{temp},{Hum},{Accel} Recieving 
// DisplayScreen_14(String m,String t,String h,String f,String bp,String Tempunit,String bpunit,String flowunit)
void setup()
{
//  delay(5000);
  Startup();
  EEPROM.begin(EEPROM_SIZE);
  flow = readflow(flow);
    Serial.print("Flow ");
      Serial.println(flow);
  calibrate = readcal(calibrate);
//    calibrate = 0.01;
  Serial.print("Calibration");
      Serial.println(calibrate);
//  runtimehours = readruntimehour(runtimehours,4);
//  runtimeminutes = readruntimehour(runtimeminutes,5);
  flowmode = readruntimehour(flowmode,12);
//  flowmode = 1;
  timedelayhour = readruntimehour(timedelayhour,6);
  timedelayminutes = readruntimehour(timedelayminutes,7);
  tempunitflag = readruntimehour(tempunitflag,8);
  flowunitflag = readruntimehour(flowunitflag,9);
  bpunitflag = readruntimehour(bpunitflag,10);
  updates = readruntimehour(updates,11);
//      if(tempunitflag == 0){
//        TemperatureUnits = "C";
//      }
//      if(tempunitflag == 1){
//        TemperatureUnits = "F";
//      }
//      if(tempunitflag == 2){
//        TemperatureUnits = "K";
//      }
      tempunitflag = 0;
      TemperatureUnits = "C";
      if(flowunitflag == 0){
        Flowrateunits = "CC/M";
      }
      if(flowunitflag == 1){
        Flowrateunits = "L/M";
      }
      if(flowunitflag == 2){
        Flowrateunits = "mL/M";
      }
      if(bpunitflag == 0){
        BackPressureUnits = "KPA";
      }
      if(bpunitflag == 1){
        BackPressureUnits = "in.H20";
      }
      if(bpunitflag == 2){
        BackPressureUnits = "cm.H20";
      }

  pinMode(28,INPUT_PULLUP);
  pinMode(27,INPUT_PULLUP);
  pinMode(26,INPUT_PULLUP);
  attachInterrupt(26,ISR_1,CHANGE);
  attachInterrupt(27,ISR_2,CHANGE);
  attachInterrupt(28,ISR_3,CHANGE);
  
  button1.attachClick(click1);
//  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);
  
  button2.attachClick(click2);
//  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);

  button3.attachClick(click3);
//  button3.attachDoubleClick(doubleclick3);
//  button3.attachLongPressStart(longPressStart3);
//  button3.attachLongPressStop(longPressStop3);
//  button3.attachDuringLongPress(longPress3);
  DisplayScreen_1();
  delay(3000);
//  DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow);tempunitflag,flowunitflag,bpunitflag;
}
void loop()
{ 
      button1.tick();
      button2.tick();
      button3.tick();
         if (SerialCustom.available()){
      char st=SerialCustom.read();
      String receivedValues=SerialCustom.readStringUntil('\n');
      Serial.println(receivedValues);
      if (st=='d'){
//        if(Screen4==true  || Screen2 == true){
//          Screen_15R = false;
//        }
//        if(Screen_15R == true){
//           FlowDisplay = flow;
//           if((flow/Displayflow.toDouble())<0.98 || (flow/ Displayflow.toDouble())>1.02)
//           {
//            FlowDisplay = Displayflow;
//           }
//          DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay);
//        }
//        if(Screen15==true || Screen_15R==true || Screen14==true){
//          Screen14 = true;
//        }
//        else{
//          Screen14 = false;
//        }
//        Screen_15R = false;
        
      char charBuf[100];
      receivedValues.toCharArray(charBuf, 100);
      Displayflow = strtok(charBuf, ",");
      DisplayTemp = strtok(NULL, ",");
      DisplayHumidity = strtok(NULL, ",");
      DisplayMotion = strtok(NULL, ",");
      DisplayVolume = strtok(NULL, ",");
      DisplayTimeHours = strtok(NULL, ",");
      DisplayBackPressure = strtok(NULL, "\n");
      DisplayTimeHours = min_to_hr_n_min(DisplayTimeHours.toInt());
//      Serial.println("Values Read");
//      Serial.print("Displayflow "); Serial.println(Displayflow);
//      Serial.print("DisplayTemp "); Serial.println(DisplayTemp);
//      Serial.print("DisplayHumidity "); Serial.println(DisplayHumidity);
//      Serial.print("DisplayMotion "); Serial.println(DisplayMotion);
//      Serial.print("DisplayVolume "); Serial.println(DisplayVolume);
//      Serial.print("DisplayTimeHours "); Serial.println(DisplayTimeHours);
//      Serial.print("DisplayBackPressure "); Serial.println(DisplayBackPressure);

      }
      if (st=='h'){
      char charBuf[100];
      receivedValues.toCharArray(charBuf, 100);
      DisplayDate = strtok(charBuf, ",");
      DisplayYear = strtok(NULL, ",");
      DisplayTime = strtok(NULL, ",");
      DisplayBattary = strtok(NULL, "\n");
//      Serial.println("Date Read");
//      Serial.print("DisplayDate "); Serial.println(DisplayDate);
//      Serial.print("DisplayYear "); Serial.println(DisplayYear);
//      Serial.print("DisplayTime "); Serial.println(DisplayTime);
//      Serial.print("DisplayBattary "); Serial.println(DisplayBattary);
      }
         }
//      if (st=='w'){
////        Screen15 = true;
//        char charBuf[100];
//        receivedValues.toCharArray(charBuf, 100);
//        String Displaydelaytime = strtok(charBuf, "\n");
////        Displaydelaytime = min_to_hr_n_min_n_sec(Displaydelaytime.toInt());
//        int s = Displaydelaytime.toInt();
//        int hour;
//        int hourminute;
//        int second;
//          
//        hour = (s/3600); 
//        
//        hourminute = (s -(3600*hour))/60;
//        
//        second = (s -(3600*hour)-(hourminute*60));
//
////        Serial.print("Displaydelaytime "); Serial.println(Displaydelaytime);
//        if(Screen15 == true){
////        Serial.print("Screen_15DelayUpdate "); Serial.println(Displaydelaytime);
////        Screen_15DelayUpdate(Displaydelaytime);
//          Screen_15DelayUpdate(displaystringsec(hour,hourminute,second));
//
//      }
//    } 
//      if (st=='r'){
//        if(Screen4==true){
//        Screen_15R = false;
//        Screen14 = false;
////        Serial.println("HERE3");
//        }
//        else{
//          Screen14 = false;
//          Screen_15Restart();
//          Screen_15R = true;
////          Serial.println("HERE1");
//        }
//      }
//      if (st=='s'){
//          Screen14 = false;
//          Screen2 = true;
////          delay(100);
//          Screen_2T0();
//          Screen_2T1();
//          transition = 0;
//      }
//      if (st=='e'){
//         Screen14 = false;
//         Screen_15R = false;
//        char charBuf[100];
//        receivedValues.toCharArray(charBuf, 100);
//        DisplayErrorMsg = strtok(charBuf, ",");
//        Screen_15Error(DisplayErrorMsg);
//        Screen15error=true;
//        if(Screen15error == true && Screen4==true){
//        Screen15error = false;
//      }
//      }
//      if(timesend==true){
//         timesend=false;
//         SetTimeandDate = "t" + String(year) + "," + String(month) + "," +  String(day) + "," + String(hour) + "," + String(minute);
//        SerialCustom.println(SetTimeandDate);
//                  
//      }
//       if(startsamplesend==true){
//          startsamplesend=false;
//          int runtime = hour_and_min_to_mins(runtimehours,runtimeminutes);
//          int timedelaytime = hour_and_min_to_mins(timedelayhour,timedelayminutes)*60;
//         StartSamplingSend = "a" + String(flow) + "," + String(calibrate) + ","  + String(runtime) + "," + String(timedelaytime) + "," + String(updates);
//         SerialCustom.println(StartSamplingSend);        
//      }
//      if(stopsamplesend==true){
//          stopsamplesend=false;
//          StopSamplingSend = "z";
//         SerialCustom.println(StopSamplingSend);
//      }
//       if(startcalibrate==true){   
//        if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
//        flow = flow / 1000;
//      }
//        unsigned long calDisplaycurrentTime = millis();
//        if (calDisplaycurrentTime - calDisplaypreviousTime >= calDisplayInterval){
//        StartCalibrationSend = "c" + String(flow) + "," + String(calibrate);
//        SerialCustom.println(StartCalibrationSend);
//        calDisplaypreviousTime = calDisplaycurrentTime;
//        if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
//        flow = flow * 1000;
//      }
//    }      
//      }
//       if(stopcalibrate==true){
//        startcalibrate=false;
//        stopcalibrate=false;
//         StopCalibrationSend = "s";
//        SerialCustom.println(StopCalibrationSend);     
//      }
//      }
//      unsigned long DisplaycurrentTime = millis();
//      if (DisplaycurrentTime - DisplaypreviousTime >= DisplayInterval){
//      timendate(DisplayTime,DisplayDate,DisplayYear);
//      battary(DisplayBattary.toInt());
//      
////      battarycharging(battarystrength);
////      battarystrength = battarystrength + 20;
//      DisplaypreviousTime = DisplaycurrentTime;
////      Serial.println(startcalibrate);
//      
//      }
//   
//  if(Screenenter == true &&  Screen15error == true){
//    Screenenter=false;
//    Screen15error=false;
//    Screen2 = true;
//    Screen_2T0();
//    Screen_2T1();
//    transition = 0;
//  }
  // Screen 2
    if(Screen1 == true){
      Screen1 = false;
      Screen2 = true;
      background_display();
      timendate(DisplayTime,DisplayDate,DisplayYear);
      headerunderline();
      footer();
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T1();
      transition = 0;
//      Serial.println("Screen_2T0()");
    }
    if((Screendown == true || Screenup == true) && transition == 0 && Screen2 == true ){
      Screendown = false;
      Screenup = false;
      Screenenter = false;
      Screen_2T1();
//      Serial.print("runtimehours: "); Serial.println(runtimehours);
//      Serial.println("Draw 1");
    }
    if((Screendown == true || Screenup == true) && transition == 1 && Screen2 == true){
      Screendown = false;
      Screenup = false;
      Screenenter = false;
      Screen_2T2();
//      Serial.println("Draw 2");
    }
    if((Screendown == true || Screenup == true) && transition == 2 && Screen2 == true ){
      Screendown = false;
      Screenup = false;
      Screenenter = false;
      Screen_2T3();
//      Serial.println("Draw 3");
    }
    if((Screendown == true || Screenup == true) && transition == 3 && Screen2 == true){
      Screendown = false;
      Screenup = false;
      Screenenter = false;
      Screen_2T4();
//      Serial.println("Draw 4");
    }
    if((Screendown == true || Screenup == true) && transition == 4 && Screen2 == true ){
      Screendown = false;
      Screenup = false;
      Screenenter = false;
      Screen_2T5();
//      Serial.println("Draw 5");
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
//   // Screen 3
///////////////////////////////////////////////////////////////////////////////////////////////////

    // Screen 3TemperatureUnits="",Flowrateunits="",BackPressureUnits = " tempunitflag,flowunitflag,bpunitflag;
      if(Screenenter == true && transition == 0 && Screen2 == true){
      Screenenter = false;
      Screen2 = false;
      Screen3 = true;
        startyesnotransition = 0;
        StartSampaling_no = true;   
        Screen_3STARTSAMPLING(flow,calibrate,runtimehours,runtimeminutes,timedelayhour,timedelayminutes,updates,"20:10 12-12-23");
        Screen_3T1();
        Serial.println("Screen_3");
      }
      if(Screenup == true && Screen3 == true){
      Screenup = false;
      if(startyesnotransition==1){
      StartSampaling_yes = false;
      StartSampaling_no = true;
      Screen_3T1();
      startyesnotransition = 0;
      }
      else{
      StartSampaling_yes = true;
      StartSampaling_no = false;
      Screen_3T2();
      startyesnotransition = 1;
      }
      Serial.println("Screen_3start");
      }
      if(Screendown == true && Screen3 == true){
        Screendown = false;
        if(startyesnotransition==0){
          StartSampaling_yes = true;
          StartSampaling_no = false;
          Screen_3T2();
          startyesnotransition = 1;
        }
        else{
          StartSampaling_yes = false;
          StartSampaling_no = true;
          Screen_3T1();
          startyesnotransition = 0;
        }  
      Serial.println("Screen_3reset");
      }
      if(Screenenter == true && Screen3 == true && startyesnotransition == 1){
      Screenenter = false;
      Screen3 = false;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T1();
      transition = 0;
      Serial.println("Screen_3to14");
      }
      if(Screenenter == true && Screen3 == true && startyesnotransition == 0){
      Screenenter = false;
      Screen3 = false;
      Screen14 = true;
      DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay,flowmode);

      Serial.println("Screen_3Reset");
      }
      if(Screenenter == true && Screen14 == true){
      Screenenter = false;
      Screen14 = false;
      Screen15 = true;
      Screen_15T1();
      screen15_flag = 0;
      Serial.println("Screen_3to14");
      }

    //
    if(Screendown == true && Screen15 == true){
      Screendown = false;
      if(screen15_flag == 0){
        Screen_15T2();
        screen15_flag = 1;
      }
      else if(screen15_flag == 1){
        Screen_15T3();
        screen15_flag = 2;
      }
      else if(screen15_flag == 2){
        Screen_15T1();
        screen15_flag = 0;
      }
//      Serial.println("Screen_11tempunitsoptionT2");
    }
     if(Screenup == true && Screen15 == true){
      Screenup = false;
      if(screen15_flag == 0){
        Screen_15T3();
        screen15_flag = 2;
      }
      else if(screen15_flag == 1){
        Screen_15T1();
        screen15_flag = 0;
      }
      else if(screen15_flag == 2){
        Screen_15T2();
        screen15_flag = 1;
      }
//      Serial.println("Screen_15T1");
    }
    if(Screenenter == true && Screen15 == true && screen15_flag == 0){
      Screenenter = false;
      Screen15 = false;
      screen15_flag = 0;
      Screen14 = true;
      DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay,flowmode);
      pausedscreen();
    } 
    if(Screenenter == true && Screen15 == true && screen15_flag == 1){
      Screenenter = false;
      Screen15 = false;
      screen15_flag = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T2();
      transition = 1;
    }
    if(Screenenter == true && Screen15 == true && screen15_flag == 2){
      Screenenter = false;
      Screen15 = false;
      screen15_flag = 0;
      Screen14 = true;
      DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay,flowmode);
    }     
      
///////////////////////////////////////////////////////////////////////////////////////////////////
//   // Screen 5
///////////////////////////////////////////////////////////////////////////////////////////////////

      if(Screenenter == true && transition == 1 && Screen2 == true){
      Screenenter = false;
      Screen2 = false;
      Screen5 = true;
      flow = readflow(flow);
      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
      flow = flow * 1000;
      flow = constrain(flow, 5000, 10000);
      }
      else{
      flow = constrain(flow, 5.00, 10.00);
      } 
      if(flowmode == 0){
         Screen_5Setflow(Flowrateunits);
      }
      if(flowmode == 1){
         Screen_5SetPressure(Flowrateunits);
      }
      if(flowmode == 2){
         Screen_5Setflow(Flowrateunits);
      }
      
//      Screen_5Setflow(Flowrateunits);
      Screen_5Setflowvalue(flow,Flowrateunits);
      Serial.println("Screen_5Flow");
      }
      if(Screenup == true && Screen5 == true){
      Screenup = false;
      if(Flowrateunits[0]=='L'){
      flow = flow + 0.05;
      flow = constrain(flow, 5.00, 10.00);
      }
      else if(Flowrateunits[0]=='C' || Flowrateunits[0] == 'm'){
      flow = flow + 50;
      flow = constrain(flow, 5000, 10000);
      }
      Screen_5Setflowvalue(flow,Flowrateunits);
      //        Screen_3T2();
      Serial.println("Screen_5up");
      }
      if(Screendown == true && Screen5 == true){
      Screendown = false;
      if(Flowrateunits[0]=='L'){
      flow = flow - 0.05;
      flow = constrain(flow, 5.00, 10.00);
      }
      else if(Flowrateunits[0]=='C' || Flowrateunits[0] == 'm'){
      flow = flow - 50;
      flow = constrain(flow, 5000, 10000);
      }
      Screen_5Setflowvalue(flow,Flowrateunits);
      //        Screen_3T1();
      Serial.println("Screen_5down");
      }
      if(Screenenter == true && Screen5 == true){
      Screenenter = false;
      Screen5 = false;
      Screen5_1 = true;
      // Screen2 = true;
      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
      flow = flow / 1000;
      }
      writeflow(flow);
      
      Screen_5SelectT1();
      // Screen_2T0();
      // Screen_2T1();
      //      Screen_5PERMISSIONCALIBRATE();
      //      Screen_5PERMISSIONCALIBRATET1();
      flowyesnotransition = 0;
      PERMISSIONCALIBRATE_no = true;
      // transition = 0;
      
      //      Serial.println("Screen_5PERMISSIONCALIBRATET1");
      }
      if(Screenup == true && Screen5_1 == true ){ //&& PERMISSIONCALIBRATE_no == true
      Screenup = false;
      if(flowyesnotransition==1){
      PERMISSIONCALIBRATE_no = true;
      PERMISSIONCALIBRATE_yes = false;
      Screen_5SelectT1();
      flowyesnotransition = 0;
      }
      else{
      PERMISSIONCALIBRATE_yes = true;
      PERMISSIONCALIBRATE_no = false;
      Screen_5SelectT2();
      flowyesnotransition = 1;
      }
      //      Serial.println("Screen_5PERMISSIONCALIBRATET2");
      }
      if(Screendown == true && Screen5_1 == true ){ //&& PERMISSIONCALIBRATE_yes == true
      Screendown = false;
      if(flowyesnotransition==0){
      PERMISSIONCALIBRATE_yes = true;
      PERMISSIONCALIBRATE_no = false;
      Screen_5SelectT2();
      flowyesnotransition = 1;
      }
      else{
      PERMISSIONCALIBRATE_no = true;
      PERMISSIONCALIBRATE_yes = false;
      Screen_5SelectT1();
      flowyesnotransition = 0;
      }
      //      Serial.println("Screen_5PERMISSIONCALIBRATET1");
      }
      if(Screenenter == true && Screen5_1 == true  && PERMISSIONCALIBRATE_no == true){
      Screenenter = false;
      Screen5_1 = false;
      PERMISSIONCALIBRATE_no = false;
      PERMISSIONCALIBRATE_yes = false;
      flowyesnotransition = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T2();
      transition = 1;
      //        Screen7from3_2_1 = true;
      //        Screen7 = true;
      //        Screen_3STARTSAMPLING();
      //        Screen_3T1();
      //        StartSampaling_no = true;
      //        Screen3_2 = true;
      //        PERMISSIONRUNTIME_yes = false;
      //        PERMISSIONCALIBRATE_yes = false;
      //        Screen_5PERMISSIONRUNTIME();
      //        Screen_5PERMISSIONRUNTIMET1();
      //        yesnotransition = 0;
      //        PERMISSIONRUNTIME_no = true;
      //      Serial.println("Screen_5PERMISSIONCALIBRATET1");
      }
      if(Screenenter == true && Screen5_1 == true && PERMISSIONCALIBRATE_yes == true){
      Screenenter = false;
      Screen5_1 = false;
      PERMISSIONCALIBRATE_no = false;
      PERMISSIONCALIBRATE_yes = false;
      flowyesnotransition = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T2();
      transition = 1;
      //      Screen3_1_1 = true;
      //      PERMISSIONCALIBRATE_no = false;
      //      PERMISSIONCALIBRATE_yes = false;
      //      Screen_6Calibrate();
      //      startcalibrate = true;
      //      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
      //        flow = flow * 1000;
      //      }
      //      calibrate = constrain(calibrate, -10.00, 10.00);
      //      Screen_5Setflowvalue(flow,Flowrateunits);
      //      Serial.print("Calibration");
      //      Serial.println(calibrate);
      // Screen_5Setflow();
      // Screen_5Setflowvalue(flow);
      //      Serial.println("Screen_5_0");
      }
//    if(Screenup == true && Screen3_1_1 == true){
//      Screenup = false;
//      calibrate = calibrate + 0.01;
//      calibrate = constrain(calibrate, -10.00, 10.00);
////      Serial.println(calibrate);
////      startcalibrate==true;
//    }
//    if(Screendown == true && Screen3_1_1 == true){
//      Screendown = false;
//      calibrate = calibrate - 0.01;
//      calibrate = constrain(calibrate, -10.00, 10.00);
////      Serial.println(calibrate);
////      startcalibrate==true;
//    }
//    if(Screenenter == true && Screen3_1_1 == true){
//      Screenenter = false;
//      Screen3_1 = false;
//      Screen3_2 = true;
//      Screen3_1_1 = false;
//      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
//        flow = flow / 1000;
//      }
//      stopcalibrate = true;
//      startcalibrate = false;
//      writecal(calibrate);
//      PERMISSIONRUNTIME_yes = false;
//      PERMISSIONCALIBRATE_yes = false;
//      Screen_5PERMISSIONRUNTIME();
//      Screen_5PERMISSIONRUNTIMET1();
//      yesnotransition = 0;
//      PERMISSIONRUNTIME_no = true;
////      Serial.println("Screen_2T0");
//    }
//    if(Screenup == true && Screen3_2 == true){
//      Screenup = false;
//      if(yesnotransition==0){
//        PERMISSIONRUNTIME_yes = true;
//        PERMISSIONRUNTIME_no = false;
//        Screen_5PERMISSIONRUNTIMET2();
//        yesnotransition = 1;
//      }
//      else{
//        PERMISSIONRUNTIME_yes = false;
//      PERMISSIONRUNTIME_no = true;
//     Screen_5PERMISSIONRUNTIMET1();
//        yesnotransition = 0;
//      }
////      Serial.println("Screen_5PERMISSIONRUNTIMET2");
//    }
//    if(Screendown == true && Screen3_2 == true){
//      Screendown = false;
//      if(yesnotransition==1){
//        PERMISSIONRUNTIME_yes = false;
//      PERMISSIONRUNTIME_no = true;
//     Screen_5PERMISSIONRUNTIMET1();
//      yesnotransition = 0;
//      }
//      else{
//        PERMISSIONRUNTIME_yes = true;
//        PERMISSIONRUNTIME_no = false;
//        Screen_5PERMISSIONRUNTIMET2();
//        yesnotransition = 1;
//      }
////      Serial.println("Screen_5PERMISSIONRUNTIMET1");
//    }
//    if(Screenenter == true && Screen3_2 == true  && PERMISSIONRUNTIME_no == true){
//      Screenenter = false;
//      Screen3_2 = false;
//      Screen3_2_1 = false;
//      PERMISSIONCALIBRATE_no = false;
////      Screen2 = true;
////      Screen_2T0();
////      Screen_2T1();
////      transition = 0;
//        Screen7from3_2_1 = true;
//        Screen7 = true;
//        Screen_3STARTSAMPLING();
//        Screen_3T1();
//        StartSampaling_no = true;
////      Serial.println("Screen_5PERMISSIONRUNTIMET1");
//    }
//     if(Screenenter == true && Screen3_2 == true && PERMISSIONRUNTIME_yes == true){
//      Screenenter = false;
//      Screen2 = false;
//       Screen3_2 = false;
//      Screen3_2_1 = true;
//      PERMISSIONRUNTIME_yes = false;
//      Screen_7Runtime();
//      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
////      Serial.println("Screen_7_0");
//    }
//    if(Screenup == true && Screen3_2_1 == true){
//      Screenup = false;
//      runtimeminutes = runtimeminutes + 1;
//      if(runtimeminutes == 60){
//        runtimehours = runtimehours + 1;
//         runtimeminutes = 0;
//        if(runtimehours == 24){
//          runtimehours = 0;
//         }
//      }
//      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
////      Serial.println("Screen_7yes");
//    }
//    if(Screendown == true && Screen3_2_1 == true){
//      Screendown = false;
//       runtimeminutes = runtimeminutes - 1;
//      if(runtimeminutes == -1){
//        runtimehours = runtimehours - 1;
//        runtimeminutes = 59;
//         if(runtimehours == -1){
//          runtimehours = 0;
//          runtimeminutes = 0;
//         }
//        
//      }
//      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
////      Serial.println("Screen_7no");
//    }
//    if(Screenenter == true && Screen3_2_1 == true){
//      Screenenter = false;
//      Screen3_2_1 = false;
////      Screen2 = true;
//      PERMISSIONCALIBRATE_yes = false;
////      writeruntimehour(runtimehours,4);
////      writeruntimehour(runtimeminutes,5);
//      Screenenter = false;
//      Screen2 = false;
//      Screen7from3_2_1 = true;
//      Screen7 = true;
//      Screen_3STARTSAMPLING();
//      Screen_3T1();
//      StartSampaling_no = true;
////      Serial.println("Screen_2T0");
//    }

///////////////////////////////////////////////////////////////////////////////////////////////////
//   // Screen 6
///////////////////////////////////////////////////////////////////////////////////////////////////

   if(Screenenter == true && transition == 2 && Screen2 == true){
      Screenenter = false;
      Screen2 = false;
      Screen6 = true;
      startcalibrate = true;
       if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
        flow = flow * 1000;
      }
      calibrate = constrain(calibrate, -10.00, 10.00);
      Screen_6Calibrate();
      Screen_5Setflowvalue(flow,Flowrateunits);
      Serial.print("Calibration");
      Serial.println(calibrate);
      // Screen_5Setflow();
      // Screen_5Setflowvalue(flow);
//      Serial.println("Screen_5_0");
    }
    if(Screenup == true && Screen6 == true){
      Screenup = false;
      calibrate = calibrate + 0.01;
      calibrate = constrain(calibrate, -10.00, 10.00);
//      Serial.println("Screen_6yes");
//      startcalibrate==true;
    }
    if(Screendown == true && Screen6 == true){
      Screendown = false;
      calibrate = calibrate - 0.01;
      calibrate = constrain(calibrate, -10.00, 10.00);
//      Serial.println("Screen_6no");
//        startcalibrate==true;
    }
    if(Screenenter == true && Screen6 == true){
      Screenenter = false;
      Screen6 = false;
      Screen6_1 = true;
//      Screen2 = true;
      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
        flow = flow / 1000;
      }
//      enterflag=0;
//      confirmscreen(Screenenter,Screenup,Screendown,"H",enterflag);
//      confirmscreen();
      Screen_5SelectT1();
      flowyesnotransition = 0;
      PERMISSIONCALIBRATE_no = true;
      PERMISSIONCALIBRATE_yes = false;
//      confirmyesnotransition = 0;
//      writecal(calibrate);
//      Screen_2T0();
//      Screen_2T2();
//      stopcalibrate = true;
//      transition = 1;
      Serial.println("Screen_6_1");
    }
  if(Screenup == true && Screen6_1 == true ){ //&& PERMISSIONCALIBRATE_no == true
      Screenup = false;
       if(flowyesnotransition==1){
        PERMISSIONCALIBRATE_no = true;
        PERMISSIONCALIBRATE_yes = false;
        Screen_5SelectT1();
        flowyesnotransition = 0;
      }
      else{
        PERMISSIONCALIBRATE_yes = true;
      PERMISSIONCALIBRATE_no = false;
      Screen_5SelectT2();
        flowyesnotransition = 1;
      }
      Serial.println("Screen_6_1_con");
//      Serial.println("Screen_5PERMISSIONCALIBRATET2");
    }
    if(Screendown == true && Screen6_1 == true ){ //&& PERMISSIONCALIBRATE_yes == true
      Screendown = false;
      if(flowyesnotransition==0){
        PERMISSIONCALIBRATE_yes = true;
      PERMISSIONCALIBRATE_no = false;
      Screen_5SelectT2();
      flowyesnotransition = 1;
      }
      else{
        PERMISSIONCALIBRATE_no = true;
        PERMISSIONCALIBRATE_yes = false;
        Screen_5SelectT1();
        flowyesnotransition = 0;
      }
      Serial.println("Screen_6_1_back");
//      Serial.println("Screen_5PERMISSIONCALIBRATET1");
    }

    if(Screenenter == true && Screen6_1 == true  && PERMISSIONCALIBRATE_no == true){
      Screenenter = false;
      Screen6_1 = false;
      PERMISSIONCALIBRATE_no = false;
      PERMISSIONCALIBRATE_yes = false;
      flowyesnotransition = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T3();
      transition = 2;
//        Screen7from3_2_1 = true;
//        Screen7 = true;
//        Screen_3STARTSAMPLING();
//        Screen_3T1();
//        StartSampaling_no = true;
//        Screen3_2 = true;
//        PERMISSIONRUNTIME_yes = false;
//        PERMISSIONCALIBRATE_yes = false;
//        Screen_5PERMISSIONRUNTIME();
//        Screen_5PERMISSIONRUNTIMET1();
//        yesnotransition = 0;
//        PERMISSIONRUNTIME_no = true;
//      Serial.println("Screen_5PERMISSIONCALIBRATET1");
    }
    if(Screenenter == true && Screen6_1 == true && PERMISSIONCALIBRATE_yes == true){
      Screenenter = false;
      Screen6_1 = false;
      PERMISSIONCALIBRATE_no = false;
      PERMISSIONCALIBRATE_yes = false;
      flowyesnotransition = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T3();
      transition = 2;
//      Screen3_1_1 = true;
//      PERMISSIONCALIBRATE_no = false;
//      PERMISSIONCALIBRATE_yes = false;
//      Screen_6Calibrate();
//      startcalibrate = true;
//      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
//        flow = flow * 1000;
//      }
//      calibrate = constrain(calibrate, -10.00, 10.00);
//      Screen_5Setflowvalue(flow,Flowrateunits);
//      Serial.print("Calibration");
//      Serial.println(calibrate);
      // Screen_5Setflow();
      // Screen_5Setflowvalue(flow);
//      Serial.println("Screen_5_0");
    }
    
///////////////////////////////////////////////////////////////////////////////////////////////////
//   // Screen 7
///////////////////////////////////////////////////////////////////////////////////////////////////

   if(Screenenter == true && transition == 3 && Screen2 == true){
      Screenenter = false;
      Screen2 = false;
      Screen7 = true;
      Screen_7Runtime();
      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
      // Screen_5Setflow();
      // Screen_5Setflowvalue(flow);
      Serial.println("Screen_7");
    }
    if(Screenup == true && Screen7 == true){
      Screenup = false;
      runtimeminutes = runtimeminutes + 1;
      if(runtimeminutes == 60){
        runtimehours = runtimehours + 1;
         runtimeminutes = 0;
        if(runtimehours == 24){
          runtimehours = 0;
         }
      }
      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
      Serial.println("Screen_7up");
//      startcalibrate==true;
    }
    if(Screendown == true && Screen7 == true){
      Screendown = false;
      runtimeminutes = runtimeminutes - 1;
      if(runtimeminutes == -1){
      runtimehours = runtimehours - 1;
      runtimeminutes = 59;
       if(runtimehours == -1){
        runtimehours = 0;
        runtimeminutes = 0;
       }
      
      }
      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
      Serial.println("Screen_7down");
//        startcalibrate==true;
    }
    if(Screenenter == true && Screen7 == true){
      Screenenter = false;
      Screen7 = false;
      Screen7_1 = true;
//      Screen2 = true;
//      enterflag=0;
//      confirmscreen(Screenenter,Screenup,Screendown,"H",enterflag);
//      confirmscreen();
      Screen_5SelectT1();
      flowyesnotransition = 0;
      PERMISSIONCALIBRATE_no = true;
      PERMISSIONCALIBRATE_yes = false;
//      confirmyesnotransition = 0;
//      writecal(calibrate);
//      Screen_2T0();
//      Screen_2T2();
//      stopcalibrate = true;
//      transition = 1;
      Serial.println("Screen_7_1");
    }
  if(Screenup == true && Screen7_1 == true ){ //&& PERMISSIONCALIBRATE_no == true
      Screenup = false;
       if(flowyesnotransition==1){
        PERMISSIONCALIBRATE_no = true;
        PERMISSIONCALIBRATE_yes = false;
        Screen_5SelectT1();
        flowyesnotransition = 0;
      }
      else{
        PERMISSIONCALIBRATE_yes = true;
      PERMISSIONCALIBRATE_no = false;
      Screen_5SelectT2();
        flowyesnotransition = 1;
      }
      Serial.println("Screen_7_1_con");
//      Serial.println("Screen_5PERMISSIONCALIBRATET2");
    }
    if(Screendown == true && Screen7_1 == true ){ //&& PERMISSIONCALIBRATE_yes == true
      Screendown = false;
      if(flowyesnotransition==0){
        PERMISSIONCALIBRATE_yes = true;
      PERMISSIONCALIBRATE_no = false;
      Screen_5SelectT2();
      flowyesnotransition = 1;
      }
      else{
        PERMISSIONCALIBRATE_no = true;
        PERMISSIONCALIBRATE_yes = false;
        Screen_5SelectT1();
        flowyesnotransition = 0;
      }
      Serial.println("Screen_7_1_back");
//      Serial.println("Screen_5PERMISSIONCALIBRATET1");
    }

    if(Screenenter == true && Screen7_1 == true  && PERMISSIONCALIBRATE_no == true){
      Screenenter = false;
      Screen7_1 = false;
      PERMISSIONCALIBRATE_no = false;
      PERMISSIONCALIBRATE_yes = false;
      flowyesnotransition = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T4();
      transition = 3;
//        Screen7from3_2_1 = true;
//        Screen7 = true;
//        Screen_3STARTSAMPLING();
//        Screen_3T1();
//        StartSampaling_no = true;
//        Screen3_2 = true;
//        PERMISSIONRUNTIME_yes = false;
//        PERMISSIONCALIBRATE_yes = false;
//        Screen_5PERMISSIONRUNTIME();
//        Screen_5PERMISSIONRUNTIMET1();
//        yesnotransition = 0;
//        PERMISSIONRUNTIME_no = true;
//      Serial.println("Screen_5PERMISSIONCALIBRATET1");
    }
    if(Screenenter == true && Screen7_1 == true && PERMISSIONCALIBRATE_yes == true){
      Screenenter = false;
      Screen7_1 = false;
      PERMISSIONCALIBRATE_no = false;
      PERMISSIONCALIBRATE_yes = false;
      flowyesnotransition = 0;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T4();
      transition = 3;
//      Screen3_1_1 = true;
//      PERMISSIONCALIBRATE_no = false;
//      PERMISSIONCALIBRATE_yes = false;
//      Screen_6Calibrate();
//      startcalibrate = true;
//      if(Flowrateunits[0] == 'C' || Flowrateunits[0] == 'm'){
//        flow = flow * 1000;
//      }
//      calibrate = constrain(calibrate, -10.00, 10.00);
//      Screen_5Setflowvalue(flow,Flowrateunits);
//      Serial.print("Calibration");
//      Serial.println(calibrate);
      // Screen_5Setflow();
      // Screen_5Setflowvalue(flow);
//      Serial.println("Screen_5_0");
    }

//     if(Screenup == true && Screen6_1 == true){
//      Screenup = false;
//      if(confirmyesnotransition==1){
//        Screen_5SelectT1();
//        confirmyesnotransition = 0;
////        stopcalibrate = true;
//      }
//      else{
//        Screen_5SelectT2();
//        confirmyesnotransition = 1;
//      }
//      
//      Serial.println("Screen_3yes");
//    }
//    if(Screendown == true && Screen6_1 == true){
//      Screendown = false;
//      if(confirmyesnotransition==0){
//        Screen_5SelectT2();
//        confirmyesnotransition = 1;
//      }
//      else{
//        Screen_5SelectT1();
//        confirmyesnotransition = 0;
////        stopcalibrate = true;
//      }
//      
//      Serial.println("Screen_3no");
//    }

//    if(Screenenter == true && Screen6_1 == true && confirmyesnotransition == 0){
//      Screenenter = false;
//      Screen6_1 = false;
//      Screen2 = true;
//      confirmyesnotransition = 0;
//      Screen_2T0();
//      Screen_2T3();
////      stopcalibrate = true;
//      transition = 2;
////      Serial.println("Screen_2T0");
//    }
//    if(Screenenter == true && Screen5_1 == true && confirmyesnotransition == 1){
//      Screenenter = false;
//      Screen5_1 = false;
//      Screen2 = true;
//      confirmyesnotransition = 0;
//      writecal(calibrate);
//      Screen_2T0();
//      Screen_2T3();
////      stopcalibrate = true;
//      transition = 2;
////      Serial.println("Screen_2T0");
//    }
//  // Screen 6 
//    if(Screenenter == true && transition == 2 && Screen2 == true){
//      Screenenter = false;
//      Screen2 = false;
//      Screen6 = true;
//      Screen_7Runtime();
//      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
////      Serial.println("Screen_7_0");
//    }
//    if(Screenup == true && Screen6 == true){
//      Screenup = false;
//      runtimeminutes = runtimeminutes + 1;
//      if(runtimeminutes == 60){
//        runtimehours = runtimehours + 1;
//         runtimeminutes = 0;
//        if(runtimehours == 24){
//          runtimehours = 0;
//         }
//      }
//      Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
////      Serial.println("Screen_7yes");
//    }
//    if(Screendown == true && Screen6 == true){
//      Screendown = false;
//       runtimeminutes = runtimeminutes - 1;
//      if(runtimeminutes == -1){
//        runtimehours = runtimehours - 1;
//        runtimeminutes = 59;
//         if(runtimehours == -1){
//          runtimehours = 0;
//          runtimeminutes = 0;
//         }
//      }
//    Screen_7SetRuntime(displaystring(runtimehours,runtimeminutes));
//    }
//    if(Screenenter == true && Screen6 == true){
//      Screenenter = false;
//      Screen6 = false;
//      Screen6_1 = true;
////      Screen2 = true;
////      writeruntimehour(runtimehours,4);
////      writeruntimehour(runtimeminutes,5);
////      Screen_2T0();
////      Screen_2T3();
////      transition = 2;
//      confirmscreen();
//      confirmscreent1();
//      confirmyesnotransition = 0;
////      Serial.println("Screen_2T0");
//    }
//     if(Screenup == true && Screen6_1 == true){
//      Screenup = false;
//      if(confirmyesnotransition==1){
//        confirmscreent1();
//        confirmyesnotransition = 0;
//      }
//      else{
//        confirmscreent2();
//        confirmyesnotransition = 1;
//      }
//      
////      Serial.println("Screen_3yes");
//    }
//    if(Screendown == true && Screen6_1 == true){
//      Screendown = false;
//      if(confirmyesnotransition==0){
//        confirmscreent2();
//        confirmyesnotransition = 1;
//      }
//      else{
//        confirmscreent1();
//        confirmyesnotransition = 0;
//      }
//      
////      Serial.println("Screen_3no");
//    }
//    if(Screenenter == true && Screen6_1 == true && confirmyesnotransition == 0){
//      Screenenter = false;
//      confirmyesnotransition=0;
//      runtimehours =8;
//      runtimeminutes =0; 
//      Screen6_1 = false;
//      Screen2 = true;
//      Screen_2T0();
//      Screen_2T3();
//      transition = 2;
////      Serial.println("Screen_2T0");
//    }
//    if(Screenenter == true && Screen6_1 == true && confirmyesnotransition == 1){
//      Screenenter = false;
//      Screen6_1 = false;
//      Screen2 = true;
//      confirmyesnotransition=0;
//      Screen_2T0();
//      Screen_2T3();
//      transition = 2;
////      Serial.println("Screen_2T0");
//    }
//    // Screen 7 
//    if(Screenenter == true && transition == 3 && Screen2 == true){
//      Screenenter = false;
//      Screen2 = false;
//      Screen7 = true;
//      Screen_3STARTSAMPLING();
//      Screen_3T1();
//      startyesnotransition = 0;
//      StartSampaling_no = true;                                                                 //here
////      Serial.println("Screen_6_0");
//    }
//    if(Screenup == true && Screen7 == true){
//      Screenup = false;
//      if(startyesnotransition==1){
//        StartSampaling_yes = false;
//        StartSampaling_no = true;
//        Screen_3T1();
//        startyesnotransition = 0;
//      }
//      else{
//        StartSampaling_yes = true;
//        StartSampaling_no = false;
//        Screen_3T2();
//        startyesnotransition = 1;
//      }
//      
////      Serial.println("Screen_3yes");
//    }
//    if(Screendown == true && Screen7 == true){
//      Screendown = false;
//      if(startyesnotransition==0){
//        StartSampaling_yes = true;
//        StartSampaling_no = false;
//        Screen_3T2();
//        startyesnotransition = 1;
//      }
//      else{
//        StartSampaling_yes = false;
//        StartSampaling_no = true;
//        Screen_3T1();
//        startyesnotransition = 0;
//      }
//      
////      Serial.println("Screen_3no");
//    }
//     if(Screenenter == true && Screen7from3_2_1 == true  && StartSampaling_no == true){
//      Screenenter = false;
//      Screen7from3_2_1 = false;
//      Screen7 = false;
//      StartSampaling_no = false;
//      Screen2 = true;
//      Screen_2T0();
//      Screen_2T4();
//      transition = 3;
////      Serial.println("Screen_2T0");
//    }
//    if(Screenenter == true && Screen7 == true  && StartSampaling_no == true && Screen7from3_2_1 == false){
//      Screenenter = false;
//      Screen7 = false;
//      StartSampaling_no = false;
//      Screen2 = true;
//      Screen_2T0();
//      Screen_2T4();
//      transition = 3;
////      Serial.println("Screen_2T0");
//    }
//    if(Screenenter == true && Screen7 == true && StartSampaling_yes == true){
//      Screenenter = false;
//      Screen7 = false;
//       Screen2 = false;
//      StartSampaling_yes = false;
//      Screen15 = true;
//      Screen14 = false;
//      startsamplesend = true;
//      FlowDisplay = "0:00";
//      int sec = 0;
//      if(timedelayminutes==0){
//        sec = 5;
//      }
//      Screen_15DelayScreen(displaystringsec(timedelayhour,timedelayminutes,sec));
////      Screen_15DelayScreen("00:00:00");
////      Serial.print("Screen_15DelayScreen "); Serial.println(Displaydelaytime);
//      
////      delay(5000);
////      
////      Serial.println("Screen_2T0");
//    }
//    if(Screen14 == true && Screen15 == true){
//      if(Displayflow.toDouble())
//           FlowDisplay = flow;
//           if((flow/Displayflow.toDouble())<0.98 || (flow/ Displayflow.toDouble())>1.02)
//           {
//            FlowDisplay = Displayflow;
//           }
//      DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay);
//    }
//    if(Screenenter == true && Screen15 == true){
//      Screenenter = false;
//      Screen7 = false;
//      Screen15 = false;
//      Screen15_1 = true;
//      Screen4 = true;
//      Screen_4STOPSAMPLING();
//      Screen_4T1();
//      stopyesnotransition = 0;
//      StopSampaling_no = true;
////      Serial.println("Screen_2T0");
//    }
//     if(Screenenter == true && Screen14 == true){
//      Screenenter = false;
//      Screen7 = false;
//      Screen14 = false;
//      Screen4 = true;
//      Screen_4STOPSAMPLING();
//      Screen_4T1();
//      stopyesnotransition = 0;
//      StopSampaling_no = true;
////      Serial.println("Screen_2T0");
//    }
//    if(Screenenter==true && Screen_15R == true){
//        Screen_15R = false;
//        Screen14 = false;
//        Screen15 = false;
////        Screen15_1 = false;
//        Screen_15R = false;
//        Screen4=true;
//        Screen_4STOPSAMPLING();
//        Screen_4T1();
//        stopyesnotransition = 0;
//        StopSampaling_no = true;
//        Serial.println("HERE2");
//      }
//    if(Screen14 == true){
//      Screen15 = false;
//      unsigned long S14_DisplaycurrentTime = millis();
//      if (S14_DisplaycurrentTime - S14_DisplaypreviousTime >= S14_DisplayInterval){
//           FlowDisplay = flow;
//           if((flow/Displayflow.toDouble())<0.98 || (flow/ Displayflow.toDouble())>1.02)
//           {
//            FlowDisplay = Displayflow;
//           }
//      DisplayScreen_14_Update(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay);
////      Serial.print("...Updating after "); Serial.println(S14_DisplayInterval);
//      timendate(DisplayTime,DisplayDate,DisplayYear);
//    
//    S14_DisplaypreviousTime = S14_DisplaycurrentTime;
//    }
//    }
//    if(Screenup == true && Screen4 == true){
//      Screenup = false;
//      if(stopyesnotransition==1){
//        StopSampaling_yes = false;
//        StopSampaling_no = true;
//        Screen_4T1();
//        stopyesnotransition = 0;
//      }
//      else{
//        StopSampaling_yes = true;
//        StopSampaling_no = false;
//        Screen_4T2();
//        stopyesnotransition = 1;
//      }
//      Serial.println("Screen_3yes");
//    }
//    if(Screendown == true && Screen4 == true){
//      Screendown = false;
//      if(yesnotransition==0){
//        StopSampaling_yes = true;
//        StopSampaling_no = false;
//        Screen_4T2();
//        yesnotransition = 1;
//      }
//      else{
//        StopSampaling_yes = false;
//        StopSampaling_no = true;
//        Screen_4T1();
//        yesnotransition = 0;
//      }
//      
//      Serial.println("Screen_3no");
//    }
//    if(Screenenter == true && Screen4 == true  && StopSampaling_no == true){
//      Screenenter = false;
//      Screen4 = false;
//      Screen7 = false;
//      
//      StopSampaling_no = false;
//      if(Screen15_1==true){
//        Screen15_1=false;
//        Screen15=true;
//        Screen_15DelayScreen(displaystringsec(timedelayhour,timedelayminutes,sec));
//      }
//      else{
//        Screen15_1 = false;
//        Screen14 = true;      
//        FlowDisplay = flow;
//        if((flow/Displayflow.toDouble())<0.98 || (flow/ Displayflow.toDouble())>1.02)
//        {
//        FlowDisplay = Displayflow;
//        }
//        DisplayScreen_14(DisplayMotion,DisplayTemp,DisplayHumidity,Displayflow,DisplayBackPressure,TemperatureUnits,BackPressureUnits,Flowrateunits,DisplayVolume,DisplayTimeHours,flow,FlowDisplay);
//      }
//      Serial.println("Screen_2T0");
//    }
//    if(Screenenter == true && Screen4 == true && StopSampaling_yes == true){
//      Screenenter = false;
//      Screen4 = false;
//      Screen2 = true;
//      Screen7 = false;
//      Screen15_1=false;
//      StopSampaling_yes = false;
//      stopsamplesend=true;
//      Screen_2T0();
//      Screen_2T1();
//      transition = 0;
////      Serial.println("Screen_2T0");
//    }
      // Screen 8
    if(Screenenter == true && transition == 4 && Screen2 == true){
      Screenenter = false;
      Screen1 = false;
      Screen2 = false;
      Screen3 = false;
      Screen4 = false;
      Screen5 = false;
      Screen6 = false;
      Screen7 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T1();
      settings_transition = 0;
//      Serial.println("Screen_8_0");
    }
    if(Screenup == true && settings_transition == 0 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T0();
      Screen_8T1();
//      Serial.println("S Draw 5");
    }
     if(Screendown == true  && settings_transition == 0 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T0();
      Screen_8T1();
//      Serial.println("S Draw 1");
    }
     if(Screenup == true && settings_transition == 1 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T0_1();
      Screen_8T1();
//      Serial.println("S Draw 5");
    }
    if(Screendown == true  && settings_transition == 1 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T2();
//      Serial.println("S Draw 2");
    }
    if(Screenup == true && settings_transition == 2 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T1();
//      Serial.println("S Draw 5");
    }
    if(Screendown == true && settings_transition == 2 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T3();
//      Serial.println("S Draw 3");
    }
     if(Screenup == true && settings_transition == 3 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T2();
//      Serial.println("S Draw 5");
    }
    if(Screendown == true && settings_transition == 3 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T4();
//      Serial.println("S Draw 4");
    }
     if(Screenup == true && settings_transition == 4 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T3();
//      Serial.println("S Draw 5");
    }
    if(Screendown == true && settings_transition == 4 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T5();
//      Serial.println("S Draw 5");
    }
    if(Screenup == true && settings_transition == 5 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T4();
//      Serial.println("S Draw 6");
    }
    
    if(Screendown == true && settings_transition == 5 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T6();
//      Serial.println("S Draw 6");
    }
    if(Screenup == true && settings_transition == 6 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T5();
//      Serial.println("S Draw 6");
    }
    if(Screendown == true  && settings_transition == 6 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T7();
//      Serial.println("S Draw 6");
    }
    if(Screenup == true && settings_transition == 7 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T8();
//      Serial.println("S Draw 6");
    }
    if(Screendown == true  && settings_transition == 7 && Screen8 == true){
      Screendown = false;
      Screenup = false;
      Screen_8T8();
//      Serial.println("S Draw 6");
    }
    
     if(Screenenter == true && settings_transition == 7 && Screen8 == true){
      Screenenter = false;
      Screen8 = false;
      Screen2 = true;
      if(flowmode == 0){
         Screen_2T0("SELECT FLOW RATE");
      }
      if(flowmode == 1){
         Screen_2T0("SET INLET PRESSURE");
      }
      if(flowmode == 2){
         Screen_2T0("SELECT FLOW RATE");
      }
      Screen_2T5();
      transition = 4;
//      Serial.println("Screen_2T0()");
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
//   // Screen 13
/////////////////////////////////////////////////////////////////////////////////////////////////// 

    if(Screenenter == true && settings_transition == 0 && Screen8 == true){
    Screenenter = false;
    Screen8 = false;
    Screen13 = true;
    Screen_13flowmodes();
//          Screen_11Setunits();
      Screen_11SetunitsT1();
      screen11_transition = 0;
      Serial.println("Screen13");
    }
    if((Screenup == true || Screendown == true ) && Screen13 == true && screen11_transition == 0){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT1();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && screen11_transition == 0 && Screen13 == true){
      Screenenter = false;
      Screen13 = false;
      Screen13_1 = true;
      Screen13flowmodeconfirm();
      Screen_3T2no();
//      Screen_13webdataoptionT2();
      webyesnotransition = 0;
      
      Serial.println("Screen_13_1");
    }
    if(Screendown == true && Screen13_1 == true){
      Screendown = false;
      if(webyesnotransition==0){
        Screen_3T1yes();
        webyesnotransition = 1;
      }
      else{
        Screen_3T2no();
        webyesnotransition = 0;
      }
      
//      Serial.println("Screen_12yes");
    }
    if(Screenup == true && Screen13_1 == true){
      Screenup = false;
      if(webyesnotransition==1){
        Screen_3T2no();
        webyesnotransition = 0;
      }
      else{
        Screen_3T1yes();
        webyesnotransition = 1;
      }
//      Serial.println("Screen_12no");
    }
    
    if(Screenenter == true && Screen13_1 == true && webyesnotransition == 1){
      Screenenter = false;
      Screen13_1 = false;
      Screen13 = true;
      Screen_13flowmodes();
//          Screen_11Setunits();
      Screen_11SetunitsT1();
      screen11_transition = 0;
      flowmode = 0;
      writeruntimehour(flowmode,12);
      Serial.println("FLOW MODE");
    }
    if(Screenenter == true && Screen13_1 == true && webyesnotransition == 0){
      Screenenter = false;
      Screen13_1 = false;
      Screen13 = true;
      Screen_13flowmodes();
//          Screen_11Setunits();
      Screen_11SetunitsT1();
      screen11_transition = 0;
//      Serial.println("Screen_2T0");
    }
     if((Screenup == true || Screendown == true ) && Screen13 == true && screen11_transition == 1){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT2();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && screen11_transition == 1 && Screen13 == true){
      Screenenter = false;
      Screen13 = false;
      Screen13_2 = true;
      Screen13pressuremodeconfirm();
      Screen_3T2no();
//      Screen_13webdataoptionT2();
      webyesnotransition = 0;
    Serial.println("Screen_13_2");   

    }
    if(Screendown == true && Screen13_2 == true){
      Screendown = false;
      if(webyesnotransition==0){
        Screen_3T1yes();
        webyesnotransition = 1;
      }
      else{
        Screen_3T2no();
        webyesnotransition = 0;
      }
      
//      Serial.println("Screen_12yes");
    }
    if(Screenup == true && Screen13_2 == true){
      Screenup = false;
      if(webyesnotransition==1){
        Screen_3T2no();
        webyesnotransition = 0;
      }
      else{
        Screen_3T1yes();
        webyesnotransition = 1;
      }
//      Serial.println("Screen_12no");
    }
    
    if(Screenenter == true && Screen13_2 == true && webyesnotransition == 1){
      Screenenter = false;
      Screen13_2 = false;
      Screen13 = true;
      Screen_13flowmodes();
      flowmode = 1;
      writeruntimehour(flowmode,12);
//          Screen_11Setunits();
      Screen_11SetunitsT2();
      screen11_transition = 1;
      Serial.println("FLOW MODE");
    }
    if(Screenenter == true && Screen13_2 == true && webyesnotransition == 0){
      Screenenter = false;
      Screen13_2 = false;
      Screen13 = true;
      Screen_13flowmodes();
//          Screen_11Setunits();
      Screen_11SetunitsT2();
//      screen11_transition = 0;
//      Serial.println("Screen_2T0");
    }
     if((Screenup == true || Screendown == true ) && Screen13 == true && screen11_transition == 2){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT3();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && screen11_transition == 2 && Screen13 == true){
      Screenenter = false;
      Screen13 = false;
      Screen13_3 = true;
      Screen13gasmodeconfirm();
      Screen_3T2no();
//      Screen_13webdataoptionT2();
      webyesnotransition = 0;
      
     Serial.println("Screen_13_3");
    }
    if(Screendown == true && Screen13_3 == true){
      Screendown = false;
      if(webyesnotransition==0){
        Screen_3T1yes();
        webyesnotransition = 1;
      }
      else{
        Screen_3T2no();
        webyesnotransition = 0;
      }
      
//      Serial.println("Screen_12yes");
    }
    if(Screenup == true && Screen13_3 == true){
      Screenup = false;
      if(webyesnotransition==1){
        Screen_3T2no();
        webyesnotransition = 0;
      }
      else{
        Screen_3T1yes();
        webyesnotransition = 1;
      }
//      Serial.println("Screen_12no");
    }
    
    if(Screenenter == true && Screen13_3 == true && webyesnotransition == 1){
      Screenenter = false;
      Screen13_3 = false;
      Screen13 = true;
      Screen_13flowmodes();
      flowmode = 2;
      writeruntimehour(flowmode,12);
//          Screen_11Setunits();
      Screen_11SetunitsT3();
      screen11_transition = 2;
      Serial.println("FLOW MODE");
    }
    if(Screenenter == true && Screen13_3 == true && webyesnotransition == 0){
      Screenenter = false;
      Screen13_3 = false;
      Screen13 = true;
      Screen_13flowmodes();
//          Screen_11Setunits();
      Screen_11SetunitsT3();
      screen11_transition = 2;
//      Serial.println("Screen_2T0");
    }
    
     if((Screenup == true || Screendown == true ) && Screen13 == true && screen11_transition == 3){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT4();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && Screen13 == true && screen11_transition == 3){
      Screenenter = false;
      Screen13 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T1();
      screen11_transition = 0;
//      Serial.println("Screen_8T0");
    }

//////////////////////////////////////////////////////////////////////////////////////    
    // Screen 9
/////////////////////////////////////////////////////////////////////////////////////

      if(Screenenter == true && settings_transition == 1 && Screen8 == true){
      Screenenter = false;
      Screen8 = false;
      Screen9 = true;
      Screen_9Timedelay();
      Screen_7SetRuntime(displaystring(timedelayhour,timedelayminutes));
//      Serial.println("Screen_9_0");
    }
    if(Screenup == true && Screen9 == true){
      Screenup = false;
      timedelayminutes = timedelayminutes + 1;
      if(timedelayminutes == 60){
        timedelayhour = timedelayhour + 1;
         timedelayminutes = 0;
        if(timedelayhour == 24){
          timedelayhour = 0;
         }
      }
      Screen_7SetRuntime(displaystring(timedelayhour,timedelayminutes));
//      Serial.println("Screen_9yes");
    }
    if(Screendown == true && Screen9 == true){
      Screendown = false;
       timedelayminutes = timedelayminutes - 1;
      if(timedelayminutes == -1){
        timedelayhour = timedelayhour - 1;
        timedelayminutes = 59;
         if(timedelayhour == -1){
          timedelayhour = 0;
          timedelayminutes = 0;
         }
        
      }
     Screen_7SetRuntime(displaystring(timedelayhour,timedelayminutes));
//      Serial.println("Screen_7no");
    }
    if(Screenenter == true && Screen9 == true){
      Screenenter = false;
      Screen9 = false;
      Screen9_1 = true;
      confirmscreen();
      confirmscreent1();
      confirmyesnotransition = 0;
//      writeruntimehour(timedelayhour,6);
//      writeruntimehour(timedelayminutes,7);
//      Screen_8T0();
//      Screen_8T1();
//      settings_transition = 0;
//      Serial.println("Screen_8T0");
    }
         if(Screenup == true && Screen9_1 == true){
      Screenup = false;
      if(confirmyesnotransition==1){
        confirmscreent1();
        confirmyesnotransition = 0;
      }
      else{
        confirmscreent2();
        confirmyesnotransition = 1;
      }
      
//      Serial.println("Screen_3yes");
    }
    if(Screendown == true && Screen9_1 == true){
      Screendown = false;
      if(confirmyesnotransition==0){
        confirmscreent2();
        confirmyesnotransition = 1;
      }
      else{
        confirmscreent1();
        confirmyesnotransition = 0;
      }
      
//      Serial.println("Screen_3no");
    }
    if(Screenenter == true && Screen9_1 == true && confirmyesnotransition == 0){
      Screenenter = false;
      timedelayhour = readruntimehour(timedelayhour,6);
      timedelayminutes = readruntimehour(timedelayminutes,7);
      confirmyesnotransition=0;
      Screen9_1 = false;
      Screen9 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T2();
      settings_transition = 1;
//      Serial.println("Screen_2T0");
    }
    if(Screenenter == true && Screen9_1 == true && confirmyesnotransition == 1){
      Screenenter = false;
      Screen9_1 = false;
      Screen9 = false;
      Screen8 = true;
      writeruntimehour(timedelayhour,6);
      writeruntimehour(timedelayminutes,7);
      confirmyesnotransition=0;
      Screen_8T0();
      Screen_8T2();
      settings_transition = 1;
//      Serial.println("Screen_2T0");
    }
    // Screen 10
      if(Screenenter == true && settings_transition == 2 && Screen8 == true){
      td_transition = 1;
      Screenenter = false;
      Screen8 = false;
      Screen10 = true;
      Screen10_h = true;
      Screen_10TnD();
      Screen_10Time();
      hour = constrain(hour, 0, 23);
      minute = constrain(minute, 0, 59);
      day = constrain(day, 1, 31);
      month = constrain(month, 1, 12);
      year = constrain(year, 2000, 2100);
      Screen_10TimevalueT1(hour,minute,sec); //hour,minute,sec,day,month,year
      Screen_10Date();
      Screen_10Datevalue(day,month,year);
//      Serial.println("Screen_10_0");
    }
    if(Screenup == true && Screen10_h == true){
      Screenup = false;
      if(hour == 23){
        hour = 0;
      }
      else{
         hour = hour + 1;
         hour = constrain(hour, 0, 23);
      }
      Screen_10TimevalueT1(hour,minute,sec);
//      Serial.println("Screen_10TimevalueT1");
    }
     if(Screendown == true && Screen10_h == true){
      Screendown = false;
       if(hour == 0){
        hour = 23;
      }
      else{
         hour = hour - 1;
         hour = constrain(hour, 0, 23);
      }
      Screen_10TimevalueT1(hour,minute,sec);
//      Serial.println("Screen_10TimevalueT1");
    }    
    if(Screenenter == true && Screen10_h == true && td_transition == 2){
      Screenenter = false;
      Screen10_h = false;
      Screen10_m = true;
      Screen_10TimevalueT2(hour,minute,sec);
//      Serial.println("Screen_10yes");
    }
     if(Screenup == true && Screen10_m == true){
      Screenup = false;
      if(minute == 59){
        minute = 0;
      }
      else{
        minute = minute + 1;
      minute = constrain(minute, 0, 59);
      }
      Screen_10TimevalueT2(hour,minute,sec);
//      Serial.println("Screen_10TimevalueT1");
    }
     if(Screendown == true && Screen10_m == true){
      Screendown = false;
      if(minute == 0){
        minute = 59;
      }
      else{
        minute = minute - 1;
      minute = constrain(minute, 0, 59);
      }
      Screen_10TimevalueT2(hour,minute,sec);
//      Serial.println("Screen_10TimevalueT1");
    }    
     if(Screenenter == true && Screen10_m == true && td_transition == 3){
      Screenenter = false;
      Screen10_h = false;
      Screen10_m = false;
      Screen10_d = true;
      hour = constrain(hour, 0, 23);
      minute = constrain(minute, 0, 59);
      day = constrain(day, 1, 31);
      month = constrain(month, 1, 12);
      year = constrain(year, 2000, 2100);
      Screen_10Timevalue(hour,minute,sec);
      Screen_10DatevalueT1(day,month,year);
//      Serial.println("Screen_10yes");
    }
     if(Screenup == true && Screen10_d == true){
      Screenup = false;
      if(day == 31){
        day = 1;
      }
      else{
        day = day + 1;
      day = constrain(day, 1, 31);
      }
     Screen_10DatevalueT1(day,month,year);
//      Serial.println("Screen_10TimevalueT1");
    }
     if(Screendown == true && Screen10_d == true){
      Screendown = false;
      if(day == 1){
        day = 31;
      }
       else{
        day = day - 1;
      day = constrain(day, 1, 31);
      }
     Screen_10DatevalueT1(day,month,year);
//      Serial.println("Screen_10TimevalueT1");
    }
    if(Screenenter == true && Screen10_d == true && td_transition == 4){
      Screenenter = false;
      Screen10_d = false;
      Screen10_mon = true;
     Screen_10DatevalueT2(day,month,year);
//      Serial.println("Screen_10DatevalueT2");
    }
     if(Screenup == true && Screen10_mon == true){
      Screenup = false;
      if(month == 12){
        month = 1;
      }
      else{
        month = month + 1;
        month = constrain(month, 1, 12);
      }
     Screen_10DatevalueT2(day,month,year);
//      Serial.println("Screen_10DatevalueT2");
    }
     if(Screendown == true && Screen10_mon == true){
      Screendown = false;
      if(month == 1){
        month = 12;
      }
      else{
        month = month - 1;
        month = constrain(month, 1, 12);
      }
     Screen_10DatevalueT2(day,month,year);
//      Serial.println("Screen_10TimevalueT1");
    }        
    if(Screenenter == true && Screen10_mon == true && td_transition == 5){
      Screenenter = false;
      Screen10_mon = false;
      Screen10_y = true;
     Screen_10DatevalueT3(day,month,year);
//     Serial.println("Screen_10yes");
    }
     if(Screenup == true && Screen10_y == true){
      Screenup = false;
      if(year == 2100){
        year = 2000;
      }
      else{
        year = year + 1;
        year = constrain(year, 2000, 2100);
      }
       Screen_10DatevalueT3(day,month,year);
//      Serial.println("Screen_10DatevalueT3");
    }
     if(Screendown == true && Screen10_y == true){
      Screendown = false;
     
      if(year == 2000){
        year = 2000;
      }
      else{
         year = year - 1;
        year = constrain(year, 2000, 2100);
      }
       Screen_10DatevalueT3(day,month,year);
//      Serial.println("Screen_10DatevalueT3");
    }   
    if(Screenenter == true && Screen10_y == true && td_transition == 6){
      Screenenter = false;
      Screen10 = false;
      Screen10_y = false;
      Screen10_1 = true;
      confirmscreen();
      confirmscreent1();
      confirmyesnotransition = 0;
//      Serial.println("Screen_8T0");
    }
    if(Screenup == true && Screen10_1 == true){
      Screenup = false;
      if(confirmyesnotransition==1){
        confirmscreent1();
        confirmyesnotransition = 0;
      }
      else{
        confirmscreent2();
        confirmyesnotransition = 1;
      }
      
//      Serial.println("Screen_3yes");
    }
    if(Screendown == true && Screen10_1 == true){
      Screendown = false;
      if(confirmyesnotransition==0){
        confirmscreent2();
        confirmyesnotransition = 1;
      }
      else{
        confirmscreent1();
        confirmyesnotransition = 0;
      }
      
//      Serial.println("Screen_3no");
    }
    if(Screenenter == true && Screen10_1 == true && confirmyesnotransition == 0){
      Screenenter = false;
      confirmyesnotransition=0;
      Screen10_1 = false;
      Screen8 = true;
      timesend = false;
      Screen_8T0();
      Screen_8T3();
      settings_transition = 2;
      td_transition = 1;
//      Serial.println("Screen_2T0");
    }
    if(Screenenter == true && Screen10_1 == true && confirmyesnotransition == 1){
      Screenenter = false;
      Screen10_1 = false;
      Screen8 = true;
      timesend = true;
      Screen_8T0();
      Screen_8T3();
      td_transition = 1;
      settings_transition = 2;
//      Serial.println("Screen_2T0");
    }                     
//    // Screen 11
      if(Screenenter == true && settings_transition == 3 && Screen8 == true){
      Screenenter = false;
      Screen8 = false;
      Screen11 = true;
      Screen_11Setunits();
      Screen_11SetunitsT1();
      screen11_transition = 0;
//      Serial.println("Screen_11SetunitsT1");
    }
    
    //
     
    if((Screenup == true || Screendown == true ) && Screen11 == true && screen11_transition == 0){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT1();
//      Serial.println("Screen_11SetunitsT1");
    }
     if(Screenenter == true && Screen11 == true && screen11_transition == 0){
      Screenenter = false;
      Screen11 = false;
      Screen11_1 = true;
      if(tempunitflag == 0){
        Screen_15T1();
      }
      if(tempunitflag == 1){
        Screen_15T2();
      }
      if(tempunitflag == 2){
        Screen_15T3();
      }
//      Serial.println("Screen_15T1");
    }
     if((Screenup == true || Screendown == true ) && Screen11 == true && screen11_transition == 1){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT2();
//      Serial.println("Screen_11SetunitsT2");
    }
     if(Screenenter == true && Screen11 == true && screen11_transition == 1){
      Screenenter = false;
      Screen11 = false;
      Screen11_2 = true;
      if(flowunitflag == 0){
        Screen_11flowunitsoptionT1();
      }
      if(flowunitflag == 1){
        Screen_11flowunitsoptionT2();
      }
      if(flowunitflag == 2){
        Screen_11flowunitsoptionT3();
      }
//      Serial.println("Screen_11flowunitsoptionT1");
    }
     if((Screenup == true || Screendown == true ) && Screen11 == true && screen11_transition == 2){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT3();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && Screen11 == true && screen11_transition == 2){
      Screenenter = false;
      Screen11 = false;
      Screen11_3 = true;
      if(bpunitflag == 0)
      {
        Screen_11bpunitsoptionT1();
      }
      if(bpunitflag == 1)
      {
        Screen_11bpunitsoptionT2();
      }
      if(bpunitflag == 2)
      {
        Screen_11bpunitsoptionT3();
      }
//      Serial.println("Screen_8T0");
    }
     if((Screenup == true || Screendown == true ) && Screen11 == true && screen11_transition == 3){
      Screenup = false;
      Screendown = false;
      Screen_11SetunitsT4();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && Screen11 == true && screen11_transition == 3){
      Screenenter = false;
      Screen11 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T3();
      screen11_transition = 0;
//      Serial.println("Screen_8T0");
    }
    //
    if(Screendown == true && Screen11_1 == true && screen11_transition == 0){
      Screendown = false;
      if(tempunitflag == 0){
        Screen_11tempunitsoptionT2();
        tempunitflag = 1;
        TemperatureUnits = "F";
      }
      else if(tempunitflag == 1){
        Screen_11tempunitsoptionT3();
        tempunitflag = 2;
        TemperatureUnits = "K";
      }
      else if(tempunitflag == 2){
        Screen_11tempunitsoptionT1();
        tempunitflag = 0;
        TemperatureUnits = "C";
      }
//      Serial.println("Screen_11tempunitsoptionT2");
    }
     if(Screenup == true && Screen11_1 == true && screen11_transition == 0){
      Screenup = false;
      if(tempunitflag == 0){
        Screen_11tempunitsoptionT3();
        tempunitflag = 2;
        TemperatureUnits = "K";
      }
      else if(tempunitflag == 1){
        Screen_11tempunitsoptionT1();
        tempunitflag = 0;
        TemperatureUnits = "C";
      }
      else if(tempunitflag == 2){
        Screen_11tempunitsoptionT2();
        tempunitflag = 1;
        TemperatureUnits = "F";
      }
//      Serial.println("Screen_11tempunitsoptionT1");
    }

    if(Screenenter == true && Screen11_1 == true){
      Screenenter = false;
      Screen11_1 = false;
      Screen11 = true;
      writeruntimehour(tempunitflag,8);
      Screen_11Setunits();
      Screen_11SetunitsT1();
      screen11_transition = 0;
//      Serial.println("Screen_11SetunitsT1");
    }
    
    //flowunitflag,bpunitflag;

     if(Screendown == true && Screen11_2 == true && screen11_transition == 1){
      Screendown = false;
      if(flowunitflag == 1){
        Screen_11flowunitsoptionT3();
        Flowrateunits = "mL/M";
        flowunitflag = 2;
//        Serial.println("Screen_11flowunitsoptionT3");
      }
      else if(flowunitflag == 2){
        Screen_11flowunitsoptionT1();
        Flowrateunits = "CC/M";
        flowunitflag = 0;
//        Serial.println("Screen_11flowunitsoptionT1");
      }
      else if(flowunitflag == 0){
        Screen_11flowunitsoptionT2();
      Flowrateunits = "L/M";
      flowunitflag = 1;
//      Serial.println("Screen_11flowunitsoptionT2");
      }
    }
     if(Screenup == true && Screen11_2 == true && screen11_transition == 1){
      Screenup = false;
      if(flowunitflag == 0){
        Screen_11flowunitsoptionT3();
        Flowrateunits = "mL/M";
        flowunitflag = 2;
//        Serial.println("Screen_11flowunitsoptionT3");
      }
      else if(flowunitflag == 2){
        Screen_11flowunitsoptionT2();
        Flowrateunits = "L/M";
        flowunitflag = 1;
//        Serial.println("Screen_11flowunitsoptionT2");
      }
      else if(flowunitflag == 1){
        Screen_11flowunitsoptionT1();
      Flowrateunits = "CC/M";
      flowunitflag = 0;
//      Serial.println("Screen_11flowunitsoptionT1");
      }
    }

    //
      if(Screendown == true && Screen11_3 == true && screen11_transition == 2){
      Screendown = false;
      if(bpunitflag == 1){
      Screen_11bpunitsoptionT3();
      BackPressureUnits = "cm.H2O";
      bpunitflag = 2;
      }
      else if(bpunitflag == 0){
      Screen_11bpunitsoptionT2();
      BackPressureUnits = "in.H20";
      bpunitflag = 1; 
      }
      else if(bpunitflag == 2){
      Screen_11bpunitsoptionT1();
      BackPressureUnits = "KPA";
      bpunitflag = 0; 
      }
//      Serial.println("Screen_11bpunitsoptionT2");
    }
     if(Screenup == true && Screen11_3 == true && screen11_transition == 2){
      Screenup = false;
      if(bpunitflag == 0){
        Screen_11bpunitsoptionT3();
      BackPressureUnits = "cm.H2O";
      bpunitflag = 2; 
      }
      else if(bpunitflag == 1){
        Screen_11bpunitsoptionT1();
        BackPressureUnits = "KPA";
        bpunitflag = 0; 
      }
      else if(bpunitflag == 2){
        Screen_11bpunitsoptionT2();
        BackPressureUnits = "in.H2O";
        bpunitflag = 1; 
      }
//      Serial.println("Screen_11bpunitsoptionT1");
    }

     if(Screenenter == true && Screen11_2 == true){
      Screenenter = false;
      Screen11_2 = false;
      Screen11 = true;
      writeruntimehour(flowunitflag,9);
       Screen_11Setunits();
      Screen_11SetunitsT2();
//      Serial.println("Screen_11SetunitsT2");
    }
    if(Screenenter == true && Screen11_3 == true){
      Screenenter = false;
      Screen11_3 = false;
      Screen11 = true;
      writeruntimehour(bpunitflag,10);
       Screen_11Setunits();
      Screen_11SetunitsT3();
//      Serial.println("Screen_11SetunitsT2");
    }
    
/////////////////////////////////////////////////////////////////////
    // Screen 12
////////////////////////////////////////////////////////////////////

      if(Screenenter == true && settings_transition == 5 && Screen8 == true){
      Screenenter = false;
      Screen8 = false;
      Screen12 = true;
      updates = constrain(updates, 0, 100000);
      Screen_12Setupdateretries();
      Screen_12Setupdateretriesvalue(updates);
//      Serial.println("Screen_9_0");
    }
    if(Screenup == true && Screen12 == true){
      Screenup = false;
      updates = updates + 1;
      updates = constrain(updates, 0, 5);
      Screen_12Setupdateretriesvalue(updates);
//      Serial.println("Screen_12yes");
    }
    if(Screendown == true && Screen12 == true){
      Screendown = false;
      updates = updates - 1;
      updates = constrain(updates, 0, 5);
      Screen_12Setupdateretriesvalue(updates);
//      Serial.println("Screen_12no");
    }
    if(Screenenter == true && Screen12 == true){
      Screenenter = false;
      Screen12 = false;
      Screen12_1 = true;
      confirmscreen();
      confirmscreent1();
      confirmyesnotransition = 0;
//      Serial.println("Screen_2T0");
    }
    if(Screenup == true && Screen12_1 == true){
      Screenup = false;
      if(confirmyesnotransition==1){
        confirmscreent1();
        confirmyesnotransition = 0;
      }
      else{
        confirmscreent2();
        confirmyesnotransition = 1;
      }
      
//      Serial.println("Screen_3yes");
    }
    if(Screendown == true && Screen12_1 == true){
      Screendown = false;
      if(confirmyesnotransition==0){
        confirmscreent2();
        confirmyesnotransition = 1;
      }
      else{
        confirmscreent1();
        confirmyesnotransition = 0;
      }
      
//      Serial.println("Screen_3no");
    }
    if(Screenenter == true && Screen12_1 == true && confirmyesnotransition == 0){
      Screenenter = false;
      confirmyesnotransition=0;
      updates = readruntimehour(updates,11);
      Screen12_1 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T4();
      td_transition = 3;
//      Serial.println("Screen_2T0");
    }
    if(Screenenter == true && Screen12_1 == true && confirmyesnotransition == 1){
      Screenenter = false;
      Screen12_1 = false;
//      updates = 0;
      writeruntimehour(updates,11);
      confirmyesnotransition=0;
      Screen8 = true;
      Screen_8T0();
      Screen_8T4();
      td_transition = 3;
//      Serial.println("Screen_2T0");
    }          
           
//////////////////////////////////////////////////////////////////////////////////////    
    // Screen 16
///////////////////////////////////////////////////////////////////////////////////////

    if(Screenenter == true && settings_transition == 4 && Screen8 == true){
      Screenenter = false;
      Screen8 = false;
      Screen16 = true;
      Screen_16calibrationoption();
      Screen_16calibrationoptionT2();
      webyesnotransition = 0;
      
//      Serial.println("Screen_9_0");
    }
    if(Screendown == true && Screen16 == true){
      Screendown = false;
      if(webyesnotransition==0){
        Screen_16calibrationoptionT1();
        webyesnotransition = 1;
      }
      else{
        Screen_16calibrationoptionT2();
        webyesnotransition = 0;
      }
      
//      Serial.println("Screen_12yes");
    }
    if(Screenup == true && Screen16 == true){
      Screenup = false;
      if(webyesnotransition==1){
        Screen_16calibrationoptionT2();
        webyesnotransition = 0;
      }
      else{
        Screen_16calibrationoptionT1();
        webyesnotransition = 1;
      }
//      Serial.println("Screen_12no");
    }
    
    if(Screenenter == true && Screen16 == true && webyesnotransition == 1){
      Screenenter = false;
      Screen16 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T5();
      td_transition = 4;
     
      Serial.println("Factory Reset");
    }
    if(Screenenter == true && Screen16 == true && webyesnotransition == 0){
      Screenenter = false;
      Screen16 = false;
      Screen8 = true;
      Screen_8T0();
      Screen_8T5();
      td_transition = 4;
//      Serial.println("Screen_2T0");
    }
///////////////////////////////////////////////////////////////////////////////
//  // Screen 17
/////////////////////////////////////////////////////////////////////////////    
     if(Screenenter == true && settings_transition == 7 && Screen8 == true){
      Screenenter = false;
      Screen8 = false;
      Screen17 = true;

//      Serial.println("Screen_2T0()");
    }
}
