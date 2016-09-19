# Suteppa
ステッピングモーターをスムーズに起動、停止するライブラリです。  
正確に言うとパルス間隔をコントロールするライブラリなので、  
このライブラリ自体にモーターを回転させる機能はありません。
## メソッド
初期化(`一回転のステップ数`, `回転用関数`)
```c
void init(unsigned long allStep, void (*rotator)(int));
```
速度変更(`ステップ間隔マイクロ秒`)
```c
void setSpeed(unsigned long speed);
```
回転  
(`回転モード`, `ステップ数(正で正転、負で逆転)`)  
(`回転モード`, `ステップ数(正で正転、負で逆転)`, `ステップごとに呼ばれる関数`)  
```c
void rotate(int mode, long step);
void rotate(int mode, long step, int (*update)(int));
```
スムーズモードセット(`加速減速に使うステップ数`, `開始速度マイクロ秒`)
```c
void beginSmooth(unsigned long step, unsigned long initSpeed);
void beginSmooth();
```
デフォルトスムーズモードセット(`加速減速に使うステップ数`, `開始速度マイクロ秒`)
```c
void setDefaultSmooth(unsigned long step, unsigned long initSpeed);
```
ホームポジションセット(なし)
```c
void setHome();
```
## サンプル
通常モードで1回転して、スムーズモードで逆に1回転するサンプル  
```c
#include <Arduino.h>
#include "Suteppa.h"
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 11;
const int IN4 = 12;
//一回転
const int MAX = 1024;
//half step(1-2相励磁)
int hs[8] = {B1000,B1100,B0100,B0110,B0010,B0011,B0001,B1001};
Suteppa suteppa;
void step(int d);
void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  //一回転のステップ数, ステップ用関数
  suteppa.init(MAX, step);
  //500マイクロ秒ごとにステップする
  suteppa.setSpeed(500);
}
void loop()
{
  //MAXステップ回転する(相対角度で1回転)
  suteppa.rotate(Suteppa::RELATIVE, MAX);
  //1秒待つ
  delay(1000);
  //スムーズモードをセットする(加減速に100ステップ, 1000マイクロ秒から500まで加速)
  suteppa.beginSmooth(100, 1000);
  //逆回転する(絶対角度で0度に戻す)
  suteppa.rotate(Suteppa::ABSOLUTE, 0);
  //スムーズモード終了
  suyeppa.endSmooth();
  //1秒待つ
  delay(1000);
}
//ステッピングモーターを回す関数(dは方向。-1か1)
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
```
