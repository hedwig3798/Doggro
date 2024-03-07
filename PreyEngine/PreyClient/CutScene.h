#pragma once
#include "Entity.h"

class ManagerSet;

class CutScene : public Entity
{
public:
	CutScene(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~CutScene();

	//virtual void Update(float _deltaTime) override;

	void StartScene();
	void NextScene();

	void IndexLoad(int _index);

private:
	ManagerSet* managerSet;

	int currentIndex;
	bool isEnd;
};

