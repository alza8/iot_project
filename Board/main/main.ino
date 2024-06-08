#include <Arduino.h>
#include <DHT11.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

// Enter your Wi-Fi credentials
const char* ssid = "Lowk3yC00L";
const char* password = "@wefull_ArVsH+0nF1R3";

// Enter your server URL and API endpoint
const char* serverUrl = "https://iot.goraznet.store";
const char* apiEndpoint = "/send.php";

DHT11 dht(D1);
WiFiClient wifiClient;
HTTPClient httpClient;
int timer = 10000;


void setup() {
  pinMode(D7, INPUT); //Gas (MQ9)
  pinMode(D6, INPUT); //Light (LDR)
  pinMode(D2, OUTPUT); //LED ON/OFF
  Serial.begin(115200);

  // Clear Serial monitor output
  for (int i = 0; i < 20; i++) {
    Serial.println();
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Connected to Wi-Fi");
}

void loop() {

  int light = digitalRead(D6);
  if(timer >= 0){
     digitalWrite(D2,light);
     timer -= 50;
     delay(50);
     return;
  }
  
  timer= 10000;

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int khak = analogRead(A0);
  int gas = digitalRead(D7);


  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  Serial.print("Light: ");
  Serial.println(light ? "HIGH" : "LOW");

  Serial.print("Khak: ");
  Serial.println(khak);

  Serial.print("Gas: ");
  Serial.println(gas ? "HIGH" : "LOW");

char url[256]; // assuming max URL length is 256 characters
sprintf(url, "%s%s?dht11_temp=%.1f&dht11_humidity=%.1f&yl_69=%d&mq9=%d&ldr=%d",
        serverUrl, apiEndpoint, temperature, humidity, khak, gas, light); // For Formatting the String

//%s is used for char* (strings) and %d is used for int (integers)

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();


    if (httpClient.begin(*client, url)) {  // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = httpClient.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = httpClient.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", httpClient.errorToString(httpCode).c_str());
      }

      httpClient.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
}