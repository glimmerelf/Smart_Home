#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>

const char *ssid     = "OnePlus Ace Pro";
const char *password = "2020239193";

ESP8266WebServer server(80);

const int ledPin = D1;
int brightness = 0; // 初始亮度为0
const int step = 100; // 步长为20
const int minBrightness = 23; // 最低亮度为24

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(ledPin, OUTPUT);
  analogWrite(ledPin, brightness); // 初始状态关闭

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/LED", HTTP_GET, handleRoot);
  server.on("/LED/on", HTTP_POST, handleOn);
  server.on("/LED/off", HTTP_POST, handleOff);
  server.on("/LED/brighter", HTTP_POST, handleBrighter); // 处理增亮请求
  server.on("/LED/dimmer", HTTP_POST, handleDimmer); // 处理减暗请求

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String message = "LED: " + String(brightness == 0 ? "OFF" : "ON");
  String(brightness);
  server.send(200, "text/plain", message);
  Serial.println("请求处理完毕");
}

void handleOn() {
  brightness = 1023;
  analogWrite(ledPin, brightness);
  handleRoot();
  Serial.println("打开灯");
}

void handleOff() {
  brightness = 0;
  analogWrite(ledPin, 0);
  handleRoot();
  Serial.println("关闭灯");
}

// 处理增亮请求
void handleBrighter() {
  if (brightness > 0) { // 只有在灯亮的时候才能调整亮度
    
    brightness = min(1023, brightness + step);
    analogWrite(ledPin, brightness);
    handleRoot();
    Serial.println("增亮");
  } else {
    server.send(400, "text/plain", "灯未打开，无法调整亮度");
  }
}

// 处理减暗请求
void handleDimmer() {
  if (brightness > 0) { // 只有在灯亮的时候才能调整亮度
    brightness = max(minBrightness, brightness - step); // 最低亮度为24
    analogWrite(ledPin, brightness);
    handleRoot();
    Serial.println("减暗");
  } else {
    server.send(400, "text/plain", "灯未打开，无法调整亮度");
  }
}
