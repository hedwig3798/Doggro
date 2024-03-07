#pragma once
#include "Entity.h"

class ManagerSet;

enum class CUTSCENETYPE
{
	STAGE1,
	STAGE2,
	STAGE3
};


class ImagineCutScene : public Entity
{
public:
	ImagineCutScene(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, CUTSCENETYPE _uiType);
	virtual ~ImagineCutScene();

public:
	void DrawUIType(CUTSCENETYPE _uiType);


private:
	ManagerSet* managerSet;

};

