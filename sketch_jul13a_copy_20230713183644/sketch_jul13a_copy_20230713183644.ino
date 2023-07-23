#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
 
const char* ssid = "WIFI名称";     
const char* password = "WIFI密码"; 
 
WiFiServer server(80);  //http的服务端口
 
void setup() {
  pinMode(16, OUTPUT);  //用于连接Wi-Fi的LED指示灯
  digitalWrite(16, LOW);
  Serial.begin(115200);
  pwm.begin();
  pwm.setPWMFreq(60); //伺服电机以60hz刷新率工作
  delay(1000);
 
  //连接到无线网络
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  //启动服务器
  server.begin();
  Serial.println("Server started");
 
  //打印IP地址
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
  digitalWrite(16, HIGH);
}
 
void loop() {
  //检查客户端是否已连接
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  //等到客户端发送一些数据
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
 
  //阅读请求的第一行
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  //匹配请求
  if (request.indexOf("/S") != -1) {
    sleep();
  }
  if (request.indexOf("/W") != -1) {
    normal();
  }
  if (request.indexOf("/F") != -1) {
    normal();
    forward();
    forward();
    forward();
    forward();
  }
  if (request.indexOf("/B") != -1) {
    normal();
    backward();
    backward();
    backward();
    backward();
  }
  if (request.indexOf("/L") != -1) {
    normal();
    left();
    left();
  }
  if (request.indexOf("/R") != -1) {
    normal();
    right();
    right();
  }
  if (request.indexOf("/H") != -1) {
    normal();
    hello();
  }
 if (request.indexOf("/C") != -1) {
    normal();
    come();
  }
  //返回响应
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println(".button{");
/*----------网页设计----------*/
  client.println("background-color: #4CAF50; /* GREEN */");
  client.println("width: 48%;");
  client.println("border: none;");
  client.println("color: white;");
  client.println("padding: 50px 40px;");
  client.println("text-align: center;");
  client.println("text-decoration: none;");
  client.println("display: inline-block;");
  client.println("font-size: 50px;");
  client.println("margin: 4px 2px;");
  client.println("cursor: pointer;");
  client.println("border-radius: 12px;");
  client.println("}");
 
  client.println("</style>");
  client.println("</head>");
  client.println("<body bgcolor=black>");
 
  client.println("<button class=\"button\" onclick=\"window.location.href='/F';\">前进</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/B';\">后退</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/L';\">左转</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/R';\">右转</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/S';\">睡觉</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/W';\">正常</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/H';\">你好</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/C';\">来啊</button>");
  client.println("</body>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
 
/*----------动作函数----------*/
 
// |   7  |             |   6  |
//  ----- -----   ----- -----
//       |  3   | |  2   |
//        -----   -----
//       |   1  | |  0   |
//  ----- -----   ----- -----
// |  5   |             |  4   |
 
void sleep() 
{
  pwm.setPWM(4, 0, 280);
  delay(100);
  pwm.setPWM(5, 0, 280);
  delay(100);
  pwm.setPWM(6, 0, 280);
  delay(100);
  pwm.setPWM(7, 0, 280);
  delay(100);
  pwm.setPWM(0, 0, 510);
  delay(100);
  pwm.setPWM(1, 0, 100);
  delay(100);
  pwm.setPWM(2, 0, 100);
  delay(100);
  pwm.setPWM(3, 0, 510);
}
 
void normal() 
{
  pwm.setPWM(0, 0, 370);
  delay(100);
  pwm.setPWM(1, 0, 190);
  delay(100);
  pwm.setPWM(2, 0, 190);
  delay(100);
  pwm.setPWM(3, 0, 370);
  delay(100);
  pwm.setPWM(4, 0, 510);
  delay(100);
  pwm.setPWM(7, 0, 100);
  delay(100);
  pwm.setPWM(6, 0, 510);
  delay(100);
  pwm.setPWM(5, 0, 100);
}
 
void left()
{
  pwm.setPWM(4, 0, 370);
  delay(100);
  pwm.setPWM(0, 0, 510);
  delay(100);
  pwm.setPWM(4, 0, 510);
  delay(100);
  pwm.setPWM(6, 0, 370);
  delay(100);
  pwm.setPWM(2, 0, 280);
  delay(100);
  pwm.setPWM(6, 0, 510);
  delay(100);
  pwm.setPWM(7, 0, 190);
  delay(100);
  pwm.setPWM(3, 0, 510);
  delay(100);
  pwm.setPWM(7, 0, 100);
  delay(100);
  pwm.setPWM(5, 0, 190);
  delay(100);
  pwm.setPWM(1, 0, 280);
  delay(100);
  pwm.setPWM(5, 0, 100);
  delay(100);
  pwm.setPWM(0, 0, 370);
  pwm.setPWM(2, 0, 190);
  pwm.setPWM(3, 0, 370);
  pwm.setPWM(1, 0, 190);
}
 
void right()
{
  pwm.setPWM(5, 0, 190);
  delay(100);
  pwm.setPWM(1, 0, 100);
  delay(100);
  pwm.setPWM(5, 0, 100);
  delay(100);
  pwm.setPWM(7, 0, 190);
  delay(100);
  pwm.setPWM(3, 0, 280);
  delay(100);
  pwm.setPWM(7, 0, 100);
  delay(100);
  pwm.setPWM(6, 0, 370);
  delay(100);
  pwm.setPWM(2, 0, 100);
  delay(100);
  pwm.setPWM(6, 0, 510);
  delay(100);
  pwm.setPWM(4, 0, 370);
  delay(100);
  pwm.setPWM(0, 0, 190);
  delay(100);
  pwm.setPWM(4, 0, 510);
  delay(100);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(3, 0, 370);
  pwm.setPWM(2, 0, 190);
  pwm.setPWM(0, 0, 370);
}
 
void forward()
{ 
  pwm.setPWM(5, 0, 190);
  delay(50);
  pwm.setPWM(1, 0, 100);
  delay(50);
  pwm.setPWM(5, 0, 100);
  delay(50);
  pwm.setPWM(4, 0, 370);
  delay(50);
  pwm.setPWM(0, 0, 510);
  delay(50);
  pwm.setPWM(4, 0, 510);
  delay(50);
  pwm.setPWM(6, 0, 370);
  delay(50);
  pwm.setPWM(2, 0, 280);
  delay(50);
  pwm.setPWM(6, 0, 510);
  delay(50);
  pwm.setPWM(7, 0, 190);
  delay(50);
  pwm.setPWM(3, 0, 280);
  delay(50);
  pwm.setPWM(7, 0, 100);
  delay(50);
  pwm.setPWM(0, 0, 370);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(2, 0, 190);
  pwm.setPWM(3, 0, 370);
}
 
void backward()
{ 
  pwm.setPWM(7, 0, 190);
  delay(50);
  pwm.setPWM(3, 0, 510);
  delay(50);
  pwm.setPWM(7, 0, 100);
  delay(50);
  pwm.setPWM(6, 0, 370);
  delay(50);
  pwm.setPWM(2, 0, 100);
  delay(50);
  pwm.setPWM(6, 0, 510);
  delay(50);
  pwm.setPWM(5, 0, 190);
  delay(50);
  pwm.setPWM(1, 0, 280);
  delay(50);
  pwm.setPWM(5, 0, 100);
  delay(50);
  pwm.setPWM(4, 0, 370);
  delay(50);
  pwm.setPWM(0, 0, 280);
  delay(50);
  pwm.setPWM(4, 0, 510);
  delay(50);
  pwm.setPWM(3, 0, 370);
  pwm.setPWM(2, 0, 190);
  pwm.setPWM(1, 0, 190);
  pwm.setPWM(0, 0, 370);
}
 
void hello()
{
  pwm.setPWM(0, 0, 510);
  delay(100);
  pwm.setPWM(4, 0, 100);
  delay(500);
  pwm.setPWM(4, 0, 190);
  delay(500);
  pwm.setPWM(4, 0, 100);
  delay(500);
  pwm.setPWM(4, 0, 190);
  delay(500);
  pwm.setPWM(4, 0, 100);
  delay(500);
  pwm.setPWM(4, 0, 510);
}
 
void come()
{
  pwm.setPWM(0, 0, 280);
  delay(100);
  pwm.setPWM(4, 0, 100);
  delay(500);
  pwm.setPWM(4, 0, 190);
  delay(500);
  pwm.setPWM(4, 0, 100);
  delay(500);
  pwm.setPWM(4, 0, 190);
  delay(500);
  pwm.setPWM(4, 0, 100);
  delay(500);
  pwm.setPWM(4, 0, 510);
}