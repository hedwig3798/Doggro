#pragma once
#include "Component.h"
#include <vector>

class Debug : public Component
{
public:
	Debug(Entity* _entity);
	virtual ~Debug();

	virtual void Update(float _deltaTime) override;
	virtual void Render() override;

private:
	ManagerSet* managerSet;

};

