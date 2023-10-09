#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

HX711 scale;
int reading;
int lastReading;
//use calibiration code to replace factor
#define CALIBRATION_FACTOR 123.456

void setup() {
  Serial.begin(57200);
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
  }
  else {
    Serial.println("HX711 not found.");
  }

}
