#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

const char* ssid = "binaryupdates.com";   // Your Network SSID
const char* password = "@visitus@";       // Your Network Password

int val;
int pin = A0;
int pinn =A1;
WiFiClient client;

unsigned long myChannelNumber = 1528049; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "NRTFY67A6USAY6JP"; //Your Write API Key

void setup()
{
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop()
{
  val = analogRead(pin)*0.322265;
  calc=analogRead(pinn)*.09775;
  // Read Analog values and Store in val variable
  Serial.print("Temperature: ");
  Serial.print(val);                 // Print on Serial Monitor
  Serial.println("*C");
  Serial.print("Humidity:");
  Serial.print(calc);
  Serial.println("%");
  
  delay(1000);
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak
  delay(100);
}
