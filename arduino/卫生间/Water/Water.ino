#include <Arduino.h>
//简谱频率，可用蜂鸣器实现音乐播放，此处简化只用于发出警报声
#define DH1 523
//列出全部D调的频率
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
//根据简谱列出各频率
int temp; //水位传感器的输出值
int buzzer = D0;      //蜂鸣器引脚D0
int water = D1; //定义水位传感器接口为D1接口
int tune[] = {DH1,DH1,DH1,DH1};
//根据简谱列出各节拍
float duration[]={1,0.5,0.5,1,};
int length; //用于表示tune长度，即音符个数
void setup()
{
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT); //定义蜂鸣器的输出beep为输出接口
    pinMode(water, INPUT); //定义水位传感器的输出water为输入接口
    length=sizeof(tune)/sizeof(tune[0]);   //计算tune长度，即音符个数，用于播放乐谱
}

void loop()
{
    temp = digitalRead(water); //获取水位传感器输出状态
    Serial.print(temp); //用于串口监视器看到temp数值变化
    if(temp == 1){
        //digitalWrite(buzzer, LOW); // 触发蜂鸣器发出警报声
        for(int x=0;x<length;x++)
        {
          tone(buzzer,tune[x]); //此函数依次播放tune序列里的数组，即每个音符
          delay(500*duration[x]); //每个音符持续的时间，即节拍duration，500是调整时间的越大，曲子速度越慢，越小曲子速度越快
          noTone(buzzer); //停止当前音符，进入下一音符
        }
        delay(100); //等待100ms后，循环重新开始
    }
    else{
        digitalWrite(buzzer, HIGH); // 停止蜂鸣器发出声音
    }

    delay(500);
}

