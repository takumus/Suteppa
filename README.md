# Suteppa
ステッピングモーターをスムーズに起動、停止するライブラリです。  
正確に言うとパルス間隔をコントロールするライブラリなので、  
このライブラリ自体にモーターを回転させる機能はありません。
## メソッド
初期化(`一回転のステップ数`, `回転用関数`)  
初期化(`一回転のステップ数`, `回転用関数`, `角度変更用関数`)
```c
void init(unsigned long allStep, void (*stepper)(int));  
void init(unsigned long allStep, void (*stepper)(int), void (*turner)(int));
```
速度変更(`ステップ間隔マイクロ秒`)
```c
void setSpeed(unsigned long speed);
```
回転  
(`回転モード`, `ステップ数(正で正転、負で逆転)`)  
(`回転モード`, `ステップ数(正で正転、負で逆転)`, `自動tick`)  
```c
void rotate(int mode, long step);
void rotate(int mode, long step, bool sync);
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
## サンプル(md09b使用)
通常モードで1回転して、スムーズモードで逆に1回転するサンプル  
```c
#include "Suteppa.h" 

//md09bの端子へ
const int STEP = 11; 
const int ENA = 10; 
const int DIR = 9;

//1回転に要するステップ数(1-2相励磁) 
const int MAX = 800;

//Suteppa宣言
Suteppa suteppa;

void stepper(int d); 
void turner(int d);

void setup(){ 
    pinMode(STEP, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(DIR, OUTPUT);
    
    //md09bを起動
    digitalWrite(ENA, LOW);
    
    //一回転のステップ数, ステップ用関数 
    suteppa.init(MAX, stepper, turner); 
    
    //250マイクロ秒ごとにステップする 
    suteppa.setSpeed(250);
} 
void loop() 
{
    //スムーズモードで１回転
    suteppa.beginSmooth(200, 600);
    suteppa.rotate(Suteppa::RELATIVE, MAX);
    suteppa.endSmooth();

    //待つ
    delay(1000);

    //絶対位置0度へ戻る。((Suteppa::RELATIVE, -MAX)と同等)
    suteppa.rotate(Suteppa::ABSOLUTE, 0);

    //待つ
    delay(1000);
} 
//ステッピングモーターを回す関数(dは方向。-1か1) 
void stepper(int d)
{
    static boolean t = true;
    digitalWrite(STEP, t?HIGH:LOW);
    t = !t;
}
//ステッピングモーターの方向転換(dは方向。-1か1)
void turner(int d)
{
    digitalWrite(DIR, d>0?HIGH:LOW);
}
```
