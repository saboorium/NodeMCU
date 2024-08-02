#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Replace with your network credentials
#define WIFI_SSID "your-SSID"
#define WIFI_PASSWORD "your-PASSWORD"

// Firebase Realtime Database URL and secret key
#define FIREBASE_HOST "your-database-url.firebaseio.com"
#define FIREBASE_AUTH "your-database-secret"

// Firebase Data object
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  // Generate random data
  int randomNumber = random(0, 100);

  // Send data to Firebase
  if (Firebase.pushInt(firebaseData, "/randomNumber", randomNumber)) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Failed to send data");
    Serial.println(firebaseData.errorReason());
  }

  // Wait for a few seconds before sending the next data
  delay(5000);
}
