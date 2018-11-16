#include "SysNanoSecond.h"

CSysNanoSecond::CSysNanoSecond(void)
{
	
	QueryPerformanceFrequency(&frequency);
}

CSysNanoSecond::~CSysNanoSecond(void)
{
}

CSysNanoSecond * CSysNanoSecond::GetInstance(void)
{
	static CSysNanoSecond clInstance;

    return &clInstance;	
}

long long  CSysNanoSecond::GetSysNanoTime(void)
{
	LARGE_INTEGER timeStart;
	QueryPerformanceCounter(&timeStart);
	return timeStart.QuadPart;

}

double CSysNanoSecond::UseNanoTime(NNTIME endTime, NNTIME startTime)
{
	if(endTime < startTime)
	 return -0.99999;
	return ((endTime - startTime) / (double)frequency.QuadPart) * 1000;
}
