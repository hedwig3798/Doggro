#pragma once
#include "pch.h"

class FbxAnimationData;

class FbxBone
{
public:
	int parentIndex;
	int index;
	std::vector<int> childIndex;
	std::string name;

	DirectX::XMMATRIX localTM;
	DirectX::XMMATRIX globalTM;

	DirectX::XMMATRIX initailLocalTM;
	DirectX::XMMATRIX initailGlobalTM;

	std::map<std::string, FbxAnimationData*> frameList;

	FbxBone();
	~FbxBone();
};

