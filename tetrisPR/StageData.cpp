#include "StageData.h"

StageData::StageData()
	:speed(0), stick_rate(0), clear_line(0)
{
}

StageData::StageData(const int& speed, const int& stick_rate, const int& clear_line)
	: speed(speed), stick_rate(stick_rate), clear_line(clear_line)
{
}


void StageData::setspeed(int s)
{
	speed = s;
}

void StageData::setstickrate(int stickrate)
{
	stick_rate = stickrate;
}

void StageData::setclearline(int clearline)
{
	clear_line = clearline;
}

int StageData::getspeed()
{
	return speed;
}

int StageData::getstickrate()
{
	return stick_rate;
}

int  StageData::getclearline()
{
	return clear_line;
}

StageData::~StageData()
{
}
