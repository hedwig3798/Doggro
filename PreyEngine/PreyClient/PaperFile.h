#pragma once
#include <string>
#include "Entity.h"

class ManagerSet;
class LoadMapData;
class AObject;

class PaperFile :public Entity
{
public:
	PaperFile(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager);
	virtual ~PaperFile();

private:
	ManagerSet* managerSet;
	LoadMapData* objectManager;
	AObject* aObject;
};
