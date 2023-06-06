//Includes
#include <Wire.h>
#include "RTClib.h"
#include <string>
//Superior Sensor Slave Addresses
 #define ND_SLAVE 0x31
 #define HV_SLAVE 0x28

//for PID
volatile double target=2;
volatile double calibration = 0;
volatile double integral=0;
volatile double prev_prop=0;
volatile double target_outlet = 0;

const double kp=0.1;
const double kd=0.1;
const double ki=0.007;

//********************************
//    Interpolation Code Start
//********************************
int oneLen = 5;
double oneValues[5][2] = {
  {0.09, 58},
  {0.32, 58},
  {1.22, 60},
  {3.15, 62},
  {20, 62}
};

int twoLen = 6;
double twoValues[6][2] = {
  {0.11, 164},
  {1.26, 166},
  {2.98, 168},
  {5.05, 170},
  {12.25, 172},
  {16.9, 172}
};

int threeLen=4;
double threeValues[4][2] = {
  {0.18, 330},
  {2.28, 334},
  {5.06, 337},
  {11.8, 340}
};

int fourLen=4;
double fourValues[4][2] = {
  {0.29, 535},
  {3.45, 540},
  {6.03, 544},
  {8.44, 546}
};

int fiveLen=3;
double fiveValues[3][2] = {
  {0.41, 780},
  {3.33, 786},
  {5.25, 792}
};


double interpolate(double arr[][2], int rows, double x) {
  // If x is less than the first x value in the array, return the first y value
  if (x < arr[0][0]) {
    return arr[0][1];
  }
  // Find the two nearest x values in the array
  int i = 0;
  while (i < rows && arr[i][0] < x) {
    i++;
  }
  // If x is greater than the last x value in the array, return the last y value
  if (i == rows) {
    return arr[rows-1][1];
  }
  // If x is equal to an x value in the array, return the corresponding y value
  if (arr[i][0] == x) {
    return arr[i][1];
  }
  // Calculate the slope and y-intercept of the line between the two nearest points
  double slope = (arr[i][1] - arr[i-1][1]) / (arr[i][0] - arr[i-1][0]);
  double yIntercept = arr[i][1] - slope * arr[i][0];
  // Use the slope and y-intercept to interpolate the y value for x
  double y = slope * x + yIntercept;
  return y;
}

double (*lowerArray)[2];
double (*upperArray)[2];
int lowerLength;
int upperLength;
double flowAdd=0;

void setFlow(double fl){
  Serial.print("Setting flow: ");
  Serial.println(fl);
  target =  fl;
//  flow = fl;
  if (fl>=1 & fl<2){
    lowerArray = oneValues;
    lowerLength = oneLen;
    upperArray = twoValues;
    upperLength = twoLen;
    flowAdd = fl-1.0;  
  }else if (fl>=2 & fl<3){
    lowerArray = twoValues;
    lowerLength = twoLen;
    upperArray = threeValues;
    upperLength = threeLen;
    flowAdd = fl-2.0;  
  }else if (fl>=3 & fl<4){
    lowerArray = threeValues;
    lowerLength = threeLen;
    upperArray = fourValues;
    upperLength = fourLen;
    flowAdd = fl-3.0;  
  }else if (fl>=4 & fl<=5){
    lowerArray = fourValues;
    lowerLength = fourLen;
    upperArray = fiveValues;
    upperLength = fiveLen;
    flowAdd = fl-4.0;  
  }  
}

double targetOutlet(double bp){
  double y1 = interpolate(lowerArray, lowerLength, bp);
  double y2 = interpolate(upperArray, upperLength, bp);
  double y = flowAdd*y2 - flowAdd*y1 + y1;
  return y;
}

void update_outlet(double bp){
  target_outlet =targetOutlet(bp);
  Serial.print("Target outlet: ");
  Serial.println(target_outlet);
}


//******************************
//    Interpolation Code End
//******************************

//Timing Info
DateTime start_time;
DateTime end_time;
DateTime current_time;
volatile unsigned int restarts = 0;
volatile unsigned int stableTime = 0;


//State Flags
bool pidRunning = false;
bool sensorSampling = false;
bool idle = true;
int pumpState = 0;

//RTC
RTC_DS1307 rtc;

//ADXL 345
#include <Adafruit_Sensor.h> 
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

//Dual Core Settings
TaskHandle_t task_loop1;
TaskHandle_t task_loop2;
void esploop1(void* pvParameters) {
  for (;;)
    loop1();
}

//Pump PWM COnfigurations
const int pwmfreq = 25000; 
const int ledChannel = 0; 
const int resolution = 10;
const int ledPin = 33;

//Flow and Back Pressure Volatile
volatile double flow = 2;
volatile double backPressure = 1;
double volume = 0;
long time_running = 0;

//For setting Pump pwm level
void setPump(int duty){
  if (duty<0) duty=0;
  if (duty>1023) duty=1023;
  pumpState = duty;
  Serial.print("Pump Set: ");
  Serial.println(duty);
    ledcWrite(ledChannel, duty);
}

//Superior Sensors
double getND(){
  Wire.beginTransmission(ND_SLAVE);
  Wire.requestFrom(ND_SLAVE, 2, true);
  byte b1 = Wire.read();
  byte b2 = Wire.read();
  int16_t rawVal = (int16_t)((b1 << 8) | b2);
  double pressure = (rawVal/29491.2)*5*6.89476;
  return pressure;
}

double getHV(){
  Wire.beginTransmission(HV_SLAVE);
  Wire.requestFrom(HV_SLAVE, 2, true);
  byte b1 = Wire.read();
  byte b2 = Wire.read();
  int16_t rawVal = (int16_t)((b1 << 8) | b2);
  double pressure = (rawVal/29491.2)*10*0.24884*1000;
  return pressure;
  }

//Read Pressures
volatile bool readingPressure = false;
volatile bool readingSensor = false;

double getBP(){
  while (readingSensor){}
  readingPressure = true;
  double outlet = getND();
  readingPressure = false;
  return outlet;
}

double getOutletPressure(){
  while (readingSensor){}
  readingPressure = true;
  double outlet = getHV();
  readingPressure = false;
  return outlet;
}

char monthStr[12][10] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


void checkCommands(){
//  Serial.println(millis());
        if (startsample == true){        //TBC to Boolean StartSample //Done
          Serial.println("a command received");
          
          //Start Sampling
          String targetFlowStr = strtok(charBuf, ",");
//          target = targetFlowStr.toFloat();
          setFlow(targetFlowStr.toFloat());
          String caliFactorStr = strtok(NULL, ",");
          calibration = caliFactorStr.toFloat();
          String runTimeStr = strtok(NULL, ",");
          Serial.println("Run time str");
          Serial.println(runTimeStr);
          String delayTimeStr = strtok(NULL, ",");
          DateTime now = current_time;
          int delayTimeInt = delayTimeStr.toInt();
          if (delayTimeInt <5) delayTimeInt=5;
          DateTime st_time(now+TimeSpan(delayTimeInt));
          start_time = st_time;
          DateTime e_time(start_time+TimeSpan(runTimeStr.toInt()*60));
          end_time = e_time;
          String restartStr = strtok(NULL, ",");
          restarts = restartStr.toInt();
          if (restarts==0){restarts=5;}
          stableTime = (120/restarts - 10);
          Serial.println("Starting Sampling");
          Serial.print("Flow: ");
          Serial.println(targetFlowStr);
          Serial.print("Calibration: ");
          Serial.println(caliFactorStr);
          Serial.print("Run Time: ");
          Serial.println(runTimeStr);
          Serial.print("Delay: ");
          Serial.println(delayTimeStr);
          Serial.print("Restarts: ");
          Serial.println(restartStr);
          Serial.print("Now: ");
          Serial.printf("%s %d,%d   %d: %d: %d\n",monthStr[now.month()-1], now.day(), now.year(),now.hour(), now.minute(), now.second());
          Serial.print("Start: ");
          Serial.printf("%s %d,%d   %d: %d:%d\n",monthStr[start_time.month()-1], start_time.day(), start_time.year(),start_time.hour(), start_time.minute(), start_time.second());
          Serial.print("Stop: ");
          Serial.printf("%s %d,%d   %d: %d:%d\n",monthStr[end_time.month()-1], end_time.day(), end_time.year(),end_time.hour(), end_time.minute(), end_time.second());
          idle = false;
          volume = 0;
          
        }else if (stopsamplesend == true){
          Serial.println("Z command received");
          
          //Stop Sampling
          Serial.println("Stopping Sampling");
          pidRunning = false;
          sensorSampling = false;
          idle = true;
        }else if (command == 't'){
          Serial.println("T command received");

          //Set time
          String yearStr = strtok(charBuf, ",");
          int year = yearStr.toFloat();
          String monthStr = strtok(NULL, ",");
          int month = monthStr.toFloat();
          String dayStr = strtok(NULL, ",");
          int day = dayStr.toFloat();
          String hourStr = strtok(NULL, ",");
          int hour = hourStr.toFloat();
          String minuteStr = strtok(NULL, ",");
          int minute = minuteStr.toFloat();
          rtc.adjust(DateTime(year, month, day, hour, minute, 0));
          Serial.println("Time Set");
            
        }else if (startcalibrate == true){
          Serial.println("C command received");
          
          //Start Calibration
          Serial.println("Start/Update Calibration");
          String targetFlowStr = strtok(charBuf, ",");
//          target = targetFlowStr.toFloat();
          setFlow(targetFlowStr.toFloat());
          String caliFactorStr = strtok(NULL, ",");
          calibration = caliFactorStr.toFloat();
          pidRunning = true;
            
        }else if (stopcalibrate == true){
          Serial.println("s command received");
          //Stop Calibration
          Serial.println("Stop Calibration");
          pidRunning=false;
            
        }

        Serial.println(data);
      
  
}




void control_setup() {
  Wire.begin();
//  Wire.setClock(5000);
  //Second Core Conf
    xTaskCreatePinnedToCore(
    esploop1,               /* Task function. */
    "loop1",                /* name of task. */
    15000,                  /* Stack size of task */
    NULL,                   /* parameter of the task */
    1,                      /* priority of the task */
    &task_loop1,            /* Task handle to keep track of created task */
    0);                     /* pin task to core */

    xTaskCreatePinnedToCore(
    control_functions,               /* Task function. */
    "loop2",                /* name of task. */
    15000,                  /* Stack size of task */
    NULL,                   /* parameter of the task */
    1,                      /* priority of the task */
    &task_loop2,            /* Task handle to keep track of created task */
    0);                     /* pin task to core */



    
}

void control_functions(void * parameter){

//Superior Sesnors
    Wire.beginTransmission(ND_SLAVE); //Inlet
    Wire.write(0x97);
    Wire.endTransmission();

    Wire.beginTransmission(HV_SLAVE);  //Outlets
    Wire.write(0xC6);
    Wire.endTransmission();

    //Serial Monitor
    Serial.begin(115200);
    //Serial2.begin(115200);

    //Pump PWM
    ledcSetup(ledChannel, pwmfreq, resolution);
    ledcAttachPin(ledPin, ledChannel);
    ledcWrite(ledChannel, 128);

    //Temperature and Humidity Sensor

    //RTC
    rtc.begin();
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
//    Serial.println("rtc done");

    //ADXL 345
    accel.begin();
//    Serial.println("adxl done");

    for (;;){
      control_loop();
    }
 
}

void control_loop() {
//  Serial.print("Main Loop ");
//  Serial.println(xPortGetCoreID());

    long t = millis();
    checkCommands();
    while (millis()-100<t);

//    Serial.println("Check commands done");
   
    t = millis();
    //Read RTC
    while (readingPressure){}
    readingSensor=true;
    DateTime now = rtc.now();
    readingSensor=false;
//    Serial.println("Read RTC done");
    
    current_time = now;
    char datestr[20];
    sprintf(datestr, "%s %d, %d", monthStr[now.month()-1], now.day(), now.year());
//    Serial.println(datestr);
    char timestr[10];
    sprintf(timestr, "%02d : %02d", now.hour(), now.minute());
//    Serial.println(timestr);
    
    while (millis()-100<t);
    
    t = millis();
    checkCommands();
    while (millis()-100<t);
    
    t = millis();
    //Read Temp & Humidity
        while (readingPressure){}
    readingSensor = true;
    Wire.beginTransmission(0x38);
    Wire.write(0x70);
    Wire.write(0xAC);            
    Wire.write(0x33);  
    Wire.write(0x00);     
    Wire.endTransmission();
    Wire.beginTransmission(0x38); 
    Wire.write(0x71);
    Wire.requestFrom(0x38,7,true);
    byte b1 = Wire.read();
    byte b2 = Wire.read();
    byte b3 = Wire.read();
    byte b4 = Wire.read();
    byte b5 = Wire.read();
    byte b6 = Wire.read();
    byte b7 = Wire.read();
    Wire.endTransmission();
    unsigned long tempraw = (b4&0xF)*256*256+b5*256+b6;

    if (tempraw == 0) tempraw=1;
    
    float temperature = tempraw/1048576.0*200.0-50.0;
//    Serial.print("Temperature: ");
//    Serial.println(temperature);
    unsigned long humraw = (b2*256*256+b3*256+b4);
    if (humraw==0) humraw=1; 
    humraw = humraw/16;
    float humidity = humraw /1048576.0*100.0;
//    Serial.print("Humidity: ");
//    Serial.println(humidity);
    readingSensor = false;

    
    
    while (millis()-100<t);
    
    t = millis();
    checkCommands();
    while (millis()-100<t);
    
    t = millis();
    //Read Acceleration
            while (readingPressure){}
            readingSensor=true;
//    sensors_event_t event; 
//    accel.getEvent(&event);
    readingSensor=false;
//    Serial.print("x: ");
//    Serial.println(event.acceleration.x);
//    Serial.print("y: ");
//    Serial.println(event.acceleration.y);
//    Serial.print("z: ");
//    Serial.println(event.acceleration.z);
        
    while (millis()-100<t);
    
    t = millis();
    checkCommands();
    while (millis()-100<t);
    
    t = millis();
    //Read Battery
    while (millis()-100<t);
    
    t = millis();
    checkCommands();
    while (millis()-100<t);
    
    t = millis();

    //TBC //Done
    //Send Data
//    Serial2.print("h");
//    Serial2.print(datestr);
//    Serial2.print(",");
//    Serial2.print(timestr);
//    Serial2.print(",5");
//    Serial2.println();
//
//    Serial.println("Serial2 data");
//    Serial.print("h");
//    Serial.print(datestr);
//    Serial.print(",");
//    Serial.print(timestr);
//    Serial.print(",5");
//    Serial.println();


    if (sensorSampling){
      //TBC   /Done


     Displayflow = flow;
     DisplayBattary = "15.00";  //TBC
     DisplayTemp  =  temperature;
     DisplayHumidity = humidity; 
     float accelr = 0;
     DisplayMotion = accelr;
     DisplayDate = datestr; 
     DisplayYear = "23";
     DisplayTime = timestr;
     DisplayBackPressure = backPressure;
     char hour_string[];
     sprintf(hour_string,"%d:%d", now.hour(), now.minute());
     DisplayVolume = volume, 
     DisplayTimeHours = hour_string; //time in hours TBC
     DisplayErrorMsg; 
     Displaydelaytime;
     FlowDisplay;
//    Serial2.print("d");
//    Serial2.print(flow);
//    Serial2.print(",");
//    Serial2.print(temperature);
//    Serial2.print(",");
//    Serial2.print(humidity);
//    Serial2.print(",");
//    float accelr = sqrt(sq(event.acceleration.x)+sq(event.acceleration.y)+sq(event.acceleration.z));
//    float accelr = 0;
//    //TBC
//    Serial2.print(accelr);
//    Serial2.print(",");
//    Serial2.print(volume);
//    Serial2.print(",");
//    Serial2.print(int(time_running/60));
////    Serial2.print(": ");
////    Serial2.print(int(time_running/60)%60); 
//    Serial2.print(",");
//    Serial2.print(backPressure);
//    Serial2.println();

    Serial.println("Serial2 data");
    Serial.print("d");
    Serial.print(flow);
    Serial.print(",");
    Serial.print(temperature);
    Serial.print(",");
    Serial.print(humidity);
    Serial.print(",");
    Serial.print(accelr);
    Serial.print(",");
    Serial.print(volume);
    Serial.print(",");
    Serial.print(int(time_running/60));
//    Serial2.print(": ");
//    Serial2.print(int(time_running/60)%60);
    Serial.print(",");
    Serial.print(backPressure);
    Serial.println();
    }
    
    while (millis()-100<t);
}

int out = 0;
int32_t long lastMax = 0;
bool wasPreviousUnstable = false;
int restartsDone = 0;
unsigned long oldFlowTime = 0;
int discardCount = 10;

void loop1(){
  static int previousWaitTime = 0;

   delay(100);

   bool limitReached = false;

    if (pidRunning){

      //Eliminated for now because frequency is now not involved
//      if (pumpState == 0){
//        setPump(100);
//        delay(1000);  
//      }
      Serial.println("Getting Pressure");
    double bp = getBP();
    Serial.print("bp=");
    Serial.println(bp);
    double outlet = getOutletPressure();
    Serial.print("outlet=");
    Serial.println(outlet);
    if (isnan(bp)){
      Serial.println("bp was nan");
      bp=60; 
     }
//    Serial.println(bp);
      backPressure = bp;
      update_outlet(bp);

      //Todo: Calculations for flowLocal remaining

      float prop = target_outlet - outlet;
      integral+=prop;
//      if (integral*ki < -3) integral = -3/ki;
//      if (integral*ki >  3) integral = 3/ki;
      
      double deriv= prop-prev_prop;
      double d = constrain(deriv*kd, -200, 200);
      double p=prop*kp;
      double i=integral*ki;

//      Serial.print("Prop: ");
//      Serial.println(p);
//      Serial.print("Deriv: ");
//      Serial.println(d);
//      Serial.print("Integ: ");
//      Serial.println(i);
      
      out = constrain(out+p+d+i, 0, 1023);
      setPump(out);

      if (out >= 1023){   
          limitReached = true;
      }
      
      prev_prop = prop;  
      
    }else{
//      Serial.println("No PID. Setting pump to zero");
      setPump(0);  
    }
    if (!idle){
//      Serial.println("Not idle");
      DateTime now = current_time;
//              Serial.print("Now: ");
//          Serial.printf("%s %d,%d   %d: %d: %d\n",monthStr[now.month()-1], now.day(), now.year(),now.hour(), now.minute(), now.second());
          
    
//    Serial.print("Raw unixtime\n");
    
    int32_t start_left = (now-start_time).totalseconds();
    if (start_left > 86400 || start_left<-86400) return;
    int32_t stop_left = (now-end_time).totalseconds();
    if (stop_left > 86400*2 || stop_left<-86400*2) return;
//    Serial.print(start_left);
//    Serial.print("    ");
//    Serial.println(stop_left);

    if (start_left<0){ //waiting condition
//      Serial.print("in the first if");
    int start_left_send = 0 - start_left;
    char start_left_string[50];
//    if (start_left_send > 5);
//    Serial.println(start_left_send);
    if (start_left_send != previousWaitTime){
      previousWaitTime = start_left_send;
        //Serial2.print("w");                     //TBC to variable, //Done
        //Serial2.println(start_left_send);
        int sec, h, m, s;
        h = (sec/3600); 
        m = (sec -(3600*h))/60;
        s = (sec -(3600*h)-(m*60));
        sprintf(start_left_string, "%d:%d:%d", h, m, s);
        displaydelaytime =  start_left_string;
        Serial.print("w");
        Serial.println(start_left_send); 
    }
 
     
    }
    
    if (start_left>0 && stop_left<=0){ //running condition
//      Serial.print("in the second if");
      if (pidRunning == false){
        oldFlowTime = millis();  
      }
      pidRunning = true;
      sensorSampling = true;  
      time_running = start_left;
      volume += (flow/60)*(millis()-oldFlowTime)/1000;
      oldFlowTime = millis();
//      Serial.println("Pump On");
      previousWaitTime = 0;
    }else if (stop_left >= 0){ // stop after time completed
//      Serial.print("in the third if");
      pidRunning = false;
      sensorSampling = false;
      idle = true;        
      Serial.println("Pump Off");
      Serial2.println("s");             //TBC
    }
      
      
      }

      //Condition for restarts
      if (sensorSampling == true){
      //limitReached  
      //stableTime
      //lastMax 
      //wasPreviousUnstable 
      //restartsDone 

      bool overridePreviousUnstable = false;

      if (!limitReached){
//        Serial.println("Not limit reached");
        if (discardCount == 0){
          discardCount--;
        lastMax = 0;
        restartsDone = 0;
//        Serial.println("Restarts done is reset"); 
        }
      }
      else{
        DateTime now = current_time;
        if (wasPreviousUnstable){
//          Serial.println("Previous was unstable");
          if ((now-start_time).totalseconds() - lastMax > stableTime){
            if (restartsDone >= restarts){
              Serial2.println("eCould not maintain flow");
              Serial.println("eCould not maintain flow");
              restartsDone=0;
              discardCount=10;
              pidRunning = false;
              sensorSampling = false;
              idle = true;  
              
            }
            else{
              setPump(0);
            lastMax = 0;
            overridePreviousUnstable = true;
            restartsDone += 1;
            restarting = true;
            Serial.print("Restart send\nRestart#");
            Serial.println(restartsDone);
            flow = 0;
            sensorSampling = false;
            integral = 0;
            delay(10000);
            if (pidRunning)
            {
              sensorSampling = true;
            }
              }
             
          }
          
        }else{//previous was not unstable. New unstability ai he
          lastMax = (now-start_time).totalseconds();
        }
      }
        if (overridePreviousUnstable){
          wasPreviousUnstable = false;
        }else{
          wasPreviousUnstable = limitReached;
        }
      }  
}
