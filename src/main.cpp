#include <Arduino.h>
#include "Suteppa.h"
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 11;
const int IN4 = 12;
const int MAX = 495;
int d_hs[8] = {
	B1000, 
	B1100,
	B0100,
	B0110,
	B0010,
	B0011,
	B0001,
	B1001
};
Suteppa s;

void step(int d);
int findBegin(int step);
void setup()
{
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(2, INPUT_PULLUP);
	//一回転のステップ数, 加減速に使うステップ数, 開始速度, 最大速度, ステップ用関数
	s.init(500, 50, 2000, 1000, step);
}
void loop()
{
	//----------------------------------------------//
	//キャリブレーション
	//----------------------------------------------//
	//スムーズオフ
	s.setSmooth(false);
	//速度を2000マイクロ秒に
	s.setMax(2000);
	//先頭まで戻る
	s.rotate(Suteppa::RELATIVE, -9999, findBegin);
	//先頭を見つけたら、もう一度繰り返す
	delay(100);
	s.rotate(Suteppa::RELATIVE, 20);
	delay(100);
	s.rotate(Suteppa::RELATIVE, -20, findBegin);
	delay(1000);

	//----------------------------------------------//
	//耐久テストセットアップ
	//----------------------------------------------//

	//スムーズ
	s.setSmooth(true);
	//初速度
	s.setBegin(2000);
	//最大速度
	s.setMax(950);
	//アクションごとの待ち時間
	int wait = 0;

	//----------------------------------------------//
	//耐久テスト開始
	//----------------------------------------------//
	while(true){
		s.rotate(Suteppa::ABSOLUTE, MAX/2 + 100);
		s.rotate(Suteppa::RELATIVE, -200);
		s.rotate(Suteppa::RELATIVE, 200);
		s.rotate(Suteppa::RELATIVE, -200);
		s.rotate(Suteppa::RELATIVE, 200);
		delay(1000);
		s.rotate(Suteppa::RELATIVE, -200);
		delay(1000);
		s.rotate(Suteppa::ABSOLUTE, MAX);
		s.rotate(Suteppa::RELATIVE, -MAX);
		s.rotate(Suteppa::ABSOLUTE, MAX);
		s.rotate(Suteppa::RELATIVE, -MAX);
	}
}
//先頭を見つける関数。
int findBegin(int step)
{
	if(digitalRead(2) == 0){
		s.setHome();
		return 1;
	}
	return 0;
}
//ステッピングモーターを回す関数
void step(int d)
{
	static int i;
	i += d;
	if(i > 7) i = 0;
	if(i < 0) i = 7;
	byte b = d_hs[i];
	digitalWrite(IN1, bitRead(b, 0));
	digitalWrite(IN2, bitRead(b, 1));
	digitalWrite(IN3, bitRead(b, 2));
	digitalWrite(IN4, bitRead(b, 3));
}