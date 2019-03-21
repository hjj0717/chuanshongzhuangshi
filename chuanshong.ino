/*
  Name:    chuanshong.ino
  Created: 2018/10/29 9:42:13
  Author:  Giles.Huang
*/

#include <Servo.h>
#define ck_zuo 8    //����
#define ck_you 9    //����
#define xianwei_shang 10  //����
#define xianwei_xia 11   //����
#define mada_zhen 4
#define mada_fu 5
#define duoji 3  //300���� ����Ϊ0.5ms-1.5ms
//����ֿ�洢λ�ã��ֿ����������

int zuo_zongshu = 0;
int you_zongshu = 0;
Servo S360;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(ck_zuo, INPUT);
	pinMode(ck_you, INPUT);
	pinMode(xianwei_xia, INPUT);
	pinMode(xianwei_shang, INPUT);
	pinMode(mada_fu, OUTPUT);
	pinMode(mada_zhen, OUTPUT);
	pinMode(duoji, OUTPUT);
	Serial.begin(9600);
	Serial.println("system initialization...");
	S360.attach(duoji);
	S360.write(90);
	Serial.println("servo ready");
	delay(1000);
	qidong_sj();
	Serial.println("system ready");
}

// the loop function runs over and over again until power down or reset
void loop()
{
	cunchu();
	delay(500);
}


//���Դ�������
void cs()
{
}

//�洢����  ˳�������洢�����Ҹ����������
void cunchu()
{
	delay(100);
	if (digitalRead(ck_zuo) == false && digitalRead(xianwei_xia) == true)
	{
		int a;
		a++;
		zuo_zongshu++;
		if (zuo_zongshu == 4)
		{
			zuo_zongshu = 1;
		}
		Serial.print("zuo_zongshu  ");
		Serial.println(zuo_zongshu);
		delay(5000);
		switch (zuo_zongshu)
		{
		case 1:
			Serial.println("changku zuo 1");
			mada_zhenzhuan();
			delay(100);
			mada_tingzhi();
			delay(500);
			S360_YOU();
			delay(500);
			break;
		case 2:
			Serial.println("changku zuo 2");
			mada_zhenzhuan();
			delay(4300);
			mada_tingzhi();
			delay(500);
			S360_YOU();
			delay(500);
			break;
		case 3:
			Serial.println("changku zuo 3");
			mada_zhenzhuan();
			delay(8800);
			mada_tingzhi();
			delay(500);
			S360_YOU();
			delay(500);
			break;
		default: break;
		}
		delay(1000);
		qidong_sj();
	}
	else if (digitalRead(ck_you) == false && digitalRead(xianwei_xia) == true)
	{
		int b;
		b++;
		you_zongshu++;
		if (you_zongshu == 4)
		{
			you_zongshu = 1;
		}
		Serial.print("you_zongshu  ");
		Serial.println(you_zongshu);
		delay(5000);
		switch (you_zongshu)
		{
		case 1:
			Serial.println("changku you 1");
			mada_zhenzhuan();
			delay(100);
			mada_tingzhi();
			delay(500);
			S360_ZUO();
			delay(500);
			break;
		case 2:
			Serial.println("changku you 2");
			mada_zhenzhuan();
			delay(4300);
			mada_tingzhi();
			delay(500);
			S360_ZUO();
			delay(500);
			break;
		case 3:
			Serial.println("changku you 3");
			mada_zhenzhuan();
			delay(8800);
			mada_tingzhi();
			delay(500);
			S360_ZUO();
			delay(500);
			break;
		default: break;
		}
		delay(1000);
		qidong_sj();
	}
}

//���������ܶ�λ
void qidong_sj()
{
	mada_fanzhuan();
	while (digitalRead(xianwei_xia) == false);
	mada_tingzhi();
	delay(500);
}

//�����תΪ����
void mada_zhenzhuan()
{
	digitalWrite(mada_zhen, 160);
	digitalWrite(mada_fu, 0);
	Serial.println("motor up");
}

//��ﷴתΪ�½�
void mada_fanzhuan()
{
	digitalWrite(mada_zhen, 0);
	digitalWrite(mada_fu, 80);
	Serial.println("motor down");
}

//���ֹͣ
void mada_tingzhi()
{
	digitalWrite(mada_zhen, LOW);
	digitalWrite(mada_fu, LOW);
	Serial.println("moto stop");
}

//����ֶ������
void S360_ZUO()
{
	Serial.println("servo left");
	S360.write(180);
	delay(1000);
	S360.write(90);
}

//���Ҳֶ������
void S360_YOU()
{
	Serial.println("servo right");
	S360.write(0);
	delay(1000);
	S360.write(90);
}
