
/*
全部使用300度舵机
204.8为1MS脉冲宽度
*/

// the setup function runs once when you press reset or power the board
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver servo_pmw;
int j = 0;
String comdata = "";
int numdata[6] = { 0 }, SERVO_PIN[6] = { 0, 1, 2, 3, 4, 5 }, mark = 0;

void setup() {
	pinMode(13, OUTPUT);
	Serial.begin(9600);
	servo_pmw.begin();
	servo_pmw.setPWMFreq(50);
	servo_xiaozun();
	delay(1000);
	servo_dakai();
}

// the loop function runs over and over again until power down or reset
void loop() {
	zhuaqu();
}

//抓取动作
void zhuaqu()
{
	servo_pmw.setPWM(0, 0, 307);
	delay(1000);
	servo_pmw.setPWM(4, 0, 150);
	delay(1000);
	servo_pmw.setPWM(1, 0, 152);
	delay(1000);
	servo_pmw.setPWM(2, 0, 204);
	delay(1000);
	servo_pmw.setPWM(4, 0, 210);
	delay(1000);
	servo_pmw.setPWM(2, 0, 250);
	delay(1000);
	servo_pmw.setPWM(1, 0, 260);
	delay(1000);
	servo_pmw.setPWM(0, 0, 104);
	delay(1000);
	servo_pmw.setPWM(1, 0, 155);
	delay(1000);
	servo_pmw.setPWM(2, 0, 204);
	delay(1000);
	servo_pmw.setPWM(4, 0, 150);
	delay(1000);
	servo_pmw.setPWM(2, 0, 250);
	delay(1000);
	servo_pmw.setPWM(1, 0, 260);
	delay(10000);
}

//底座舵机最大旋转范围
void cs0()
{
	servo_pmw.setPWM(0, 0, 70);
	delay(5000);
	servo_pmw.setPWM(0, 0, 408);
	delay(5000);
}

//摇臂1最大可旋转范围
void cs1()
{
	servo_pmw.setPWM(1, 0, 307);
	delay(5000);
	servo_pmw.setPWM(1, 0, 204);
	delay(5000);
}
//摇臂2最大可旋转范围
void cs2()
{
	servo_pmw.setPWM(2, 0, 320);
	delay(5000);
	servo_pmw.setPWM(2, 0, 130);
	delay(5000);
}

//旋转臂最大可旋转范围
void cs3()
{
	servo_pmw.setPWM(3, 0, 120);
	delay(3000);
	servo_pmw.setPWM(3, 0, 370);
	delay(3000);
}
//夹持最大可张开范围
void cs4()
{
	servo_pmw.setPWM(4, 0, 210);  //关闭
	delay(3000);
	servo_pmw.setPWM(4, 0, 150);  //打开
	delay(3000);
}

//启动缩回机械臂
void servo_xiaozun()
{
	servo_pmw.setPWM(0, 0, 307);
	delay(500);
	servo_pmw.setPWM(1, 0, 307);
	delay(500);
	servo_pmw.setPWM(2, 0, 90);
	delay(500);
	servo_pmw.setPWM(3, 0, 120);
	delay(500);
	servo_pmw.setPWM(4, 0, 200);
	delay(500);
}

//启动伸展机械臂
void servo_dakai()
{
	servo_pmw.setPWM(0, 0, 204);
	delay(500);
	servo_pmw.setPWM(1, 0, 204);
	delay(500);
	servo_pmw.setPWM(2, 0, 330);
	delay(500);
	servo_pmw.setPWM(3, 0, 130);
	delay(500);
	servo_pmw.setPWM(4, 0, 150);
	delay(500);
}

//调试用
void servo_0()
{
	servo_pmw.setPWM(0, 0, 103);
	servo_pmw.setPWM(1, 0, 103);
	servo_pmw.setPWM(2, 0, 103);
	servo_pmw.setPWM(3, 0, 103);
	servo_pmw.setPWM(4, 0, 103);
}

//调试用
void servo_300()
{
	servo_pmw.setPWM(0, 0, 408);
	servo_pmw.setPWM(1, 0, 408);
	servo_pmw.setPWM(2, 0, 408);
	servo_pmw.setPWM(3, 0, 408);
	servo_pmw.setPWM(4, 0, 408);
}


//调试用
void serial_read()
{
	while (Serial.available() > 0)
	{
		comdata += char(Serial.read());
		delay(2);
		mark = 1;
	}

	if (mark == 1)
	{
		Serial.println(comdata);
		Serial.println(comdata.length());
		for (int i = 0; i < comdata.length(); i++)
		{
			if (comdata[i] == ',')
			{
				j++;
			}
			else
			{
				numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
			}
			comdata = String("");
			mark = 0;
		}
		for (int i = 0; i < 6; i++)
		{
			Serial.print(SERVO_PIN[i]);
			Serial.print("---");
			Serial.println(numdata[i]);
			servo_pmw.setPWM(SERVO_PIN[i], 0, numdata[i]);
			numdata[i] = 0;
		}
	}
}