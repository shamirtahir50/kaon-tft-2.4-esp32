

// Screen 2
void Screen_2T0(){
// Transition 1
//  Screen_2();
  // List
  // 1
//  tft.pushImage(40,80,15, 125, s2_pointerback);
//  tft.fillTriangle(40,80,40,100,50,90,TFT_CYAN3);
 tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSS12);
  tft.setCursor(55,100);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("SELECT FLOW RATE");
  // 2
  tft.setFreeFont(FSS12);
  tft.setCursor(55,125);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("CALIBRATE");
  // 3
  tft.setFreeFont(FSS12);
  tft.setCursor(55,150);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("RUNNING TIME");
  // 4
  tft.setFreeFont(FSS12);
  tft.setCursor(55,175);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("START SAMPLING");
  // 5
  tft.setFreeFont(FSS12);
  tft.setCursor(55,200);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("SETTINGS");
  
}
void Screen_2T1(){
// Transition 1
//  Screen_2();
  // List
  // 1
  tft.pushImage(40,60,15, 150, triback);
  tft.fillTriangle(40,80,40,100,50,90,TFT_CYAN3);
}
void Screen_2T2(){
// Transition 2
//  Screen_2();
  // List
  // 1
  tft.pushImage(40,60,15, 150, triback);
//  tft.setFreeFont(FSS12);
//  tft.setCursor(55,100);
//  tft.setTextColor(TFT_CYAN3);
//  tft.setTextSize(1);
//  tft.print("START SAMPLING");
//  // 2
  tft.fillTriangle(40,105,40,125,50,115,TFT_CYAN3);

}
void Screen_2T3(){
// Transition 3
//  Screen_2();
  // List
  // 1
  tft.pushImage(40,60,15, 150, triback);

  tft.fillTriangle(40,130,40,150,50,140,TFT_CYAN3);

}

void Screen_2T4(){

  tft.pushImage(40,60,15, 150, triback);

  tft.fillTriangle(40,155,40,175,50,165,TFT_CYAN3);

}

void Screen_2T5(){

  tft.pushImage(40,60,15, 150, triback);

  tft.fillTriangle(40,180,40,200,50,190,TFT_CYAN3);
}
void DisplayScreen_2(){
  
  
}
