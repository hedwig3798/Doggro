#pragma once
#include "Collider.h"

/// <summary>
/// �̹����� sphere �浹ü ������
/// 2024.02.01 chlaudrl
/// </summary>

class Entity;
class CollsionManager;

class SphereCollider :  public Collider
{
public:
	SphereCollider(Entity* _entity, CollsionManager* _collisionManager);
	~SphereCollider();

	virtual void Start() override;
	virtual void FixedUpdate(float _deltaTime);
	virtual void Update(float _deltaTime) override;
	virtual void Finalize() override;

	virtual bool IsRigid() const override { return true; }

	float GetRadius() const { return radius; }
	void SetRadius(float val) { radius = val; }

	bool ISCollision();

private:
	float radius;

	float lineardamping;
	float angularDamping;
};

