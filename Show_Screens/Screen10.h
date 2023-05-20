
// Screen 10
void Screen_10TnD(){
     tft.pushImage(0,60,320, 150, midscreenback);
  tft.setFreeFont(FSSB12);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(95,90);
  tft.setTextSize(1);
  tft.print("TIME & DATE");
}
void Screen_10Time(){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(140,115);
  tft.setTextSize(1);
  tft.print("Hr : Min");
}
void Screen_10Timevalue(int h,int m,int s){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(145,140);
  tft.setTextSize(1);
  tft.pushImage(145,125,22, 20, hrback);
  tft.print(h);
  tft.print("   : ");
  tft.setCursor(180,140);
  tft.pushImage(180,125,22, 20,minback);
  tft.print(m);
}
void Screen_10TimevalueT1(int h,int m,int s){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(145,140);
  tft.setTextSize(1);
  tft.fillRoundRect(145,125,22, 20, 1 , TFT_GREY3);
  tft.print(h);
  tft.setTextColor(TFT_CYAN3);
  tft.pushImage(180,125,22, 20,minback);
  tft.print("   : ");
  tft.setCursor(180,140);
  tft.print(m);
}
void Screen_10TimevalueT2(int h,int m,int s){
  tft.setFreeFont(FSSB9);  // FreeSans9
  
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(145,140);
  tft.setTextSize(1);
  tft.pushImage(145,125,22, 20, hrback);
  tft.print(h);
  tft.fillRoundRect(180,125,22, 20, 1 , TFT_GREY3);
  tft.print("   : ");
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(180,140);
  tft.print(m);
  
}
void Screen_10SetTimenDate(float td){

 tft.pushImage(115,125,100 , 50, s5_setflowback);
  tft.setFreeFont(FSSB18);  // FreeSansbold9
  tft.setTextColor(TFT_GREY3);
  tft.setCursor(120,160);
  tft.setTextSize(1);
  tft.print(td);
}
void Screen_10Date(){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(105,170);
  tft.setTextSize(1);
  tft.print("DD / MM / YY");
}
void Screen_10Datevalue(int d,int m,int y){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(115,195);
   tft.pushImage(115,180,22, 20,  dayback);
  tft.setTextSize(1);
  tft.print(d);
  tft.print("   / ");
  tft.pushImage(150,180,22, 20, monback);
  tft.setCursor(150,195);
  tft.print(m);
  tft.print("   / ");
  tft.setCursor(185,195);
   tft.pushImage(185,180,42, 20,  yearback);
  tft.print(y);
}
void Screen_10DatevalueT1(int d,int m,int y){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_WHITE);
  tft.setCursor(115,195);
  tft.fillRoundRect(115,180,22, 20, 1 , TFT_GREY3);
  tft.setTextSize(1);
  tft.print(d);
  tft.setTextColor(TFT_CYAN3);
  tft.print("   / ");
  tft.pushImage(150,180,22, 20, monback);
  tft.setCursor(150,195);
  tft.print(m);
  tft.print("   / ");
  tft.pushImage(185,180,42, 20,  yearback);
  tft.setCursor(185,195);
  tft.print(y);
}
void Screen_10DatevalueT2(int d,int m,int y){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(115,195);
  tft.pushImage(115,180,22, 20,  dayback);
  tft.setTextSize(1);
  tft.print(d);
  tft.print("   / ");
  tft.fillRoundRect(150,180,22, 20, 1 , TFT_GREY3);
  tft.setCursor(150,195);
  tft.setTextColor(TFT_WHITE);
  tft.print(m);
  tft.setTextColor(TFT_CYAN3);
  tft.print("   / ");
  tft.pushImage(185,180,42, 20, yearback);
  tft.setCursor(185,195);
  tft.print(y);
}
void Screen_10DatevalueT3(int d,int m,int y){
  tft.setFreeFont(FSSB9);  // FreeSans9
  tft.setTextColor(TFT_CYAN3);
  tft.setCursor(115,195);
  tft.pushImage(115,180,22, 20,  dayback);
  tft.setTextSize(1);
//  tft.setTextColor(TFT_CYAN3);
  tft.print(d);
  tft.print("   / ");
  tft.pushImage(150,180,22, 20,  monback);
  tft.setCursor(150,195);
  tft.print(m);
  tft.print("   / ");
  tft.setTextColor(TFT_WHITE);
  tft.fillRoundRect(185,180,42, 20, 1 , TFT_GREY3);
  tft.setCursor(185,195);
  tft.print(y);
}
void DisplayScreen_10(){

}
