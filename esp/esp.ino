#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
const char* ssid = "INFINITUM799D_2.4";
const char* password = "CB530045BC";
String response="";
IPAddress local_IP(192, 168, 1, 103);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 254);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
String str;
void setup(){
pinMode(D1,OUTPUT);
Serial.begin(115200);
Serial1.begin(115200);
delay(2000);
// Configures static IP address
Serial.println("Test de salida");
 /*if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
	Serial.println("STA Failed to configure");
  }*/
 digitalWrite(D1,HIGH);
   delay(1000);
   digitalWrite(D1,LOW);
Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
	delay(500);
	Serial.print(".");
  }
  Serial.println(" connected");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
  response="IP&"+WiFi.localIP();
  int str_len = response.length() + 1;
	char char_array[str_len];
	response.toCharArray(char_array, str_len);
	Udp.beginPacket("192.168.1.99", 4210);
   Udp.write(char_array);
   Udp.endPacket();
   response="";
   digitalWrite(D1,HIGH);
   delay(1000);
   digitalWrite(D1,LOW);
 
 
}
void loop()
{
  boolean sended=LOW;
 
  while (Serial.available()) {
  sended=HIGH;
  char r=Serial.read();
  Serial.write(r);
  response.concat(r);
  delay(10);
  digitalWrite(D1,HIGH);
  }
  Serial.println(sended);
  if(sended){
	int str_len = response.length() + 1;
	char char_array[str_len];
	response.toCharArray(char_array, str_len);
	Udp.beginPacket("192.168.1.145", 4210);
   Udp.write(char_array);
   Udp.endPacket();
   response="";
   digitalWrite(D1,LOW);
  }
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
	int len = Udp.read(incomingPacket, 255);
	if (len > 0)
	{
  	incomingPacket[len] = 0;
	}
	Serial1.printf(incomingPacket);
  }
delay(1000);
}
