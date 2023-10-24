#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>

const char* ssid = "realme 9 5G";// enter wifi name(case sensitive)
const char* password = "12345678";//enter password

//Generate api key by sending text message "I allow callmebot to send me messages" to https://wa.me/+34644992698
String phoneNumber = "+916005659527";
String apiKey = "4688525";

//flexsensor and buzzer pins
const int flexPin = A0;
const int buzzpin = 2;

int initflex = analogRead(flexPin);
//Serial.println(initflex);


//fuction definition to send message to whatsapp
void sendMessage(String message){
  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void setup() {
  
  Serial.begin(115200);
  Serial.println(initflex);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  
  pinMode(buzzpin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int flexValue;
  flexValue = analogRead(flexPin);
//  Serial.print("sensor: ");
//  Serial.println(flexValue);

  Serial.print("sensor: ");
  Serial.println(initflex);
  if(flexValue<(initflex-50))
  {
     digitalWrite(buzzpin,HIGH);
     Serial.print("sensor: ");
     Serial.println(flexValue);
     sendMessage("your patient requires assistance");
     delay(300000);
  }
    if(flexValue>(initflex+50))
  {
     digitalWrite(buzzpin,HIGH);
     Serial.print("sensor: ");
     Serial.println(flexValue);
     sendMessage("your patient requires assistance");
     delay(300000);
  }
  else{
    digitalWrite(buzzpin,LOW);
  }
 
  delay(200);
}
