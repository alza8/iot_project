# include  < Arduino. h>
# include  < DHT11. h>
# include  < WiFi. h>
# include  < HTTPClient. h>

// Replace with your Wi-Fi credentials
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";

// Replace with your server URL and API endpoint
const char* serverUrl = "http://your-server-url.com";
const char* apiEndpoint = "/send";

DHT11 dht(D1);
WiFiClient wifiClient;
HTTPClient httpClient;

void setup() {
  pinMode(D7, INPUT);
  pinMode(D6, INPUT);
  pinMode(D2, OUTPUT);
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
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int light = digitalRead(D6);
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

  String url = serverUrl;
  url += apiEndpoint;
  url += "?temp=" + String(temperature, 1);
  url += "&humi=" + String(humidity, 1);
  url += "&khak=" + String(khak);
  url += "&gas=" + String(gas);
  url += "&light=" + String(light);

  httpClient.begin(wifiClient, url);
  int statusCode = httpClient.GET();
  httpClient.end();

  if (statusCode == 200) {
    Serial.println("Data transmission was successful.");
  } else {
    Serial.println("Data transmission failed.");
  }

  delay((1 * 1000)); // delay 5 minutes
}