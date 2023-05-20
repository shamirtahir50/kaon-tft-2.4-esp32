// Screen 11
void Screen_11Setunits(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(55,100);
  tft.print("TEMPERATURE");
  tft.setCursor(55,130);
  tft.setTextSize(1);
  tft.print("FLOW RATE");
  tft.setCursor(55,160);
  tft.setTextSize(1);
  tft.print("BACK PRESSURE");
  tft.setCursor(55,190);
  tft.setTextSize(1);
  tft.print("BACK");

}
void Screen_11SetunitsT1(){
    tft.pushImage(40,60,15, 150, triback);
  tft.fillTriangle(40,85,40,105,50,95,TFT_CYAN3);
}
void Screen_11SetunitsT2(){
 tft.pushImage(40,60,15, 150, triback);
  tft.fillTriangle(40,115,40,135,50,125,TFT_CYAN3);
}
void Screen_11SetunitsT3(){
 tft.pushImage(40,60,15, 150, triback);
  tft.fillTriangle(40,145,40,165,50,155,TFT_CYAN3);
}
void Screen_11SetunitsT4(){
 tft.pushImage(40,60,15, 150, triback);
  tft.fillTriangle(40,175,40,195,50,185,TFT_CYAN3);
}
void Screen_11tempunitsoptionT1(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(120,110);
  tft.fillRoundRect(100,95,120, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print("CELSIUS");
//  tft.pushImage(100,145,120, 20, fahback);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(105,140);
  tft.print("FAHRENHEIT");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(125,170);
  tft.print("KELVIN");
}
void Screen_11tempunitsoptionT2(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(120,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("CELSIUS");
  tft.fillRoundRect(100,125,120, 20, 1 , TFT_GREY3);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(105,140);
  tft.setTextSize(1);
  tft.print("FAHRENHEIT");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(125,170);
  tft.print("KELVIN");
}
void Screen_11tempunitsoptionT3(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(120,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("CELSIUS");
  tft.fillRoundRect(100,155,120, 20, 1 , TFT_GREY3);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(105,140);
  tft.print("FAHRENHEIT");
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(125,170);
  tft.print("KELVIN");
}
void Screen_11flowunitsoptionT1(){ 
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(130,110);
  tft.fillRoundRect(100,95,120, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print("CC/M");
//  tft.pushImage(100,145,120, 20, fahback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,140);
  tft.print("L/M");
    tft.setCursor(130,170);
  tft.print("mL/M");
}
void Screen_11flowunitsoptionT2(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(130,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("CC/M");
  tft.fillRoundRect(100,125,120, 20, 1 , TFT_GREY3);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(140,140);
  tft.print("L/M");
  tft.setCursor(130,170);
  tft.setTextColor(TFT_GREY3);
  tft.print("mL/M");
}

void Screen_11flowunitsoptionT3(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(130,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("CC/M");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,140);
  tft.print("L/M");
  tft.fillRoundRect(100,155,120, 20, 1 , TFT_GREY3);
  tft.setCursor(130,170);
  tft.setTextColor(TFT_WHITE);
  tft.print("mL/M");
}
void Screen_11bpunitsoptionT1(){ 
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(145,110);
  tft.fillRoundRect(100,95,120, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print("KPA");
  
//  tft.pushImage(100,145,120, 20, fahback);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,140);
  tft.print("in.H20");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(135,170);
  tft.print("cm.H20");
}
void Screen_11bpunitsoptionT2(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(145,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("KPA");
  tft.fillRoundRect(100,125,120, 20, 1 , TFT_GREY3);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(140,140);
  tft.print("in.H20");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(135,170);
  tft.print("cm.H20");
}
void Screen_11bpunitsoptionT3(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(145,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("KPA");
  tft.fillRoundRect(100,155,120, 20, 1 , TFT_GREY3);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,140);
  tft.print("in.H20");
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(135,170);
  tft.print("cm.H20");
}

void DisplayScreen_11(){

}
