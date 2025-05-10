#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "jumanji";
const char* password = "8949@pavan";
const char* mqtt_server = "10.0.0.64";

WiFiClient espClient;
PubSubClient client(espClient);

int ldrPin = 34; // Analog pin

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(">");
  }
  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT");
    } else {
      delay(5000);
      Serial.println("<");
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int lightVal = analogRead(ldrPin);


  char buffer[50];
  sprintf(buffer, "{\"light\": %d}", lightVal);
  client.publish("sensors/light", buffer);
Serial.print("send data via mqtt: ");
Serial.println(buffer);

  delay(2000); // publish every 15 seconds
}