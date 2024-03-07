#pragma once
#include <string>
#include <vector>

#include "Entity.h"

class ManagerSet;
class UObject;

class GetSoul : public Entity
{
public:
	GetSoul(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~GetSoul();

public:
	void QuestClear(float _heightTop);

public:
	ManagerSet* managerSet;
	UObject* topInventory;
	
	std::vector<UObject*> souls;

	UObject* souls1;
	UObject* souls2;
	UObject* souls3;
	UObject* souls4;
	UObject* souls5;
	UObject* souls6;
	UObject* souls7;
	UObject* souls8;
	UObject* souls9;
	UObject* souls10;
	UObject* souls11;
	UObject* souls12;
	UObject* souls13;
	UObject* souls14;
	UObject* souls15;

	float heightTop;
	std::wstring upath[2]
	{
		L"../Shader/compiled/UIVertexShader.cso",
		L"../Shader/compiled/UIPixelShader.cso",
	};
};

