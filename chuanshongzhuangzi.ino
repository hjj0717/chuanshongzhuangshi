/*
 Name:		changku.ino
 Created:	2018/10/20 14:04:30
 Author:	Giles.Huang
*/

//A4,A5两脚硬件I2C通讯  A4,SCL    A5,SCK

#include <TimerOne.h>   //定时器1  
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>	

#define jiejing_chukou_qian   2    
#define jiejing_panduan_qian    A0
#define jiejing_panduan_hou 3
#define jiejing_chukou_hou 8
#define jiejing_chukou_wei  9
#define stepper_pul_zhen 10
#define stepper_dir_zhen  11
#define stepper_en_zhen 12
int da, xiao = 0;

#define prescale0Pin  4
#define prescale1Pin  5
#define colorSelect0pin  6
#define colorSelect1pin  7
#define pulsePin  13

Adafruit_PWMServoDriver SERVO_I2C=Adafruit_PWMServoDriver(0x40);  //setPMW 50HZ,差分1ms为204.8

void setup()
{
	pinMode(stepper_pul_zhen, OUTPUT);
	pinMode(stepper_dir_zhen, OUTPUT);
	pinMode(stepper_en_zhen, OUTPUT);
	pinMode(jiejing_chukou_qian, INPUT);
	pinMode(jiejing_panduan_qian, INPUT);
	pinMode(jiejing_panduan_hou, INPUT);
	pinMode(jiejing_chukou_hou, INPUT);
	pinMode(jiejing_chukou_wei, INPUT);

	pinMode(prescale0Pin, OUTPUT);
	pinMode(prescale1Pin, OUTPUT);
	digitalWrite(prescale0Pin, HIGH);
	digitalWrite(prescale1Pin, HIGH);
	pinMode(colorSelect0pin, OUTPUT);
	pinMode(colorSelect1pin, OUTPUT);
	pinMode(pulsePin, INPUT);

	Serial.begin(9600);
	SERVO_I2C.begin();
	SERVO_I2C.setPWMFreq(50);  //设置舵机驱动板的工作频率
	servo_csh();
	Serial.println("I2C reday");
	delay(200);
	digitalWrite(11, HIGH);
	Timer1.initialize(1000);        //调频 1ms的频率
	Timer1.pwm(10, 5);               //占空比5
	Timer1.attachInterrupt(callback);   
	Serial.println("stepper reday");
	zhuanghuo();
}

void loop()
{
	panduan();
	if (digitalRead(jiejing_chukou_wei) == LOW)
	{
		da_chukou();
		zhuanghuo();
	}
	if (digitalRead(jiejing_chukou_qian) == LOW)
	{
		yanshe_chukou();
		zhuanghuo();
	}
	if (digitalRead(jiejing_chukou_hou) == LOW)
	{
		xiao_chukou();
		zhuanghuo();
	}
	delay(200);
	yanshe_shibie();
	yanshe_tichu();
}

void callback()
{
	digitalWrite(10, digitalRead(10) ^ 1);    //反转
}

//装在货物
void zhuanghuo()
{
	Serial.println("zhuanhuo");
	SERVO_I2C.setPWM(0, 0, 204);
	delay(1000);
	SERVO_I2C.setPWM(0, 0, 307);
}
//其他颜色出口
void yanshe_chukou()
{
	Serial.println("qita yanse");
	SERVO_I2C.setPWM(2, 0, 204);
	delay(2000);
	SERVO_I2C.setPWM(2, 0, 307);	
}

//大货物出口  第二个侧出口
void xiao_chukou()
{
	Serial.println("da chukou");
	SERVO_I2C.setPWM(4, 0, 204);
	delay(2000);
	SERVO_I2C.setPWM(4, 0, 307);
}

//小货物出口  尾端
void da_chukou()
{
	Serial.println("xiao chukou");
	SERVO_I2C.setPWM(5, 0, 204);
	delay(2000);
	SERVO_I2C.setPWM(5, 0,307);
}
//踢出大货物
void  tichu()
{
	SERVO_I2C.setPWM(3, 0, 400);
	delay(1000);
	SERVO_I2C.setPWM(3, 0, 204);
}

//舵机初始化位置
void servo_csh()
{
	SERVO_I2C.setPWM(0, 0, 307);
	Serial.println("servo 0 begin");
	delay(200);
	SERVO_I2C.setPWM(1, 0, 204);
	Serial.println("servo 1 begin");
	delay(200);
	SERVO_I2C.setPWM(2, 0, 307);
	Serial.println("servo 2 begin");
	delay(200);
	SERVO_I2C.setPWM(3, 0, 204);
	Serial.println("servo 3 begin");
	delay(200);
	SERVO_I2C.setPWM(4, 0, 307);
	Serial.println("servo 4 begin");
	delay(200);
	SERVO_I2C.setPWM(5, 0, 307);
	Serial.println("servo 5 begin");
	delay(200);
}

//舵机矫正
void cs()
{
	SERVO_I2C.setPWM(0, 0, 307);
	Serial.println("servo 0 begin");
	delay(500);
	SERVO_I2C.setPWM(1, 1, 307);
	Serial.println("servo 1 begin");
	delay(500);
	SERVO_I2C.setPWM(2, 0, 307);
	Serial.println("servo 2 begin");
	delay(500);
	SERVO_I2C.setPWM(3, 0, 307);
	Serial.println("servo 3 begin");
	delay(500);
	SERVO_I2C.setPWM(4, 0, 307);
	Serial.println("servo 4 begin");
	delay(500);
	SERVO_I2C.setPWM(6, 0, 307);
	Serial.println("servo 4 begin");
	delay(500);
	Serial.println("all servo reday");
}


//判断货物大小
void panduan()
{
	if (digitalRead(jiejing_panduan_qian)==LOW && digitalRead(jiejing_panduan_hou)== LOW)
	{
		delay(3000);
		da++;
		Serial.print("da");
		Serial.println(da);
		tichu();
	}
	else
	{
		xiao++;
		Serial.print("xiao");
		Serial.println(xiao);
	}
}

//颜色识别
int yanshe_shibie()
{
	int a;
	long red = readRed();
	long green = readGreen();
	long blue = readBlue();
	if (red < green && red < blue)
	{
		Serial.println("RED");
		a = 1;
	}
	if (green < red && green < blue)
	{
		Serial.println("GREEN");
		a = 1;
	}
	if (blue < green && blue < red)
	{
		Serial.println("BLUE");
		a = 1;
	}
	return a;
}

//踢出颜色
void yanshe_tichu()
{
	Serial.println("tichu yanse");
	SERVO_I2C.setPWM(1, 0, 204);
	delay(1000);
	SERVO_I2C.setPWM(1, 0, 307);
}
     
//读取四种颜色
long readRed()
{
	return (readColor(LOW, LOW));
}

long readGreen()
{
	return (readColor(HIGH, HIGH));
}

long readBlue()
{
	return (readColor(LOW, HIGH));
}

long readWhite()
{
	return (readColor(HIGH, LOW));
}

long readColor(int bit0, int bit1)
{
	digitalWrite(colorSelect0pin, bit0);
	digitalWrite(colorSelect1pin, bit1);
	long start = millis();
	for (int i = 0; i < 1000; i++)
	{
		pulseIn(pulsePin, HIGH);
	}
	return (millis() - start);
}

void printRGB()
{
	Serial.print(readRed()); Serial.print("\t");
	Serial.print(readGreen()); Serial.print("\t");
	Serial.print(readBlue()); Serial.print("\t");
	Serial.println(readWhite());
}
