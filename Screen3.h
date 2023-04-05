
// Screen 3
void Screen_3STARTSAMPLING(){
//  tft.fillRoundRect(65,100,185, 70, 3 , TFT_CYAN1);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(75,120);
  tft.setTextSize(1);
  tft.print("START SAMPLING");
  
}
void Screen_3T1(){
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
void Screen_3T2(){
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
