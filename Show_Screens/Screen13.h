//// Screen 13
//void Screen_13Setwebdataoption(){
//   tft.pushImage(0,60,320, 150, midscreenback);
//  tft.setFreeFont(FSSB9);  // FreeSans9
//  tft.setTextColor(TFT_CYAN3);
//  tft.setCursor(90,90);
//  tft.setTextSize(1);
//  tft.print("FACTORY RESET");
//}
void Screen_13flowmodes(){
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(55,100);
  tft.print("FLOW CONTROL");
  tft.setCursor(55,130);
  tft.setTextSize(1);
  tft.print("PRESSURE CONTROL");
  tft.setCursor(55,160);
  tft.setTextSize(1);
  tft.print("GAS SAMPLING");
  tft.setCursor(55,190);
  tft.setTextSize(1);
  tft.print("BACK");

}
void Screen13flowmodeconfirm(){
//  tft.fillRect(75,110,155, 15, TFT_BLACK);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(80,120);
  tft.setTextSize(1);
  tft.print("FLOW CONTROL");
}
void Screen13pressuremodeconfirm(){
//  tft.fillRect(75,110,155, 15, TFT_BLACK);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(60,120);
  tft.setTextSize(1);
  tft.print("PRESSURE CONTROL");
}
void Screen13gasmodeconfirm(){
//  tft.fillRect(75,110,155, 15, TFT_BLACK);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB9);  // FreeSansbold9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(90,120);
  tft.setTextSize(1);
  tft.print("GAS CONTROL");
}
