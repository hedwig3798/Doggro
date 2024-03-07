#pragma once
#include "Component.h"

/// <summary>
/// Entity�� ������ �� �ִ� Component
/// </summary>
class Movable : public Component
{
public:
	Movable(Entity* _entity);
	virtual ~Movable();

	virtual void Update(float _deltaTime) override;

private:
	ManagerSet* managerSet;
};