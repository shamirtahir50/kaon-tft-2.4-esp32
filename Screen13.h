// Screen 13
void Screen_13Setwebdataoption(){
   tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(90,90);
  tft.setTextSize(1);
  tft.print("FACTORY RESET");
}
void Screen_13webdataoptionT1(){
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(140,130);
  tft.fillRoundRect(100,115,120, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print("YES");
  
  tft.pushImage(100,145,120, 20, fahback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(145,160);
  tft.setTextSize(1);
  tft.print("NO");
}
void Screen_13webdataoptionT2(){
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(140,130);
  tft.pushImage(100,115,120, 20, celback);

  tft.setTextSize(1);
  tft.print("YES");
  tft.fillRoundRect(100,145,120, 20, 1 , TFT_GREY3);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(145,160);
  tft.setTextSize(1);
  tft.print("NO");
}
