#pragma once
#include "Entity.h"
class UIButton : public Entity
{
public:
	UIButton(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~UIButton();


};

