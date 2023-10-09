#include "HX711.h"
#include <ESP8266WiFi.h>

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const char *ssid =  "";     
const char *pass =  "";

WiFiClient client;
HX711 scale;

int reading;
int lastReading;
//use calibiration code to replace factor
#define CALIBRATION_FACTOR 123.456

void setup() {
  pinMode(4,OUTPUT); //100 percent full
  pinMode(5,OUTPUT); //70 percent full
  pinMode(6,OUTPUT); //40 percent full
  pinMode(7,OUTPUT); //10 persccent full
  pinMode(8,OUTPUT); // less tahn 10 percent beeping alert
  Serial.begin(57200);

  WiFi.begin(ssid, pass); // CONNECTING TO WIFI
  Serial.println("WiFi connected")
  
  Serial.println("Initializing the scale");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(CALIBRATION_FACTOR);
  scale.tare();
}

void loop() {
  if (scale.wait_ready_timeout(200)) {
    reading = round(scale.get_units());
    Serial.print("Weight: ");
    Serial.println(reading);
    lastReading = reading;
    int weight = reading;
    if((weight/weight)*100 >=100)
      {
        digitalWrite(4,HIGH);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
      }
      else if((weight/weight)*100 >=70)
      {        
        digitalWrite(4,LOW);
        digitalWrite(5,HIGH);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
      }
      else if((weight/weight)*100 >=40)
      {        
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,HIGH);
        digitalWrite(7,HIGH);
        digitalWrite(8,LOW);
      }
      else if((weight/weight)*100 >=10)
      {        
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
          digitalWrite(7, HIGH);
          delay(1000);
          digitalWrite(7, LOW);
          delay(1000); 
        digitalWrite(8,LOW);
      }
      else if((weight/weight)*100 < 10)
      {        
        digitalWrite(4,LOW);
        digitalWrite(5,LOW);
        digitalWrite(6,LOW);
        digitalWrite(7,LOW);
          digitalWrite(8, HIGH);
          delay(1000);
          digitalWrite(8, LOW);
          delay(1000); 
      }
  }
  else {
    Serial.println("HX711 not found.");
  }

}
