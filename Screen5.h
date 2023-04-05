
// Screen 5
void Screen_5Setflow(String flowunit){
 tft.pushImage(0,60,320, 150, midscreenback);
//  tft.fillRect(115,110,90, 15, TFT_BLACK);
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.setCursor(175,115);
  if(flowunit[0] == 'C'){
    tft.print("CC/M");
    tft.setCursor(115,115);
    tft.print("FLOW");
  }
  else if(flowunit[0] == 'm'){
    tft.setCursor(170,115);
    tft.print("mL/M");
    tft.setCursor(110,115);
    tft.print("FLOW");
  }
  else{
    tft.print("L/M");
    tft.setCursor(115,115);
    tft.print("FLOW");
  }
}
void Screen_5Setflowvalue(double flow,String flowunit){
  
  tft.setFreeFont(FSSB24);  // FreeSansbold9
  tft.setTextColor(TFT_GREY3);
  
  tft.setTextSize(1);
  if(flowunit[0] == 'C' || flowunit[0] == 'm'){
    tft.pushImage(80,120,200 , 50, setflowbackcc);
    tft.setCursor(95,160);
    if(flow<10000){
      tft.setCursor(115,160);
    }
    int temp = int(flow);
    tft.print(temp);
  }
  else{
    tft.pushImage(80,120,200 , 50, setflowbackcc);
    tft.setCursor(115,160);
    tft.print(flow);
  }
  
}
//void Screen_5CONFIRMCALIBRATE(){
////  tft.fillRoundRect(65,100,185, 70, 3 , TFT_CYAN1);
// tft.pushImage(0,60,320, 150, midscreenback);
//  tft.setFreeFont(FSSB9);  // FreeSansbold9
//  tft.setTextColor(TFT_CYAN3);
//  tft.setCursor(40,120);
//  tft.setTextSize(1);
//  tft.print("CONTINUE TO CALIBRATE");
//  
//}
//void Screen_CONFIRMCALIBRATET1(){
//  tft.pushImage(80,145,140, 20, s3_yesnoback);
//  tft.setFreeFont(FSS9);  // FreeSans9
//  tft.setTextColor(TFT_GREY3);
//  tft.setCursor(95,160);
//  tft.setTextSize(1);
//  tft.print("YES");
//
//  tft.fillRoundRect(170,145,45, 20, 1 , TFT_GREY3);
//  tft.setFreeFont(FSS9);  // FreeSans9
//  tft.setTextColor(TFT_WHITE);
//  tft.setCursor(180,160);
//  tft.setTextSize(1);
//  tft.print("NO");
//}
//void Screen_5CONFIRMCALIBRATET2(){
//  tft.pushImage(80,145,140, 20, s3_yesnoback);
//  tft.fillRoundRect(90,145,45, 20, 1 , TFT_GREY3);
//  tft.setFreeFont(FSS9);  // FreeSans9
//  tft.setTextColor(TFT_WHITE);
//  tft.setCursor(95,160);
//  tft.setTextSize(1);
//  tft.print("YES");
//
////  tft.fillRoundRect(170,145,45, 20, 1 , TFT_WHITE);
//  tft.setFreeFont(FSS9);  // FreeSans9
//  tft.setTextColor(TFT_GREY3);
//  tft.setCursor(180,160);
//  tft.setTextSize(1);
//  tft.print("NO"); 
//}
void Screen_5PERMISSIONCALIBRATE(){
  tft.fillRoundRect(65,100,185, 70, 3 , TFT_CYAN1);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(40,120);
  tft.setTextSize(1);
  tft.print("CONTINUE TO CALIBRATE");
  
}
void Screen_5PERMISSIONCALIBRATET1(){
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
void Screen_5PERMISSIONCALIBRATET2(){
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
void Screen_5PERMISSIONRUNTIME(){
//  tft.fillRoundRect(65,100,185, 70, 3 , TFT_CYAN1);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(40,120);
  tft.setTextSize(1);
  tft.print("CONTINUE TO RUNTIME");
  
}
void Screen_5PERMISSIONRUNTIMET1(){
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
void Screen_5PERMISSIONRUNTIMET2(){
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
