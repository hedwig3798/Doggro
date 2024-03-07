#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;

//�÷��� ȭ�鿡 �׷����� �� �⺻���� Background�� Ÿ���� ���صд�.
enum class BACKGROUNDTYPE
{
	FLOOR1,
	WALL1,

};

class BackGround :public Entity
{
public:
	BackGround(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, BACKGROUNDTYPE _backType);
	virtual ~BackGround();
	
public:
	void DrawBackgroundType(BACKGROUNDTYPE _uiType);
private:
	ManagerSet* managerSet;

};

