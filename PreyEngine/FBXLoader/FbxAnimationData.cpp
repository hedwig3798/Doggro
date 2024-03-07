#include "FbxAnimationData.h"

FbxAnimationData::FbxAnimationData()
	: animationData{}
	, keyFrameCount(0)
	, framerate(0.0f)
	, defaultFramerate(0.0f)
	, nowTime(0.0f)
	, prevIndex(0)
{

}

FbxAnimationData::~FbxAnimationData()
{

}

DirectX::XMMATRIX FbxAnimationData::GetAnimationMatirx(float _dt)
{
	if (animationData.empty())
	{
		return DirectX::XMMatrixIdentity();
	}
	else if (animationData.size() == 1)
	{
		return animationData[0].second;
	}

	this->nowTime += _dt / framerate;
	if (animationData[prevIndex + 1].first <= nowTime)
	{
		prevIndex++;
		if (prevIndex == this->animationData.size() - 1)
		{
			prevIndex = 0;
			nowTime -= this->animationData.back().first;
		}
	}

	return DirectX::XMMatrixIdentity();
}

void FbxAnimationData::ResetAnimation()
{
	this->nowTime = 0.0f;
	this->prevIndex = 0;
}
