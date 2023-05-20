
// Screen 7
void Screen_7Runtime(){
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(90,115);
  tft.setTextSize(1);
  tft.print("RUNNING TIME");
}
void Screen_7SetRuntime(String fulltime){

  tft.pushImage(100,125,130, 50, runtimeback);
//  tft.pushImage(115,125,100 , 48, s5_setflowback);
  tft.setFreeFont(FSSB24);  // FreeSansbold9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(100,160);
  tft.setTextSize(1);
  tft.print(fulltime);
//  tft.setCursor(155,155);
//  tft.setTextSize(1);
//  tft.print(":");
//  tft.setCursor(170,160);
//  tft.setTextSize(1);
//  tft.print(m);
   tft.setFreeFont(FSS09);  // FreeSansbold9
//  tft.setTextColor(TFT_GREY3);
  tft.setCursor(230,160);
  tft.setTextSize(1);
  tft.print("HOURS");
}
void DisplayScreen_7(){

}
