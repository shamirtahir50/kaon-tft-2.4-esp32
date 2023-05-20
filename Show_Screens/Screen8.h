// Screen 8
void Screen_8T0(){
// Transition 0
//  Screen_8();
  // List
  // 1
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS10);
  tft.setCursor(55,80);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("FLOW MODES");
  
  // 2
  tft.setCursor(55,105);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("SET DELAY TIME");
  
  // 3
  tft.setCursor(55,130);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("TIME & DATE");
  
  // 4
  tft.setCursor(55,155);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("UNITS");
  
  // 5
  tft.setCursor(55,180);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("CALIBRATION MODE");
  
   // 6
  tft.setCursor(55,205);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("RESTART SETTINGS");
//  tft.print("BACK");
}
void Screen_8T0_1(){
// Transition 0
//  Screen_8();
  // List
  // 1
  tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS10);
  tft.setCursor(55,80);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("SET DELAY TIME");
//  tft.print("FLOW MODES");
  
  // 2
  tft.setCursor(55,105);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("TIME & DATE");
  
  
  // 3
  tft.setCursor(55,130);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("UNITS");
  
  // 4
  tft.setCursor(55,155);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("CALIBRATION MODE");
  
  
  // 5
  tft.setCursor(55,180);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("RESTART SETTINGS");
  
   // 6
  tft.setCursor(55,205);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("DISPLAY SETTINGS");
  
  
//  tft.print("BACK");
}
void Screen_8T1(){
// Transition 1
//  Screen_8();
  // List
  // 1
//   tft.pushImage(40,80,15, 125, s2_pointerback);
//   tft.fillRect(40,60,15, 152, TFT_WHITE);
//  tft.pushImage(40,60,15, 151, pointimg);
  
//  tft.pushImage(0,60,320, 150, midscreenback);
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
void Screen_8T7(){
  tft.pushImage(0,60,320, 150, midscreenback);
  
  tft.setFreeFont(FSS10);
  tft.setCursor(55,80);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("SET DELAY TIME");
  // 2
  tft.setCursor(55,105);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("TIME & DATE");
  
  // 3
  tft.setCursor(55,130);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("UNITS");
  
  
  // 4
  tft.setCursor(55,155);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("CALIBRATION MODE");
  
  
  // 5
  tft.setCursor(55,180);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("RESTART SETTINGS");
  
  
   // 6
  tft.setCursor(55,205);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("DISPLAY SETTINGS");
  tft.fillTriangle(40,190,40,210,50,200,TFT_CYAN3);

}
void Screen_8T8(){
tft.pushImage(0,60,320, 150, midscreenback);
  
  tft.setFreeFont(FSS10);
  tft.setCursor(55,80);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("TIME & DATE");
  // 2
  tft.setCursor(55,105);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("UNITS");
  
  // 3

  tft.setCursor(55,130);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("CALIBRATION MODE");
  
  
  // 4

  tft.setCursor(55,155);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("RESTART SETTINGS");
  
  
  // 5
  tft.setCursor(55,180);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("DISPLAY SETTINGS");
  
  
   // 6

  tft.setCursor(55,205);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("BACK");
  tft.fillTriangle(40,190,40,210,50,200,TFT_CYAN3);
}
