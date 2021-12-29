#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h> 
#include <ctime>
#include<iomanip>

#define EXT_KEY        0xffffffe0   //확장키 인식값 
#define KEY_LEFT      0x4b
#define KEY_RIGHT      0x4d
#define KEY_UP         0x48
#define KEY_DOWN      0x50
#define KEY_K		0x6b //keep 키 k
class StageData
{
private:
	int speed;   //숫자가 낮을수록 속도가 빠르다
	int stick_rate;      //막대가 나오는 확률 0~99 , 99면 막대기만 나옴
	int clear_line;      //레벨을 클리어하기 위해 없애야 하는 줄 수
public:
	void setspeed(int s);
	void setstickrate(int stickrate);
	void setclearline(int clearline);
	int getspeed();
	int getstickrate();
	int getclearline();
	StageData();
	StageData(const int& speed, const int& stick_rate, const int& clear_line);
	~StageData();

	
};

