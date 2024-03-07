#pragma once
#include "Collider.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 박스 콜라이더 만들기
/// 2024.01.23 chlaudrl
/// </summary>

class Entity;
class Transform;
class CollsionManager;

class BoxCollider : public Collider
{
public:
	BoxCollider(Entity* _entity, CollsionManager* _collisionManager);
	virtual ~BoxCollider();

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

