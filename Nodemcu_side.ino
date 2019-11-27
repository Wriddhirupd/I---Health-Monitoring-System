#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>

String apiKey = "xxxxxxxxxxxxxxxx";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "xxxx";     // replace with your mobile wifi ssid 
const char *pass =  "xxxxxxxx";  // replace with your mobile wifi password
const char* server = "api.thingspeak.com";
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
WiFiClient client;

void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);


  if (root == JsonObject::invalid())
  {
    Serial.println("ababab");
  }
  //int state=Serial.read();
  float h = root.get<float>("humidity"); // template version of get()
  float t = root.get<float>("temperature"); // template version of get()
  
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  int data1=root["temp"]; data1 = data1 + 28;
  Serial.println(data1);
  Serial.print("Humidity    ");
  int data2=root["hum"]; data2=data2+27;
  Serial.println(data2);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");
 delay(2000);

               if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(17000);
}