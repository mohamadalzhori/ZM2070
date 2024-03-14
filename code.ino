

/////defining special characters 
byte c1[] = {B11111,B11111,B11100,B11100,B00000,B00000,B00000,B00000};//1
byte c2[] = {B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111};//2
byte c3[] = {B11111,B11111,B00011,B00111,B01110,B11100,B11000,B00000};//3
byte c4[] = {B00000,B00001,B00011,B00111,B01110,B11100,B11111,B11111};//4
byte c5[] = {B11111,B11111,B00000,B00000,B00000,B00000,B11111,B11111};//5
byte c6[] = {B00000,B00000,B00000,B00000,B00111,B00111,B11111,B11111};//6
byte fire[] = {B00000,B00100,B01110,B01111,B00111,B00110,B01110,B11111};
byte cooling[] = {B00000,B00000,B01100,B00101,B11111,B10100,B00110,B00000};





// Seting up the LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);


//  EEPROM for storing important data
#include <EEPROM.h>


// Libraries needed for the sensor
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


//////////////////////////////////////////////////////// still do not know
unsigned long previousTime=0;//timer 1
//unsigned long LcdReset=0;




int page; //page number
int delayT=3000;// Time to assure temp change in fans

// Some bools to detect temp change with delayT
bool a,e=1;//fan 1
bool b,f=1;//fan 2 
bool c,g=1;//fan 3
bool d,h=1;//fan 4
bool i,l=1;//fan 5
bool s,r=1; //alarm
bool k,n=1;//heater
bool p,o=1;//cooling

//bool q;
//bool y,x;


// Some bools to deal with ON & OFF
int w=1;
int v=1;
int u=1;
int t=1;
int z=1;


// Some Variables to store time. need to detect temp change with delayT
int T1;
int T2;
int T3;
int T4;
int T5;
int T6;
int T7;
int T9;//alarm
int TST;//alarm

byte maxPage = 14;
//////////////////////////////////////////////////////////////////


// Connecting Code Vaiables with EEPROM
float F1=EEPROM.read(1);
float F2=EEPROM.read(2);
float F3=EEPROM.read(3);
float F4=EEPROM.read(4);
float F5=EEPROM.read(5);
float F6=EEPROM.read(6);
float ST=EEPROM.read(10;
int WC=EEPROM.read(7);//Water Cooling
int H=EEPROM.read(8);//heater
int SC=EEPROM.read(9);
int ON=EEPROM.read(11);
int OFF=EEPROM.read(12);
int timerSelect1=EEPROM.read(17);
int AR=EEPROM.read(19);//Alarm Range


void setup() {
  
  
  
  // Initiating the sensor
  sensors.begin();

  // Initiating the LCD and creating Custom characters 
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, c1);
  lcd.createChar(2, c2);
  lcd.createChar(3, c3);
  lcd.createChar(4, c4);
  lcd.createChar(5, c5);
  lcd.createChar(6, c6);
  lcd.createChar(7, fire);
  lcd.createChar(8, cooling);


  // Defining the Pins
  pinMode(22,OUTPUT);//fan 1
  pinMode(24,OUTPUT);//fan 2
  pinMode(26,OUTPUT);//fan 3
  pinMode(28,OUTPUT);//fan 4
  pinMode(30,OUTPUT);//fan 5
  pinMode(32,OUTPUT);//cooling
  pinMode(34,OUTPUT);//alarm 
  pinMode(36,OUTPUT);//heater
  pinMode(40,OUTPUT);// set button  
  pinMode(42,OUTPUT);//+ button 
  pinMode(43,OUTPUT);//- button

  // Playing the animation
  logo();
  delay(3000);
  lcd.clear();
    
    
    
}

void loop() {

  // Getting the temperature
  sensors.requestTemperatures();
  float T = sensors.getTempCByIndex(0) + SC;

  /*
  if(millis()-LcdReset > 4000){
    lcd.begin(16, 2);
    LcdReset=millis();
  }*/

  // Next Page. if maxPage is reached go back
  if(digitalRead(40)==1){
  page++;
  lcd.clear();
  if(page==maxPage){page=0;}}



     
    
  ////////////  ON
  if(e==1){if(a==0){if((T-ST)>F1){T1=millis();a=1;}}}
  if(a==1){if(millis()-T1>delayT){if((T-ST)>F1){digitalWrite(22,0);}T1=0;a=0;e=0;}}//fan 1

  if(f==1){if(b==0){if((T-ST)>F2){T2=millis();b=1;}}}
  if(b==1){if(millis()-T2>delayT){if((T-ST)>F2){digitalWrite(24,0);}T2=0;b=0;f=0;}}//fan 2

  if(g==1){if(c==0){if((T-ST)>F3){T3=millis();c=1;}}}
  if(c==1){if(millis()-T3>delayT){if((T-ST)>F3){digitalWrite(26,0);}T3=0;c=0;g=0;}}//fan 3

  if(h==1){if(d==0){if((T-ST)>F4){T4=millis();d=1;}}}
  if(d==1){if(millis()-T4>delayT){if((T-ST)>F4){digitalWrite(28,0);}T4=0;d=0;h=0;}}//fan 4

  if(l==1){if(i==0){if((T-ST)>F5){T5=millis();i=1;}}}
  if(i==1){if(millis()-T5>delayT){if((T-ST)>F5){digitalWrite(30,0);}T5=0;i=0;l=0;}}//fan 5 

  //////////////

  if(n==1){if(k==0){if((ST-T)>H){T7=millis();k=1;}}}
  if(k==1){if(millis()-T7>delayT){if((ST-T)>H){digitalWrite(36,0);}T7=0;k=0;n=0;}}///heater

  if(o==1){if(p==0){if((T-ST)>WC){T6=millis();p=1;}}}
  if(p==1){if(millis()-T6>delayT){if((T-ST)>WC){digitalWrite(32,0);}T6=0;p=0;o=0;}}//cooling


  /////////////// ALARM


  if(r==1){if(s==0){TST=T-ST;if((abs(TST))>AR){T9=millis();s=1;}}}
  if(s==1){if(millis()-T9>delayT){TST=T-ST;if((abs(TST))>AR){digitalWrite(34,1);}T1=0;s=0;r=0;}}/////////////////////
  TST=T-ST;
  if((abs(TST))<AR){digitalWrite(34,0);r=1;}
  ////////////////

  
  ///////////////////   OFF
  if(timerSelect1 !=1 ){if((T-ST)<F1){digitalWrite(22,1);e=1;}}//fan1
  if(timerSelect1 !=2 ){if((T-ST)<F2){digitalWrite(24,1);f=1;}}//fan2
  if(timerSelect1 !=3 ){if((T-ST)<F3){digitalWrite(26,1);g=1;}}//fan3
  if(timerSelect1 !=4 ){if((T-ST)<F4){digitalWrite(28,1);h=1;}}//fan4
  if(timerSelect1 !=5 ){if((T-ST)<F5){digitalWrite(30,1);l=1;}}//fan5
 
  if((T-ST)<WC){p=0;o=1;digitalWrite(32,1);}
  if(T>ST){digitalWrite(36,1);lcd.setCursor(15,0);lcd.print(" ");n=1;}


if(ON !=0 && OFF !=0){

if(timerSelect1==1){if((T-ST)<F1){if(w==0){  if(millis()-previousTime >=ON*1000){digitalWrite(22,1);previousTime=millis();w=1;}}if(w==1){if(millis()-previousTime>=OFF*1000){digitalWrite(22,0);previousTime=millis();w=0;}}}}    
   
if(timerSelect1==2){if((T-ST)<F2){if(v==0){  if(millis()-previousTime >=ON*1000){digitalWrite(24,1);previousTime=millis();v=1;}}if(v==1){if(millis()-previousTime>=OFF*1000){digitalWrite(24,0);previousTime=millis();v=0;}}}}    

if(timerSelect1==3){if((T-ST)<F3){if(u==0){  if(millis()-previousTime >=ON*1000){digitalWrite(26,1);previousTime=millis();u=1;}}if(u==1){if(millis()-previousTime>=OFF*1000){digitalWrite(26,0);previousTime=millis();u=0;}}}}

if(timerSelect1==4){if((T-ST)<F4){if(t==0){  if(millis()-previousTime >=ON*1000){digitalWrite(28,1);previousTime=millis();t=1;}}if(t==1){if(millis()-previousTime>=OFF*1000){digitalWrite(28,0);previousTime=millis();t=0;}}}}

if(timerSelect1==5){if((T-ST)<F5){if(z==0){  if(millis()-previousTime >=ON*1000){digitalWrite(30,1);previousTime=millis();z=1;}}if(z==1){if(millis()-previousTime>=OFF*1000){digitalWrite(30,0);previousTime=millis();z=0;}}}}

}




  
  if(page==0){
    lcd.setCursor(0, 0);
    lcd.print("Temp :");

    lcd.setCursor(8, 0);
    lcd.print(T);
    ////////// Showing indicator
  if(digitalRead(22)==0){lcd.setCursor(0,1);lcd.print("1");}else{lcd.setCursor(0,1);lcd.print(" ");}
  if(digitalRead(24)==0){lcd.setCursor(2,1);lcd.print("2");}else{lcd.setCursor(2,1);lcd.print(" ");}
  if(digitalRead(26)==0){lcd.setCursor(4,1);lcd.print("3");}else{lcd.setCursor(4,1);lcd.print(" ");}
  if(digitalRead(28)==0){lcd.setCursor(6,1);lcd.print("4");}else{lcd.setCursor(6,1);lcd.print(" ");}
  if(digitalRead(30)==0){lcd.setCursor(8,1);lcd.print("5");}else{lcd.setCursor(8,1);lcd.print(" ");}

  if(digitalRead(32)==0){lcd.setCursor(10,1);lcd.print("C");}else{lcd.setCursor(10,1);lcd.print(" ");}//cooling
  if(digitalRead(36)==0){lcd.setCursor(12,0);lcd.print("H");}else{lcd.setCursor(12,0);lcd.print(" ");}//heater
  if(digitalRead(34)==1){lcd.setCursor(14,0);lcd.print("A");}else{lcd.setCursor(14,0);lcd.print(" ");}//alarm


    }


if(page==1){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Temp: ");//        SET TEMP
      lcd.setCursor(10, 1);
    lcd.print(ST);
    //lcd.setCursor(10+getLength(ST), 1);
    lcd.print("  ");
    if(digitalRead(42)==0){ST=ST+0.5;if(ST>50){ST=0;}EEPROM.update(10,ST);}
    if(digitalRead(43)==0){ST=ST-0.5;if(ST<0){ST=50;}EEPROM.update(10,ST);}
  }
  
  if(page==2){
    lcd.setCursor(0, 0);
    lcd.print("Fan 1: ");//             FAN 1
    lcd.setCursor(10, 0);
    lcd.print(F1);
    
    if(digitalRead(42)==0){F1=F1+0.5;if(F1>10){F1=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(1,F1);}
    if(digitalRead(43)==0){F1=F1-0.5;if(F1<0){F1=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(1,F1);}
  }

  if(page==3){
    lcd.setCursor(0, 0);
    lcd.print("Fan 2: ");//             FAN 2
    lcd.setCursor(10, 0);
    lcd.print(F2);
    
    if(digitalRead(42)==0){F2=F2+0.5;if(F2>10){F2=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(2,F2);}
    if(digitalRead(43)==0){F2=F2-0.5;if(F2<0){F2=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(2,F2);}
  }

  if(page==4){
    lcd.setCursor(0, 0);
    lcd.print("Fan 3: ");//             FAN 3
    lcd.setCursor(10, 0);
    lcd.print(F3);
    
    if(digitalRead(42)==0){F3=F3+0.5;if(F3>10){F3=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(3,F3);}
    if(digitalRead(43)==0){F3=F3-0.5;if(F3<0){F3=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(3,F3);}
  }

  if(page==5){
    lcd.setCursor(0, 0);
    lcd.print("Fan 4: ");//             FAN 4
    lcd.setCursor(10, 0);
    lcd.print(F4);
    
    if(digitalRead(42)==0){F4=F4+0.5;if(F4>10){F4=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(4,F4);}
    if(digitalRead(43)==0){F4=F4-0.5;if(F4<0){F4=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(4,F4);}
  }

  if(page==6){
    lcd.setCursor(0, 0);
    lcd.print("Fan 5: ");//             FAN 5
    lcd.setCursor(10, 0);
    lcd.print(F5);
    
    if(digitalRead(42)==0){F5=F5+0.5;if(F5>10){F5=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(5,F5);}
    if(digitalRead(43)==0){F5=F5-0.5;if(F5<0){F5=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(5,F5);}
  }

///////////////////////
  if(page==7){
    lcd.setCursor(0, 0);
    lcd.print("Cooling : ");//             Cooling
    lcd.setCursor(10, 0);
    lcd.print(WC);
    
    if(digitalRead(42)==0){WC++;if(WC>10){WC=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(7,WC);}
    if(digitalRead(43)==0){WC--;if(WC<0){WC=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(7,WC);}
  }

 
  ///////////////////////////


  if(page==8){
    lcd.setCursor(0, 0);
    lcd.print("Heater : ");//             Heater
    lcd.setCursor(10, 0);
    lcd.print(H);
    
    if(digitalRead(42)==0){H++;if(H>10){H=0;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(8,H);}
    if(digitalRead(43)==0){H--;if(H<0){H=10;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(8,H);}
  }



  if(page==9){
    lcd.setCursor(0, 0);
    lcd.print("Select timer ");//             timer select 1
    lcd.setCursor(15, 0);
    lcd.print(timerSelect1);

  
    
    if(digitalRead(42)==0){
      timerSelect1++;
      EEPROM.update(17,timerSelect1);
      if(timerSelect1>6){timerSelect1=1;}
    }
    if(digitalRead(43)==0){
      timerSelect1--;
      EEPROM.update(17,timerSelect1);
      if(timerSelect1<0){timerSelect1=6;}
    }}

  if(page==12){
    lcd.setCursor(0, 0);
    lcd.print("Alarm: ");//             Alarm
    lcd.setCursor(10, 0);
    lcd.print(AR);
    
    if(digitalRead(42)==0){AR++;if(AR>20){AR=-20;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(19,AR);}
    if(digitalRead(43)==0){AR--;if(AR<-20){AR=20;lcd.setCursor(11, 0);lcd.print(" ");}EEPROM.update(19,AR);}
  }
  
  
  if(page==10){
    lcd.setCursor(0, 0);
    lcd.print("Timer ON: ");//             TIMER ON
    lcd.setCursor(12, 0);
    lcd.print(ON);
    lcd.setCursor(12+getLength(ON), 0);
    lcd.print("  ");
    if(digitalRead(42)==0){ON++;if(ON>30){ON=0;}EEPROM.update(11,ON);}
    if(digitalRead(43)==0){ON--;if(ON<0){ON=30;}EEPROM.update(11,ON);}
    
  }

  if(page==11){
    lcd.setCursor(0, 0);
    lcd.print("Timer OFF: ");//             TIMER OFF
    lcd.setCursor(13, 0);
    lcd.print(OFF);
    lcd.setCursor(13+getLength(OFF), 0);
    lcd.print("  ");
    if(digitalRead(42)==0){OFF++;if(OFF>30){OFF=0;}EEPROM.update(12,OFF);}
    if(digitalRead(43)==0){OFF--;if(OFF<0){OFF=30;}EEPROM.update(12,OFF);}
  }

  


  if(page==13){
    lcd.setCursor(0, 0);
    lcd.print("Calibration: ");//     CALIBRATION
    lcd.setCursor(0, 1);
    lcd.print(SC);
    if(SC>0){lcd.setCursor(getLength(SC), 1);lcd.print("  ");}
    if(SC>-10 && SC<0){lcd.setCursor(2,1);lcd.print("  ");}
    if(digitalRead(42)==0){SC++;if(SC>50){SC=-50;}EEPROM.update(9,SC);}
    if(digitalRead(43)==0){SC--;if(SC<-50){SC=50;}EEPROM.update(9,SC);}
  }



}



int getLength(int value){
  int digits=1;
  int divided=value/10;
  while (divided > 0) {
  divided = divided /10;
  digits++; 
  }
  return digits;}
void logo(){
      blnk();
    Weeee("i",3);blnk();
    Weeee("a",4);blnk();
    Weeee("d",5);blnk();
    Weeee("E",7);blnk();
    Weeee("l",8);blnk();
    Weeee("e",9);blnk();
    Weeee("c",10);blnk();
    Weeee("t",11);blnk();
    Weeee("r",12);blnk();
    Weeee("i",13);blnk();
    Weeee("c",14);blnk();
    lcd.setCursor(0,0);lcd.write(1);lcd.setCursor(1,0);lcd.write(2);lcd.setCursor(2,0);lcd.write(3);lcd.setCursor(0,1);lcd.write(4);lcd.setCursor(1,1);lcd.write(5);lcd.setCursor(2,1);lcd.write(6);

  }
void Weeee(String txt,int nd){
  for(int i=16;i>nd;i--){
    lcd.setCursor(i,1);lcd.print(txt);
    delay(50-nd);
    lcd.setCursor(i,1);lcd.print(" ");
   }
   lcd.setCursor(nd,1);lcd.print(txt);}
  
void blnk(){
   lcd.setCursor(0,0);lcd.write(1);lcd.setCursor(1,0);lcd.write(2);lcd.setCursor(2,0);lcd.write(3);lcd.setCursor(0,1);lcd.write(4);lcd.setCursor(1,1);lcd.write(5);lcd.setCursor(2,1);lcd.write(6);
   delay(100);
   lcd.setCursor(0,0);lcd.print("   ");lcd.setCursor(0,1);lcd.print("   ");
   delay(100);}

   
