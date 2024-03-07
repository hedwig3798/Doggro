#pragma once
#include "pch.h"

class FbxAnimationData
{
public:
	std::vector<std::pair<float, DirectX::XMMATRIX>> animationData;

	int keyFrameCount;
	float framerate;
	float defaultFramerate;

	float nowTime;
	int prevIndex;

public:
	FbxAnimationData();
	~FbxAnimationData();

	DirectX::XMMATRIX GetAnimationMatirx(float _dt);
	void ResetAnimation();
};

