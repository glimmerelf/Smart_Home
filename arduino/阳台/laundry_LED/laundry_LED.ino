#include <CheapStepper.h>//阳台节点
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "2666";
const char* password = "12345678";
WiFiServer server(80);
const int sensorPin = D1;//定义人体传感器的引脚
const int ledPin = D2;  // 定义LED的引脚
bool moveClockwise = true;
unsigned long moveStartTime = 0;

CheapStepper stepper(D3,D7,D5,D6);//定义步进电机的引脚

//IPAddress staticIP(192, 168, 185,21);     // 设置你想要的固定IP地址
//IPAddress gateway(192, 168, 185, 211);        // 设置网关的IP地址
//IPAddress subnet(255, 255, 255, 0);       // 设置子网掩码

ESP8266WebServer httpServer(80);

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>Stepper Motor and LED Control</h1>";
  html += "<p>Click the buttons below to control the motor and LED:</p>";
  html += "<button onclick=\"rotateClockwise()\">Rotate Clockwise</button>";
  html += "<button onclick=\"rotateCounterclockwise()\">Rotate Counterclockwise</button>";
  html += "<button onclick=\"toggleLED()\">Toggle LED</button>";
  html += "<script>";
  html += "function rotateClockwise() {";
  html += "  sendCommand('0');";
  html += "}";
  html += "function rotateCounterclockwise() {";
  html += "  sendCommand('1');";
  html += "}";
  html += "function toggleLED() {";
  html += "  sendCommand('2');";
  html += "}";
  html += "function sendCommand(command) {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/control?cmd=' + command, true);";
  html += "  xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";

  httpServer.send(200, "text/html", html);
}

void handleControl() {
  if (httpServer.hasArg("cmd")) {
    char command = httpServer.arg("cmd")[0];
    if (command == '0' && stepper.getStepsLeft() == 0) {
      moveClockwise = true;
      stepper.newMoveDegrees(moveClockwise, 360); // Move 360 degrees in the clockwise direction
      moveStartTime = millis();
      httpServer.send(200, "text/plain", "Rotating clockwise.");
    } else if (command == '1' && stepper.getStepsLeft() == 0) {
      moveClockwise = false;
      stepper.newMoveDegrees(moveClockwise, 360); // Move 360 degrees in the counterclockwise direction
      moveStartTime = millis();
      httpServer.send(200, "text/plain", "Rotating counterclockwise.");
    } else if (command == '2') {
      // 切换LED状态
      digitalWrite(ledPin, !digitalRead(ledPin));
      httpServer.send(200, "text/plain", "Toggled LED.");
    } else if (command == '3') {
      // 停止电机
      stepper.setRpm(0); // 将电机速度设置为0，停止运动
      httpServer.send(200, "text/plain", "Motor stopped.");
    }
  } else {
    httpServer.send(400, "text/plain", "Bad Request");
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);  // 将LED引脚设置为输出
  digitalWrite(ledPin, LOW);  // 最初关闭LED

  stepper.setRpm(20);

  Serial.begin(9600);
  Serial.print("stepper RPM: ");
  Serial.print(stepper.getRpm());
  Serial.println();
  Serial.print("stepper delay (micros): ");
  Serial.print(stepper.getDelay());
  Serial.println();
   
  moveStartTime = millis();

  // 连接到WiFi网络
  WiFi.begin(ssid, password);
  //WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
   


  httpServer.on("/", handleRoot);
  httpServer.on("/control", handleControl);

  httpServer.begin();

  Serial.println("HTTP server started.");
}

void loop() {
  httpServer.handleClient();

  // 检测红外传感器
  int irSensorValue = digitalRead(sensorPin);
  
  if (irSensorValue == HIGH) {
    // 有人接近，执行相应操作
    //Serial.println("Motion detected!");

    // 启动电机
   /* if (stepper.getStepsLeft() == 0) {
      stepper.setRpm(20);
      moveClockwise = !moveClockwise;
      stepper.newMoveDegrees(moveClockwise, 360);
      moveStartTime = millis();
      Serial.println("Rotating.");
    }*/

    // 打开LED
    digitalWrite(ledPin, HIGH);

    // 延时5秒
    delay(5000);

    // 关闭LED
    digitalWrite(ledPin, LOW);
  }

  // 如果电机运动完成，停止电机
  if (stepper.getStepsLeft() == 0) {
    stepper.setRpm(0);
    //Serial.println("Motor stopped.");
  }

  stepper.run();
}

