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
	
	//��� �� ������Ʈ�� �ҷ��� �����ص� ���� �ϴ� �Լ�
	void LoadMapMesh(std::string _stageName);
	
public:
	IGraphicsEngine* gp;

	//Map ��ü�� �о�� ���, �ѹ��� ���Ϳ� �����մϴ�.
	std::vector<AObject*> mapObjects;
};

