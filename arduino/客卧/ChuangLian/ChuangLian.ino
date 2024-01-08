#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// 替换为你的 Wi-Fi 凭证
const char *ssid     = "oppo"; // 网络的SSID
const char *password = "cyt123123";      // WiFi密码

// 设置固定的IP地址、网关和子网掩码
IPAddress staticIP(192,168,50,41);     // 设置你想要的固定IP地址
IPAddress gateway(192,168,50,1);        // 设置网关的IP地址
IPAddress subnet(255, 255, 255, 0);       // 设置子网掩码

// 设置服务器端口
ESP8266WebServer server(80);
Servo myservo;
// 设置灯的引脚
 // 使用ESP8266上的GPIO 5 (D0)

myservo.attach(D0); 

void setup() {
  Serial.begin(115200); // 初始化串口通信
  Serial.println();

  pinMode(sgPin, OUTPUT);
  digitalWrite(sgPin, LOW); // 初始状态关闭

  // 连接到 Wi-Fi 网络
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // 设置固定IP地址、网关和子网掩码
  WiFi.config(staticIP, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting to WiFi...");
  }

  // 打印连接成功信息
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // 设置路由处理请求
  server.on("/SG90", HTTP_GET, handleRoot);
  server.on("/SG90on", HTTP_POST, handleOn); // 改为处理POST请求
  server.on("/SG90off", HTTP_POST, handleOff); // 改为处理POST请求

  // 启动服务器
  server.begin();
}

void loop() {
  server.handleClient();
}

// 处理根路径的请求
void handleRoot() {
  String message = "SG90: " + String(digitalRead(sgPin) == LOW ? "SGOFF" : "SGON");
  server.send(200, "text/plain", message);
  Serial.println("请求处理完毕");
}


// 处理打开灯的请求
void handleOn() {
    for (pos = 0; pos <= 180; pos += 1) { // 从0度到180度
    myservo.write(pos);              // 设置舵机位置
    delay(15);                       // 等待15毫秒，让舵机到达指定位置
  handleRoot(); // 更新状态后，返回根路径的状态信息
  Serial.println("打开灯");
}

// 处理关闭灯的请求
void handleOff() {
    for (pos = 180; pos >= 0; pos -= 1) { // 从0度到180度
    myservo.write(pos);              // 设置舵机位置
    delay(15);                       // 等待15毫秒，让舵机到达指定位置
  handleRoot(); // 更新状态后，返回根路径的状态信息
  Serial.println("关闭灯");
}}}