#pragma once
#include "Entity.h"

enum class DogType
{
	Stage1,
	Stage2,
	Stage3,
	Stage4,
	// 어린 강아지 투명 강아지 성인 강아지
};

class ManagerSet;
class QuestManager;
class LoadMapData;
class AObject;
class DogSight;
class ImagineCutScene;
class Human;

class Dog : public Entity
{
public:
	Dog(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, DogType _dogType, LoadMapData* _loadMapData, QuestManager* _questManager, Entity* _dogSight, Entity* _dogImagine);
	virtual ~Dog();

private:
	ManagerSet* managerSet;
	QuestManager* questManager;
	LoadMapData* loadMapData;

	AObject* myMesh;
	Entity* dogSight;
	Entity* imagineCutScene;
	Entity* human;

public:
	void GetHuman(Entity* _human);
};

