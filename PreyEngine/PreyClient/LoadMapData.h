#pragma once
#include <vector>
#include "Component.h"
#include "Define.h"

class IGraphicsEngine;
class AObject;

class LoadMapData
{
public:
	LoadMapData(IGraphicsEngine* _gp);
	~LoadMapData();
	
	//모든 방 오브젝트를 불러와 저장해둘 일을 하는 함수
	void LoadMapMesh(std::string _stageName);
	
public:
	IGraphicsEngine* gp;

	//Map 전체를 읽어올 경우, 한번에 벡터에 저장합니다.
	std::vector<AObject*> mapObjects;
};

