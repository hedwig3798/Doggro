#pragma once
#include "Collider.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

class Entity;
class Transform;
class CollsionManager;

class StaticCollider : public Collider
{
public:
	StaticCollider(Entity* _entity, CollsionManager* _collisionManager);
	virtual ~StaticCollider();

	virtual void Start() override;
	virtual void FixedUpdate(float _deltaTime) override;
	virtual void Update(float _deltaTime) override;
	virtual void Finalize() override;

	virtual bool IsRigid() const override { return true; }

	DirectX::SimpleMath::Vector3 GetSize() const { return size; }
	void SetSize(DirectX::SimpleMath::Vector3 val) { size = val; }

private:
	Vector3 size;
	bool isSleep = false;

	float lineardamping;
	float angularDamping;
};

