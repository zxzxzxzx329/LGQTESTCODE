#pragma once
#include <Windows.h>

typedef long long NNTIME;
class CSysNanoSecond
{
private:
	LARGE_INTEGER frequency;	//��ʱ��Ƶ��	
public:
	static CSysNanoSecond * GetInstance(void);
	NNTIME  GetSysNanoTime(void);
	double UseNanoTime(NNTIME endTime, NNTIME startTime);
public:
	CSysNanoSecond(void);
	~CSysNanoSecond(void);
};
