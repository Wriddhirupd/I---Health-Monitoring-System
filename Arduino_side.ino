#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>
 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
}
 
void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
 Serial.println("abcd");
  if (root == JsonObject::invalid())
  {
    Serial.println("adndmene");
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  int data1=root["temp"];
  Serial.println(data1);
  Serial.print("Humidity    ");
  int data2=root["hum"];
  Serial.println(data2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");
 delay(2000);
}