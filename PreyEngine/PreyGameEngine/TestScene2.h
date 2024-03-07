#pragma once
#include "Scene.h"

class TestScene2 : public Scene
{
public:
	TestScene2(std::string _name);
	virtual ~TestScene2();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;

private:

};

