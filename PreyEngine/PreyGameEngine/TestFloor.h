#pragma once
#include "Collider.h"

class CollsionManager;

class TestFloor : public Collider
{
public:
	TestFloor() = delete;
	TestFloor(Entity* _entity, CollsionManager* _collisionManager);
	virtual ~TestFloor();

	void Start();
	virtual void Update(float _deltaTime) override;
	virtual void Finalize() override;

	virtual bool IsRigid() const override { return true; }

private:
	Vector3 normal = Vector3(0, 1, 0);

	float distance = 0;
};

