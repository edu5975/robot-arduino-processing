#include <SoftwareSerial.h>
 String instruction="";
String objective="";
String response;
boolean done=LOW;
boolean last=LOW;
boolean second=LOW;
int c=1,s=2;
int t;
SoftwareSerial espSerial(5, 6);
void setup() {
 //MOTOR VERTICAL
  pinMode(53,OUTPUT);
pinMode(51,OUTPUT);
pinMode(49,OUTPUT);
pinMode(47,OUTPUT);
//MOTOR HORIZONTAL
pinMode(52,OUTPUT);
pinMode(50,OUTPUT);
pinMode(48,OUTPUT);
pinMode(46,OUTPUT);
// Open serial communications and wait for port to open:
Serial.begin(115200);
espSerial.begin(115200);
} 
void loop() { // run over and over
  
boolean sended=HIGH;
  while (Serial.available()) {
  sended=LOW;
  char r=Serial.read();
  Serial.write(r);
  response.concat(r);
  delay(1);
  }
   if(!sended){
    if(response.equals("HR")){
      for(int i=0;i<=10;i++){
        nonestep(2);
      }
    }
    if(response.equals("HL")){
      for(int i=0;i<=10;i++){
        onestep(2);
      }
    }
    if(response.equals("VU")){
      for(int i=0;i<=10;i++){
        nonestep(1);
      }
    }
    if(response.equals("VD")){
      for(int i=0;i<=10;i++){
        onestep(1);
      }
    }
    response="";
  }
if(t==5000){
  t=0;
  String temp=String(random(1500, 4000)/100);
  String humedad=String(random(500, 1500)/100);
  String gas=String(random(500, 1500)/100);
  String laser=String(random(0, 20000)/100);
  String ultra=String(random(0, 3000)/100);
  String bateria=String(random(0, 10000)/100);
  String msg="SENS$"+temp+"$"+humedad+"$"+gas+"$"+laser+"$"+ultra+"$"+bateria;
  espSerial.println(msg);
  c++;
}else{
  t++;
}
delay(1);
}
void writee(int a,int b,int c,int d, int M){
  if(M==1){
    digitalWrite(53,a);
    digitalWrite(51,b);
    digitalWrite(49,c);
    digitalWrite(47,d);
  }else if(M==2){
    digitalWrite(52,a);
    digitalWrite(50,b);
    digitalWrite(48,c);
    digitalWrite(46,d);
  }
}
void onestep(int M){
writee(1,0,0,0,M);
delay(s);
writee(1,1,0,0,M);
delay(s);
writee(0,1,0,0,M);
delay(s);
writee(0,1,1,0,M);
delay(s);
writee(0,0,1,0,M);
delay(s);
writee(0,0,1,1,M);
delay(s);
writee(0,0,0,1,M);
delay(s);
writee(1,0,0,1,M);
delay(s);
writee(0,0,0,0,M);
}
void nonestep(int M){
writee(0,0,0,1,M);
delay(s);
writee(0,0,1,1,M);
delay(s);
writee(0,0,1,0,M);
delay(s);
writee(0,1,1,0,M);
delay(s);
writee(0,1,0,0,M);
delay(s);
writee(1,1,0,0,M);
delay(s);
writee(1,0,0,0,M);
delay(s);
writee(1,0,0,1,M);
delay(s);
writee(0,0,0,0,M);
}
