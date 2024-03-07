#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class UObject;

class Album : public Entity
{
public:
	Album(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~Album();

public:
	void SetCurrentAlbum(int _currentIndex);
	void SetCurrentStage(int _currentIndex);

public:
	ManagerSet* managerSet;
	UObject* nowAlbum;

	UObject* nowSelect;
	float selectX;
	float selectY;

	std::wstring upath[2]
	{
		L"../Shader/compiled/UIVertexShader.cso",
		L"../Shader/compiled/UIPixelShader.cso",
	};
};

