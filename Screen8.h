// Screen 8
void Screen_8T0(){
// Transition 0
//  Screen_8();
  // List
  // 1
   tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS9);
  tft.setCursor(55,80);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("SET DELAY TIME");
  // 2
  tft.setFreeFont(FSS9);
  tft.setCursor(55,105);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("TIME & DATE");
  // 3
  tft.setFreeFont(FSS9);
  tft.setCursor(55,130);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("UNITS");
  // 4
  tft.setFreeFont(FSS9);
  tft.setCursor(55,155);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("RESTART SETTINGS");
  // 5
  tft.setFreeFont(FSS9);
  tft.setCursor(55,180);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("FACTORY RESET");
   // 6
  tft.setFreeFont(FSS9);
  tft.setCursor(55,205);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("BACK");
}
void Screen_8T1(){
// Transition 1
//  Screen_8();
  // List
  // 1
//   tft.pushImage(40,80,15, 125, s2_pointerback);
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
  tft.pushImage(40,60,15, 151, pointimg);
  
  tft.fillTriangle(40,65,40,85,50,75,TFT_CYAN3);

}
void Screen_8T2(){
// Transition 2
//  Screen_2();
  // List
  // 1
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
   tft.pushImage(40,60,15, 151, pointimg);

  // 2
  tft.fillTriangle(40,90,40,110,50,100,TFT_CYAN3);

}
void Screen_8T3(){
// Transition 3
//  Screen_2();
  // List
  // 1
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
 tft.pushImage(40,60,15, 151, pointimg);

  tft.fillTriangle(40,115,40,135,50,125,TFT_CYAN3);
}

void Screen_8T4(){
// Transition 4
//  Screen_2();
  // List
  // 1
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
tft.pushImage(40,60,15, 151, pointimg);

  tft.fillTriangle(40,140,40,160,50,150,TFT_CYAN3);

}

void Screen_8T5(){
// Transition 5
//  Screen_2();
  // List
  // 1
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
 tft.pushImage(40,60,15, 151, pointimg);

  tft.fillTriangle(40,165,40,185,50,175,TFT_CYAN3);
}
void Screen_8T6(){
// Transition 5
//  Screen_2();
  // List
  // 1
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
 tft.pushImage(40,60,15, 151, pointimg);

  tft.fillTriangle(40,190,40,210,50,200,TFT_CYAN3);

}
void DisplayScreen_8(){

}
