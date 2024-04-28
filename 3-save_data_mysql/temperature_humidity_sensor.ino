#include <ESP8266WiFi.h>
#include <DHT.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";
const char* server = "SERVER_IP_ADDRESS";
const int httpPort = 8080
const int sensorPin = D2;
const int DHTTYPE = DHT11;

DHT dht(sensorPin, DHTTYPE);

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String data = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";

  WiFiClient client;
  if (client.connect(server, httpPort)) {
    client.print("POST /data HTTP/1.1\r\n");
    client.print("Host: " + server + "\r\n");
    client.print("Content-Type: application/json\r\n");
    client.print("Content-Length: " + data.length() + "\r\n");
    client.print("\r\n");
    client.print(data);
    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }

  delay(1000);
}
