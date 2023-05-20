
// Screen 3
void Screen_3STARTSAMPLING(double flow,double calibrate,int runtimehours,int runtimeminutes,int timedelayhour, int timedelayminutes,int updates, String lastcal){
//  tft.fillRoundRect(65,100,185, 70, 3 , TFT_CYAN1);
    tft.pushImage(0,60,320, 150, midscreenback);
    tft.setFreeFont(FSS09);  // FreeSansbold9
    tft.setTextColor(TFT_CYAN3);
    tft.setCursor(125,110);
    tft.setTextSize(1);
    tft.print("Set flow");
    tft.setCursor(125,125);
    tft.print("Run time");
    tft.setCursor(125,140);
    tft.print("Calibrated");
    tft.setCursor(125,155);
    tft.print("Restarts");
    tft.setCursor(125,170);
    tft.print("Time delay");
    tft.setCursor(200,110);
    tft.print(flow);
    tft.setCursor(200,125);
    String Run = String(runtimehours) + ":" + String(runtimeminutes);
    tft.print(Run);
    tft.setCursor(200,140);
    tft.print(lastcal);
    tft.setCursor(200,155);
    tft.print(updates);
    tft.setCursor(200,170);
    Run = String(timedelayhour) + ":" + String(timedelayminutes);
    tft.print(Run);
}
void Screen_3T1(){
//  tft.pushImage(80,145,140, 20, s3_yesnoback);
  tft.fillRoundRect(20,85,85, 42, 1 , TFT_WHITE);
  tft.pushImage(15,135,102, 42, s3_opt2);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(40,100);
  tft.setTextSize(1);
  tft.print("Start");
  tft.setCursor(25,120);
  tft.print("Sampling");
//  tft.pushImage(40,85,85, 42, s3_opt1);

  tft.setCursor(40,150);
  tft.print("Reset");
  tft.setCursor(20,170);
  tft.print("Parameters");
//  tft.fillRoundRect(170,145,45, 20, 1 , TFT_GREY3);


  
}
void Screen_3T2(){
  tft.pushImage(20,85,85, 42, s3_opt1);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(40,100);
  tft.setTextSize(1);
  tft.print("Start");
  tft.setCursor(25,120); 
  tft.print("Sampling");
  tft.fillRoundRect(15,135,102, 42, 1 , TFT_WHITE);
//  tft.pushImage(40,85,85, 42, s3_opt1);
  tft.setCursor(40,150);
  tft.print("Reset");
  tft.setCursor(20,170);
  tft.print("Parameters");
  
}
void Screen_3T2no(){
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
void Screen_3T1yes(){
  tft.pushImage(80,145,140, 20, s3_yesnoback);
  tft.fillRoundRect(90,145,45, 20, 1 , TFT_GREY3);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(95,160);
  tft.setTextSize(1);
  tft.print("YES");

//  tft.fillRoundRect(170,145,45, 20, 1 , TFT_WHITE);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(180,160);
  tft.setTextSize(1);
  tft.print("NO"); 
}
//void DisplayScreen_3(){

//}
