#pragma once
#include "Component.h"


class Move : public Component
{
public:
	Move(Entity* _entity);
	virtual ~Move();


	virtual void Update(float _deltaTime) override;
private:
	ManagerSet* managerSet;
};

