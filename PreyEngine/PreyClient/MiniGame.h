#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class UObject;

class MiniGame : public Entity
{
public:
	MiniGame(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~MiniGame();

public:
	void SetCutScene(int _currentIndex);


private:
	ManagerSet* managerSet;

	UObject* nowCutScene;

	int cutSceneNumber;

	std::wstring upath[2]
	{
		L"../Shader/compiled/UIVertexShader.cso",
		L"../Shader/compiled/UIPixelShader.cso",
	};
};

