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
