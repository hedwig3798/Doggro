#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene(std::string _name);
	virtual ~TestScene();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;

private:
	Entity* player;
	Entity* player2;
	Entity* testphysx;
	Entity* testBox;
};

