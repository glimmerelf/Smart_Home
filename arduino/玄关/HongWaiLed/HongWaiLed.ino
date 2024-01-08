const int sensorPin = D1; //定义SR501人体红外的引脚
const int ledPin = D2;    //定义LED灯的引脚
int sensorValue = 0;      //声明传感器数据变量

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin,LOW);  
  pinMode(sensorPin, INPUT);  
}

void loop()
{
  sensorValue = digitalRead(sensorPin);   //读取传感器数据
  Serial.println(sensorValue);
  if(sensorValue == 1){                 //判断是否有人接近
      digitalWrite(ledPin,HIGH);         //点亮LED灯
      delay(60000);                      //延时60秒
      digitalWrite(ledPin,LOW);          //关闭LED灯
  }
}