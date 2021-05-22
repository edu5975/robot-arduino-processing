import processing.video.*;
import hypermedia.net.*;
int medx=350,medy=350;
String msg;
UDP udp; 
Boolean con=false;
int life=0;
String temp="0",humedad="0",gas="0",laser="0",ultra="0",bateria="0";
PImage img,img2,img3,img4,vcam,fondo;
Capture video;
 int clk = 1;
String message;  // the message to send
String ip   	= "192.168.1.170";  // the remote IP address
int port    	= 4210;	// the destination port
void setup() {
  size(displayWidth, displayHeight);
  println(displayWidth);
  println(displayHeight);
  String[] cameras = Capture.list();
  video=new Capture(this,1280,720,cameras[0]);
  video.start();
  udp = new UDP( this, 4210 );
  udp.listen( true );
  	//message = "0";
	//udp.send( message, ip, port );
	img = loadImage("imagenes/termo.png");
	img2 = loadImage("imagenes/battery.png");
	img3 = loadImage("imagenes/rule.png");
	img4 = loadImage("imagenes/arrow.png");
    vcam=loadImage("imagenes/marco.png");
	fondo=loadImage("imagenes/fondo.jpg");
  }
void draw() {
  background(0, 0, 0);
  image(fondo,0,0);
   if (video.available() == true) {
	video.read();
  }
  if(!con){
	textSize(50);
	fill(255, 0, 0);
	text("No conectado", 500, 350);
   }else{
	int cx=displayWidth/2,cy=260;
	stroke(255);
	strokeWeight(5);
	imageMode(CENTER);
	image(video,cx, cy,896,504);
	image(vcam,cx,cy,1060,1010);
	imageMode(CORNER);
	textSize(15);
	fill(255,255,255);
	text("Temperatura: "+temp+"°",medx+50,medy+680);
	text("Humedad: "+humedad+"%",medx+300,medy+680);
 	text("Nivel CO: "+gas+"%", medx+550,medy+680);
	//text("Distancia Camara: "+laser+"cm",medx+50,medy+280);
    text("Dist front: "+ultra+"cm",medx+800,medy+680);
	text("Bateria: "+bateria+"%",medx+1050,medy+680);
	image(img, medx+50, medy+360, 100,300);
	fill(255,0,0);
	float yi=-2.2*(Integer.valueOf(temp));
	noStroke();
	rect(medx+89, medy+599, 19, yi);
	stroke(255);
	fill(25,0,0,0);
	arc(medx+355, medy+630, 200, 200, radians(-180), 0, PIE);
	fill(51, 204, 204);
	arc(medx+355, medy+630, 200, 200, radians(-180), radians(1.8*Integer.valueOf(humedad)-180), PIE);
	fill(25,0,0,0);
	arc(medx+355, medy+630, 150, 150, radians(-180), 0, PIE);
	fill(51,204,204);
	textSize(30);
    text(humedad+"%",medx+335,medy+620);
	fill(140,242,30);
	noStroke();
	yi=-1.4*(Integer.valueOf(bateria));
	rect(medx+1050,medy+ 599, 70, yi);
	image(img2, medx+985, medy+400, 200,250);
	//3er
	stroke(255);
	fill(25,0,0,0);
	arc(medx+600,medy+ 630, 200, 200, radians(-180), 0, PIE);
	fill(255, 153, 0);
	arc(medx+600, medy+630, 200, 200, radians(-180), radians(1.8*Integer.valueOf(gas)-180), PIE);
	fill(25,0,0,0);
	arc(medx+600, medy+630, 150, 150, radians(-180), 0, PIE);
	fill(255, 153, 0);
	textSize(30);
	text(gas+"%",medx+575,medy+620);
	//
	image(img3,medx+750,medy+350,200,300);
	yi=-3*(Integer.valueOf(ultra))+595;
	image(img4,medx+870,medy+yi,50,50); 
	fill(255);
	textSize(20);
	text("CONTROLES CAMARA",40,40);
  }
  if(life>=500){
	con=false;
  }else{
	life++;
  }
  //text(life,50,50);
  delay(1);
}
void exect(String inst) {
	String message  = inst;
	// formats the message for Pd
	// send the message
	udp.send( message, ip, port );
 
 
	
}
void receive( byte[] data){
  data = subset(data, 0, data.length-2);
  msg = new String( data );
  println(msg);
  String[] list = split(msg, '$');
  if(list[0].equals("SENS")){
  temp=list[1];
  humedad=list[2];
  gas=list[3];
 
  laser=list[4];
  ultra=list[5];
  bateria=list[6];
  }else if(list[0].equals("IP")){
	ip=list[1];
  }
   con=true;
  life=0;
}
void keyPressed() {
  if (key == CODED) {
 
	if (keyCode == UP) {
  	exect("VU");
	} else if (keyCode == DOWN) {
  	exect("VD");
	}
	else if (keyCode == LEFT) {
  	exect("HL");
	}
	else if (keyCode == RIGHT) {
  	exect("HR");
	}
  }
 
  else {	
  }
}
 
