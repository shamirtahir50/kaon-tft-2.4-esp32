
// Screen 4
void Screen_4STOPSAMPLING(){
//  tft.fillRect(75,110,155, 15, TFT_BLACK);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(82,120);
  tft.setTextSize(1);
  tft.print("STOP SAMPLING");
}
void Screen_4T1(){
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
void Screen_4T2(){
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
void DisplayScreen_4(){
  Screen_4STOPSAMPLING();
    Screen_4T1();
    delay(1000);
    Screen_4T2();
//  if(Screen2_no == true){
//    
//  }
//  if(Screen2_yes == true){
//    Screen_4T2();
//  }
  delay(1000);
}
