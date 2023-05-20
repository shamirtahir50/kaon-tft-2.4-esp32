void Screen_15T1(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(130,110);
  tft.fillRoundRect(100,95,120, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print("PAUSE");
//  tft.pushImage(100,145,120, 20, fahback);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,140);
  tft.print("END");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(115,170);
  tft.print("CONTINUE");
}
void Screen_15T2(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(130,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("PAUSE");
  tft.fillRoundRect(100,125,120, 20, 1 , TFT_GREY3);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(140,140);
  tft.setTextSize(1);
  tft.print("END");
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(115,170);
  tft.print("CONTINUE");
}
void Screen_15T3(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(130,110);
//  tft.pushImage(100,115,120, 20, celback);
  tft.setTextSize(1);
  tft.print("PAUSE");
  tft.fillRoundRect(100,155,120, 20, 1 , TFT_GREY3);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,140);
  tft.print("END");
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(115,170);
  tft.print("CONTINUE");
}
void Screen_15Error(String msg){
   tft.pushImage(0,60,320, 150, midscreenback);
//  tft.fillRect(80,90,160, 80, TFT_RED);
  tft.setFreeFont(FSSB12);  // FreeSans9
  tft.setTextColor(TFT_RED);
  tft.setCursor(115,120);
  tft.setTextSize(1);
  tft.print("ERROR");
  tft.setTextColor(TFT_CYAN3);
  tft.setFreeFont(FSSB9);
  tft.setCursor(60,160);
  tft.print(msg);

}

void Screen_15DelayScreen(String delaytime){
  
  tft.pushImage(0,60,320, 150, midscreenback);
//  tft.fillRect(80,90,160, 80, TFT_RED);
  tft.setFreeFont(FSS12);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(90,120);
  tft.setTextSize(1);
  tft.print("STARTING IN");
//  tft.pushImage(120,115,120, 40, restartback);
tft.pushImage(115,130,100, 25, restartback);
  tft.setTextSize(1);
  tft.setFreeFont(FSSB12);
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(115,150);
  tft.print(delaytime);
}
void Screen_15DelayUpdate(String delaytime){
//  tft.pushImage(195,115,110, 40, restartback);
tft.pushImage(115,130,100, 25, restartback);
  tft.setTextSize(1);
  tft.setFreeFont(FSSB12);
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(115,150);
  tft.print(delaytime);
}
void Screen_15Restart(){
  
  tft.pushImage(0,60,320, 150, midscreenback);
//  tft.fillRect(80,90,160, 80, TFT_RED);
  tft.setFreeFont(FSSB12);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(90,140);
  tft.setTextSize(1);
  tft.print("Restarting ... ");
}
