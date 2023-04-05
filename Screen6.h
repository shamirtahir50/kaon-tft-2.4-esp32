// Screen 6 

void Screen_6Calibrate(){
    tft.pushImage(0,60,320, 150, midscreenback);
//  tft.fillRect(115,110,90, 15, TFT_BLACK);
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(110,115);
  tft.setTextSize(1);
  tft.print("CALIBRATE");
}
void Screen_6Showflowvalue(double flow,String flowunit){

  tft.pushImage(110,120,120 , 50, flowvalueback);
  tft.setFreeFont(FSSB24);  // FreeSansbold9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(115,160);
  tft.setTextSize(1);
  if(flowunit[0] == 'C' || flowunit[0] == 'm'){
    flow = flow * 1000;
  }
  tft.print(flow);
}

void DisplayScreen_6(){

}
