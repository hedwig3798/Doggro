#include "TimeManager.h"

TimeManager::TimeManager()
	:currentCount{}
	,frequency{}
	,prevCount{}
	,deltaTime(0.0)
	,elapsedTime(0.0)
	,updateCount(0)
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Initalize()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&prevCount);
	QueryPerformanceCounter(&currentCount);
}

double TimeManager::Update()
{
	QueryPerformanceCounter(&currentCount);

	deltaTime = (currentCount.QuadPart - prevCount.QuadPart) / (double)frequency.QuadPart;

	prevCount = currentCount;

	++updateCount;
	elapsedTime += deltaTime;
	if (elapsedTime >= 1.)
	{
		elapsedTime -= 1.;
		updateCount = 0;
	}
	return deltaTime;
}

void TimeManager::Finalize()
{

}
