#pragma once
#include "Scene.h"

class MainScene : public Scene
{
public:
	MainScene(std::string _name);
	virtual ~MainScene();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

	Entity* titleStart;
	Entity* titleStart2;
	Entity* titleExit;
	Entity* titleExit2;
	Entity* titleCredit;
	Entity* titleCredit2;
	Entity* stamp;

	void DeleteLiveObject();
};

