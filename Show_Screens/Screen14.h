// Screen 14
void displaytime(String t){
  tft.pushImage(20,15,80, 20, timeback);
  tft.setFreeFont(FSS9);  
  tft.setCursor(20,30);
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREY3);
  tft.print(t);
}
void displaydate(String d,String y){
  tft.pushImage(20,35,150, 15, dateback);
  tft.setFreeFont(FSS09);
  tft.setCursor(20,45);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  String date = d + ", " + y;
  tft.print(date);
//  tft.setCursor(100,45);
  
//  tft.print(temp);
}
void timendate(String t,String d,String y){
//  tft.pushImage(10,10,120, 40, timedateback);
  displaytime(t);
  displaydate(d,y);
}
void Screen14_flowrate(String flowmode,String flowunit){
  tft.setFreeFont(FSSB9); 
  tft.setCursor(25,90);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print(flowmode);
  tft.setFreeFont(FSS09); 
  tft.setCursor(85,90);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(flowunit);
 
}
void Screen14_flowratevalue(String ft,String bp,String bpunitkpa,String flowunit,double flow,String FlowDisplay){
//  tft.pushImage(85,80,45,15, screen14flowunit);
  double ftemp = ft.toDouble();
  if(flowunit[0] == 'C' || flowunit[0] == 'm'){
       
       ftemp = ftemp / 1000;
      }
  
  double check = (ftemp/FlowDisplay.toDouble());
//  if(check < 0.98 ||  check > 1.02){
//    FlowDisplay = ft;
////    Serial.println("No Change");
//  }
//  else if(check > 1.02 ){
//    FlowDisplay = ft;
//  }
//  else{
//  FlowDisplay = ft; 
//  }
  tft.setFreeFont(FSS09); 
  tft.setCursor(85,90);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
//  tft.print(flowunit);
//  tft.fillRect(25,100,170,45, TFT_BLACK);
  tft.pushImage(25,100,170,45, flowrateback);
  tft.setFreeFont(&FreeSansBold24pt7b);
  tft.setCursor(25,140);
  tft.setTextColor(TFT_GREY3);
  
  
  check = (ftemp/flow);
  
  if(check < 0.95 ){
    tft.setTextColor(TFT_RED);
  }
  else if(check > 1.05 ){
    tft.setTextColor(TFT_RED);
  }
  else{
    tft.setTextColor(TFT_GREY3);
  }
  
 
  tft.setTextSize(1);
  tft.print(FlowDisplay);
   tft.setFreeFont(FSSB9); 
  tft.setCursor(25,170);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("BP");
  tft.pushImage(55,155,50,20, bpback);
//  tft.fillRect(55,155,50,20, TFT_RED);
  tft.setCursor(55,170);
  tft.setFreeFont(FSSB9);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(bp);
//  tft.fillRect(105,160,55,15, TFT_RED);
  tft.pushImage(105,160,55,15, bpunit);
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(105,170);
  tft.setFreeFont(FSS09);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(bpunitkpa);
}
void timename(){
  tft.setFreeFont(FSS09);
  tft.setCursor(215,90);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("TIME");
  tft.setFreeFont(FSS09);
  tft.setCursor(250,90);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print("HOUR");
}
void timevalue(String t){
  tft.pushImage(220,95,80,25, timehourback);
  tft.setFreeFont(FSSB12);
  tft.setCursor(220,115);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(t);
}
void volumename(String volumeunit){
  tft.pushImage(220,140,100,25, volumeback);
  tft.setFreeFont(FSS09);
  tft.setCursor(215,135);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("VOLUME");
  //redraw the unit of volume at unit change
  tft.setFreeFont(FSS09);
  tft.setCursor(280,135);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(volumeunit);
}
void volumevalue(String v){
  tft.setFreeFont(FSSB12);
  tft.setCursor(220,160);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(v);
}
void leftpart(String h,String v,String volumeunit){
  timename();
  timevalue(h);
  volumename(volumeunit);
  volumevalue(v);
}

void motionname1(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(15,195);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Motion");
}
void motionvalue1(String m){
  tft.pushImage(60,180,40,30, motionback);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setCursor(60,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  double buff = m.toDouble();
  int buff1 = round(buff);
  m = String(buff1);
  tft.print(m);
}
void motionvaluepercent1(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(100,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print("%");
}
void tempname1(){
  
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(113,195);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Temp");
}
void tempvalue1(String t){
  tft.pushImage(148,180,60,30, tempback);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setCursor(148,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  double buff = t.toDouble();
  int buff1 = round(buff);
  t = String(buff1);
  tft.print(t);
}
void tempvaluecelcius1(String unit){
  tft.pushImage(208,190,12,20, tempunitback);
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(208,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(unit);
}
void humname1(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(220,195);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Hum");
}
void humvalue1(String h){
  tft.pushImage(255,180,40,30, humback);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setCursor(255,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  double buff = h.toDouble();
  int buff1 = round(buff);
  h = String(buff1);
  tft.print(h);
}
void humvaluepercent1(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(295,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print("%");
}
void beforefooter1(String m,String t,String h,String Tempunit){
  tft.pushImage(0,175,320,35, bottom);
  motionname1();
  motionvalue1(m);
  motionvaluepercent1();
  tempname1();
  tempvalue1(t);
  tempvaluecelcius1(Tempunit);
  humname1();
  humvalue1(h);
  humvaluepercent1();
}
void motionname2(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(20,195);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Motion");
}
void motionvalue2(String m){
//  tft.pushImage(60,180,40,30, motionback);
tft.pushImage(65,180,40,30, motionback2);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setCursor(65,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  double buff = m.toDouble();
  int buff1 = round(buff);
  m = String(buff1);
  tft.print(m);
}
void motionvaluepercent2(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(110,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print("%");
}
void tempname2(){
  
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(125,195);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Temp");
}
void tempvalue2(String t){
//  tft.pushImage(148,180,60,30, tempback);
tft.pushImage(165,180,40,30, tempback2);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setCursor(165,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  double buff = t.toDouble();
  int buff1 = round(buff);
  t = String(buff1);
  tft.print(t);
}
void tempvaluecelcius2(String unit){
//  tft.pushImage(208,190,12,20, tempunitback);
tft.pushImage(205,190,12,20, tempunitback2);
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(205,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print(unit);
}
void humname2(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(217,195);
  tft.setTextColor(TFT_CYAN3);
  tft.setTextSize(1);
  tft.print("Hum");
}
void humvalue2(String h){
//  tft.pushImage(255,180,40,30, humback);
tft.pushImage(250,180,40,30, humback2);
  tft.setFreeFont(&FreeSansBold18pt7b);
  tft.setCursor(250,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  double buff = h.toDouble();
  int buff1 = round(buff);
  h = String(buff1);
  tft.print(h);
}
void humvaluepercent2(){
  tft.setFreeFont(&FreeSans7pt7b);
  tft.setCursor(290,205);
  tft.setTextColor(TFT_GREY3);
  tft.setTextSize(1);
  tft.print("%");
}
void beforefooter2(String m,String t,String h,String Tempunit){
  tft.pushImage(0,175,320,35, bottom);
  motionname2();
  motionvalue2(m);
  motionvaluepercent2();
  tempname2();
  tempvalue2(t);
  tempvaluecelcius2(Tempunit);
  humname2();
  humvalue2(h);
  humvaluepercent2();
}

void DisplayScreen_14(String m,String t,String h,String f,String bp,String Tempunit,String bpunit,String flowunit,String volume,String timeh,double flow,String FlowDisplay,int flowmode){
  tft.pushImage(0,60,320, 150, midscreenback);
  String volumeunit = "LTR";
      if(flowunit[0] == 'C'){
        volumeunit = "CC";
        int buff = f.toDouble();
        int intbuffv = volume.toInt(); 
        int buffv = intbuffv * 1000;
        buff = buff * 1000;
        int buff1 = round(buff);
        f = String(buff1);
        volume = String(buffv);
      }
      if(bpunit[0] == 'i'){
        float buff = bp.toFloat();
        buff = (4.01865 * buff);
        int buff1 = round(buff);
        bp = String(buff1); 
      }
      else if(bpunit[0] == 'c'){
        float buff = bp.toFloat();
        buff = (10.1972 * buff);
        int buff1 = round(buff);
        bp = String(buff1); 
      }
      if(flowmode == 0){
          Screen14_flowrate("FLOW",flowunit);
      }
      if(flowmode == 1){
        Screen14_flowrate("INLET PRESSURE","");
      }
      if(flowmode == 2){
        Screen14_flowrate("FLOW",flowunit);
      }
  if(Tempunit[0] == 'C'){
       if(t.toInt()>=100){
        t = "-";
       }
      }
   if(Tempunit[0] == 'F'){
        double buff = t.toInt();
        buff = (buff * 9/5) + 32;
        int buff1 = round(buff);
        t = String(buff1);
      }
      if(Tempunit[0] == 'K'){
        double buff = t.toInt();
        buff = buff + 273.15;
        int buff1 = round(buff);
        t = String(buff1);
      }
      if(h.toInt()>=100){
       
        h = "-";

      }
      if(m.toInt()>=100){
       
        m = "-";

      }
      
  if(Tempunit[0] == 'F' && t.toInt() >= 100  || Tempunit[0] == 'K' && t.toInt() >= 100){
    beforefooter1(m,t,h,Tempunit);
  }
  else{
     beforefooter2(m,t,h,Tempunit);
  }
  
  leftpart(timeh,volume,volumeunit);
  Screen14_flowratevalue(f,bp,bpunit,flowunit,flow,FlowDisplay);
  if(Tempunit[0] == 'F' && t.toInt() >= 100  || Tempunit[0] == 'K' && t.toInt() >= 100){
    motionvalue1(m);
    tempvalue1(t);
    humvalue1(h);
  }
  else{
     motionvalue2(m);
  tempvalue2(t);
  humvalue2(h);
  }
}
void pausedscreen(){
    tft.setFreeFont(FSSB12);
    tft.setCursor(110,40);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(1);
    tft.print("PAUSED");
    
}
void DisplayScreen_14_Update(String m,String t,String h,String f,String bp,String Tempunit,String bpunit,String flowunit,String volume,String timeh,double flow,String FlowDisplay){
      String volumeunit = "LTR";

      if(flowunit[0] == 'C' || flowunit[0] == 'm'){
        volumeunit = "CC";
        double flowbuff = f.toDouble();
        double volbuff = volume.toDouble(); 
        flowbuff = flowbuff * 1000;
        volbuff = volbuff * 1000;
        int flowbuff1 = round(flowbuff);
        int volbuff1 = round(volbuff);
        f = String(flowbuff1);
        volume = String(volbuff1);
      }
      if(bpunit[0] == 'i'){
        float buff = bp.toFloat();
        buff = (4.01865 * buff);
        int buff1 = round(buff);
        bp = String(buff1); 
      }
      else if(bpunit[0] == 'c'){
        float buff = bp.toFloat();
        buff = (10.1972 * buff);
        int buff1 = round(buff);
        bp = String(buff1); 
      }
        if(Tempunit[0] == 'C'){
       if(t.toInt()>=100){
        t = "-";
       }
      }
      if(Tempunit[0] == 'F'){
        double buff = t.toInt();
        buff = (buff * 9/5) + 32;
        int buff1 = round(buff);
        t = String(buff1);
      }
      if(Tempunit[0] == 'K'){
        double buff = t.toInt();
        buff = buff + 273.15;
        int buff1 = round(buff);
        t = String(buff1);
      }
      if(h.toInt()>=100){
       
        h = "-";

      }
      if(m.toInt()>=100){
       
        m = "-";

      }
      leftpart(timeh,volume,volumeunit);
   if(Tempunit[0] == 'F' && t.toInt() >= 100 || Tempunit[0] == 'K' && t.toInt() >= 100){
        motionvalue1(m);
  tempvalue1(t);
  humvalue1(h);
  Screen14_flowratevalue(f,bp,bpunit,flowunit,flow,FlowDisplay);
  tempvaluecelcius1(Tempunit);
  }
  else{
      motionvalue2(m);
  tempvalue2(t);
  humvalue2(h);
  Screen14_flowratevalue(f,bp,bpunit,flowunit,flow,FlowDisplay);
  tempvaluecelcius2(Tempunit);
  }

}
