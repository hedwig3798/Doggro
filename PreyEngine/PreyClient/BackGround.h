#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;

//플레이 화면에 그려지게 될 기본적인 Background의 타입을 정해둔다.
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

