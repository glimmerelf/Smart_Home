#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

const char *ssid = "2666";
const char *password = "12345678";

// IPAddress staticIP(192, 168, 185, 22);
// IPAddress gateway(192, 168, 185, 211);
// IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

int gasSensorPin = A0;
int buzzerPin = D4;
int ledPin = D1;
int relayPin = D2;
int threshold = 400;

void setup() {
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 // WiFi.config(staticIP, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/LED/on", HTTP_POST, handleLedOn);
  server.on("/LED/off", HTTP_POST, handleLedOff);

  server.begin();
}

void loop() {
  server.handleClient();

  int gasValue = analogRead(gasSensorPin);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, LOW); // 继电器接通
  } else {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, HIGH); // 继电器断开
  }
if (gasValue > 400) {
    digitalWrite(buzzerPin, LOW); // 蜂鸣器响
  } else {
    digitalWrite(buzzerPin, HIGH); // 蜂鸣器不响
  }
  delay(1000);
}

void handleRoot() {
  String message = "LED: " + String(digitalRead(ledPin) == LOW ? "OFF" : "ON");
  server.send(200, "text/plain", message);
  Serial.println("Request handled");
}

void handleLedOn() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(relayPin, LOW); // 继电器接通
  handleRoot();
  Serial.println("LED turned ON");
}

void handleLedOff() {
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, HIGH); // 继电器断开
  handleRoot();
  Serial.println("LED turned OFF");
}

