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
//   if(Screen8_enter == true && settings_transition == 3 && Screen8 ==  true){
//    Screen2_enter = false;
//    Screen8_enter = false;
//    Screen2_down = false;
//    Screen2_up = false;
//    Screen2 = false;  
//    Screen3 = false;
//    Screen5 = false;
//    Screen6 = false;
//    Screen7 = false;
//    Screen8 = false;
//    Screen9 = false;
//    Screen10 = false;
//    Screen11 = false;
//    Screen12 = true;
//    Screen_12Setupdateretries();
////    flowrate = 00.00;
////    Screen_10SetTimenDate(flowrate);
//  }
//  if(Screen12 == true && Screen2_up == true){
//      Screen2_up = false;
//      Screen2_down = false;
//      flowrate = flowrate + 0.10;
//      Screen_10SetTimenDate(flowrate);
//    }
//  if(Screen12 == true && Screen2_down == true){
//      Screen2_up = false;
//      Screen2_down = false;
//      flowrate = flowrate - 0.10;
//      Screen_10SetTimenDate(flowrate);
//   }
//  if(Screen8_enter == true && Screen12 == true){
//    Screen8_enter = false;
//    Screen2 = false;
//    Screen8 = true;
//    Screen9 = false;
//    Screen11 = false;
//    Screen10 = false;
//    Screen12 = false;
//    Screen_8T0();
//  }
Screen_12Setupdateretries();
Screen_12Setupdateretriesvalue(10);
}
