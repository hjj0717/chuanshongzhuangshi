/*
 Name:    chache
 Created: 2018/10/17 14:47:53
 Author:  huang
*/

#include <Wire.h>
#include <PS2X_lib.h>       //PS2手柄
PS2X ps2x; 
	   //////////PS2引脚//////////////////一共4个信号引脚
#define PS2_DAT        10  // DI
#define PS2_CMD        11  //  DO
#define PS2_SEL        12   //CS
#define PS2_CLK        13  //CLK

#define fr_left_motorPositive 5
#define fr_left_motorCathode 4
#define fr_right_motorPositive 7
#define fr_right_motorCathode 6
#define Rise_up_motorPositive 2
#define Rise_down_motorPositive 3
#define electromagnet_motorPositive 9

int turn_speed = 255;  //必须大于180，否则马达带不动
unsigned char servo, PS2_LY, PS2_LX, PS2_RY, PS2_RX, PS2_KEY;  //定义相关的变量
void(*resetFunc) (void) = 0;// Reset func

void setup() {
	char error;
	Serial.begin(115200);        //开启串口    
	delay(500);
	error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);//PS2控制
	pinMode(fr_left_motorPositive, OUTPUT);
	pinMode(fr_left_motorCathode, OUTPUT);
	pinMode(fr_right_motorPositive, OUTPUT);
	pinMode(fr_right_motorCathode, OUTPUT);
	pinMode(Rise_up_motorPositive, OUTPUT);
	pinMode(Rise_up_motorPositive, OUTPUT);
	pinMode(electromagnet_motorPositive, OUTPUT);
}


void loop()
{
	ps2x.read_gamepad(true, 1); //读PS2按键 下面几行是读XY坐标
	PS2_LX = ps2x.Analog(PSS_LX);
	PS2_LY = ps2x.Analog(PSS_LY);
	PS2_RX = ps2x.Analog(PSS_RX);
	PS2_RY = ps2x.Analog(PSS_RY);
	ps2_read_motor();
	motor_speed();
	//car_run();
	electromagnet_run();
	PS2_button_car();
	delay(10);
}

//电磁铁
void electromagnet_run() {
	if (ps2x.Button(PSB_SQUARE))
	{
		analogWrite(electromagnet_motorPositive, 255);
		analogWrite(8, 0);
		Serial.println("electromagnet_run!");
	}
	else if (ps2x.Button(PSB_CIRCLE))
	{
		analogWrite(electromagnet_motorPositive, 0);
		analogWrite(8, 0);
		Serial.println("electromagnet_stop!");
	}
}

void PS2_button_car() {
	if (ps2x.Button(PSB_PAD_DOWN))
	{
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, turn_speed);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, turn_speed);
		Serial.println("car up!");
	}
	else if (ps2x.Button(PSB_PAD_UP))
	{
		analogWrite(fr_left_motorPositive, turn_speed);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, turn_speed);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car down!");
	}
	else if (ps2x.Button(PSB_PAD_LEFT))
	{
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, turn_speed);
		analogWrite(fr_right_motorPositive, turn_speed);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car rihgt!");
	}
	else if (ps2x.Button(PSB_PAD_RIGHT))
	{
		analogWrite(fr_left_motorPositive, turn_speed);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, turn_speed);
		Serial.println("car left!");

	}
	else
	{
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car rihgt!");
	}
}

void car_run() {
	if (PS2_LY < 125 && PS2_LX < 125) //左前行  OK
	{
		int trun1 = 2 * (128 - PS2_LX);
		analogWrite(fr_left_motorPositive, turn_speed);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, trun1);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car left!");
	}
	else if (PS2_LY < 125 && PS2_LX>131)//右前行   
	{
		int trun2 = 2 * (PS2_LX - 128);
		analogWrite(fr_left_motorPositive, trun2);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, turn_speed);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car rihgt!");
	}

	else if (PS2_LY > 131 && PS2_LX < 125)//左后行  OK
	{
		int trun3 = 2 * (128 - PS2_LX);
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, trun3);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, turn_speed);
		Serial.println("car back left!");

	}
	else if (PS2_LY > 131 && PS2_LX > 131)
	{
		int trun4 = 2 * (PS2_LY - 128);  //右后行   OK
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, turn_speed);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, trun4);
		Serial.println("car back right!");
	}
	else if (PS2_LY <= 125 && (PS2_LX >= 125 && PS2_LX <= 131))  //前直行OK
	{
		analogWrite(fr_left_motorPositive, turn_speed);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, turn_speed);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car up!");
	}
	else if (PS2_LY >= 131 && (PS2_LX >= 125 && PS2_LX <= 131))  //后直行 OK
	{
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, turn_speed);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, turn_speed);
		Serial.println("car down!");
	}
	else {
		analogWrite(fr_left_motorPositive, 0);
		analogWrite(fr_left_motorCathode, 0);
		analogWrite(fr_right_motorPositive, 0);
		analogWrite(fr_right_motorCathode, 0);
		Serial.println("car STOP!");
	}
}

//升降马达 
void ps2_read_motor() {
	if (ps2x.Button(PSB_TRIANGLE))
	{
		analogWrite(Rise_up_motorPositive, turn_speed);
		analogWrite(Rise_down_motorPositive, 0);
		Serial.println("Rise_up!");
	}
	else if (ps2x.Button(PSB_CROSS))
	{
		analogWrite(Rise_up_motorPositive, 0);
		analogWrite(Rise_down_motorPositive, turn_speed);
		Serial.println("Rise_down!");
	}
	else
	{
		analogWrite(Rise_up_motorPositive, 0);
		analogWrite(Rise_down_motorPositive, 0);
		Serial.println("Rise_stop!");
	}
}


// 调节所有马达的运行速度
void motor_speed() {
	if (ps2x.Button(PSB_L1))
	{
		turn_speed = turn_speed + 10;
		Serial.println("MOTOR TRUN SPEED:" + turn_speed);
	}
	else if (ps2x.Button(PSB_L2))
	{
		turn_speed = turn_speed - 10;
		Serial.println("MOTOR TRUN SPEED:" + turn_speed);
	}
	else
	{
		turn_speed = turn_speed;
		Serial.println("MOTOR TRUN SPEED:" + turn_speed);
	}
}