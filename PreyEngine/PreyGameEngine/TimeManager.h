#pragma once
#include <windows.h>

/// <summary>
/// 시간과 프레임 제어를 위한 매니저
/// 2024.01.09 chlaudrl
/// </summary>

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Initalize();
	double Update();
	void Finalize();
	
	float GetDeltaTime() const { return static_cast<float>(deltaTime); }

private:
	LARGE_INTEGER currentCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER frequency;

	double deltaTime;
	double elapsedTime;
	int updateCount;

};

