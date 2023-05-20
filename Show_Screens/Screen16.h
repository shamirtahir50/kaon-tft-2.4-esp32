void Screen_16calibrationoption(){
   tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(70,90);
  tft.setTextSize(1);
  tft.print("CALIBRATION MODE");
}
void Screen_16calibrationoptionT1(){
  tft.setFreeFont(FSS09);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(117,130);
  tft.fillRoundRect(100,115,120, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print("Auto-calibrate");
  
  tft.pushImage(100,145,120, 20, fahback);
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(117,160);
  tft.setTextSize(1);
  tft.print("Man-calibrate");
}
void Screen_16calibrationoptionT2(){
  tft.setFreeFont(FSS09);  // FreeSans9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(117,130);
  tft.pushImage(100,115,120, 20, celback);

  tft.setTextSize(1);
  tft.print("Auto-calibrate");
  tft.fillRoundRect(100,145,120, 20, 1 , TFT_GREY3);
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(117,160);
  tft.setTextSize(1);
  tft.print("Man-calibrate");
}
