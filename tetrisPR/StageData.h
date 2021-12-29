#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h> 
#include <ctime>
#include<iomanip>

#define EXT_KEY        0xffffffe0   //Ȯ��Ű �νİ� 
#define KEY_LEFT      0x4b
#define KEY_RIGHT      0x4d
#define KEY_UP         0x48
#define KEY_DOWN      0x50
#define KEY_K		0x6b //keep Ű k
class StageData
{
private:
	int speed;   //���ڰ� �������� �ӵ��� ������
	int stick_rate;      //���밡 ������ Ȯ�� 0~99 , 99�� ����⸸ ����
	int clear_line;      //������ Ŭ�����ϱ� ���� ���־� �ϴ� �� ��
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

