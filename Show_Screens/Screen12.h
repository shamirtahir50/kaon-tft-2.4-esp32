// Screen 12
void Screen_12Setupdateretries(){
    tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(80,120);
  tft.setTextSize(1);
  tft.print("UPDATE RETRIES");
}
void Screen_12Setupdateretriesvalue(int up){
  tft.pushImage(115,125,100 , 45, s5_setflowback);
  tft.setFreeFont(FSSB18);  // FreeSansbold9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(120,160);
  tft.setTextSize(1);
  tft.print(up);
  tft.setFreeFont(FSS9); 
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(170,160);
  tft.setTextSize(1);
  tft.print("TIMES");
}
void DisplayScreen_12(){
Screen_12Setupdateretries();
Screen_12Setupdateretriesvalue(10);
}
