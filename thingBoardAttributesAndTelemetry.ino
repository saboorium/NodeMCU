#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "DHT.h"
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>

#define WIFI_AP "realme GT NEO 3"
#define WIFI_PASSWORD "v379i2rn"

#define TOKEN "jyde1i70xm9h8h3qok3e"

#define GPIO0 D0
#define GPIO2 D2

#define GPIO0_PIN 3
#define GPIO2_PIN 5

const int trigPin = D5;
const int echoPin = D6;

char thingsboardServer[] = "demo.thingsboard.io";

WiFiClient wifiClient;
SoftwareSerial mySerial(D6,D5); // RX, TX 
// connect yellow wire to D5 and White wire to D6
PubSubClient client(wifiClient);
DHT dht;

unsigned char data[4]={};
float distance;
int status = WL_IDLE_STATUS;
unsigned long lastSend;

// We assume that all GPIOs are LOW
boolean gpioState[] = {false, false};

void setup() {
  Serial.begin(115200);
  // Set output mode for all GPIO pins
  pinMode(GPIO0, OUTPUT);
  pinMode(GPIO2, OUTPUT);
    pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.setup(D1);
  mySerial.begin(9600); 
  delay(10);
  InitWiFi();
  client.setServer( thingsboardServer, 1883 );
  client.setCallback(on_message);
}

void loop() {
  if ( !client.connected() ) {
    reconnect();
  }
  // if ( millis() - lastSend > 1000 ) { // Update and send only after 1 seconds
  //   getAndSendTemperatureAndHumidityData();
  //   lastSend = millis();
  // }
  // getDistanceData();
  // sendDistanceData();
  getAndSendDistanceData();
  client.loop();
  
}
void getAndSendDistanceData()
{
  const int trigPin = D5;
const int echoPin = D6;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  Serial.print("Distance:");
  Serial.println(distance);
  delay(400);
  String payload="{";
  payload+="\"Distance\":"; payload+=distance; payload+="}";
  char data[500];
  payload.toCharArray(data, 500);
  Serial.println("Sending Data To ThingsBoard:");
  Serial.println(distance);
  client.publish("v1/devices/me/telemetry",data);
}

void getDistanceData()
{
  Serial.println("Collecting Distance Data:");
  do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
         distance=distance / 10;
         Serial.print(distance);
      }
     }
     delay(100);
}
void sendDistanceData()
{
  String payload="{";
  payload+="\"Distance\":"; payload+=distance; payload+="}";
  char data[500];
  payload.toCharArray(data, 500);
  Serial.println("Sending Data To ThingsBoard:");
  Serial.println(distance);
  client.publish("v1/devices/me/telemetry",data);
}
void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data.");

  // Reading temperature or humidity takes about 250 milliseconds!
  float humidity = dht.getHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.getTemperature();
  float tempf=dht.toFahrenheit(temperature);
  Serial.println("STATUS OF DHT11");
  Serial.print(dht.getStatusString());
  char data[500];
  String payload1 = "{";
  payload1 += "\"Humidity\":";   payload1 += humidity;    payload1 += ",";
  payload1 += "\"Temperature*C\":";         payload1 +=temperature;          payload1 += ",";
  payload1 += "\"Temperature*F\":";         payload1 += tempf;
  payload1 += "}";
  payload1.toCharArray(data, 500);

  Serial.println("Sending data to ThingsBoard:");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print(tempf);
  Serial.println("*F");

  client.publish("v1/devices/me/telemetry",data);
}

// The callback for when a PUBLISH message is received from the server.
void on_message(const char* topic, byte* payload, unsigned int length) {

  Serial.println("On message");

  char json[length + 1];
  strncpy (json, (char*)payload, length);
  json[length] = '\0';

  Serial.print("Topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(json);

  // Decode JSON request
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject((char*)json);

  if (!data.success())
  {
    Serial.println("parseObject() failed");
    return;
  }

  // Check request method
  String methodName = String((const char*)data["method"]);
  Serial.println(methodName);
  Serial.println(String((const char*)data["params"]["pin"]));
  Serial.println(String((const char*)data["params"]["enabled"]));
  if (methodName.equals("getGpioStatus")) {
    // Reply with GPIO status
    Serial.println("i am getting status");
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    client.publish(responseTopic.c_str(), get_gpio_status().c_str());
  } else if (methodName.equals("setGpioStatus")) {
    // Update GPIO status and reply
    Serial.println("i am here now, lets set new ststus");
    set_gpio_status(data["params"]["pin"], data["params"]["enabled"]);
    String responseTopic = String(topic);
    responseTopic.replace("request", "response");
    client.publish(responseTopic.c_str(), get_gpio_status().c_str());
    client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
  }
}

String get_gpio_status() {
  // Prepare gpios JSON payload string
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  data[String(GPIO0_PIN)] = gpioState[0] ? true : false;
  data[String(GPIO2_PIN)] = gpioState[1] ? true : false;
  char payload[256];
  data.printTo(payload, sizeof(payload));
  String strPayload = String(payload);
  Serial.print("Get gpio status: ");
  Serial.println(strPayload);
  return strPayload;
}

void set_gpio_status(int pin, boolean enabled) {
  Serial.println("now setting the pin status");
  if (pin == GPIO0_PIN) {
    // Output GPIOs state
    digitalWrite(GPIO0, enabled ? LOW : HIGH);
    // Update GPIOs state
    gpioState[0] = enabled;
  } else if (pin == GPIO2_PIN) {
    // Output GPIOs state
    digitalWrite(GPIO2, enabled ? HIGH : LOW);
    // Update GPIOs state
    gpioState[1] = enabled;
  }
}

void InitWiFi() {
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( client.connect("node mcu", TOKEN, NULL) ) {
      Serial.println( "[DONE]" );
      // Subscribing to receive RPC requests
      client.subscribe("v1/devices/me/rpc/request/+");
      // Sending current GPIO status
      Serial.println("Sending current GPIO status ...");
      client.publish("v1/devices/me/attributes", get_gpio_status().c_str());
    } else {
      Serial.print( "[FAILED] [ rc = " );
      Serial.print( client.state() );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
