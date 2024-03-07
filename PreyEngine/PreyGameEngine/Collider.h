#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "PxPhysicsAPI.h"
#include "Define.h"

using namespace DirectX::SimpleMath;
using namespace physx;

/// <summary>
/// �浹ü���� �θ�Ŭ������ �ұ�,,,
/// �浹ü �������̽� ���� ��
/// 2024.01.16 chlaudrl
/// physx�� ���� collider�� �ٽ� ������ 
/// 2024.01.30 chlaudrl
/// </summary>

class Entity;
class SphereCollider;
class BoxCollider;
class CollsionManager;
struct CollisionInfo;
struct ColliderInfo;

enum class BodyType
{
	Static,
	Dynamic,
	Kinematic
};

enum class ForceMode
{
	Force,			// �ð����� ������ ũ��� ������ ����
	Impulse,		// ���� ũ��� ������ ���������� �����
	VelocityChange,	// �ﰢ���� �ӵ� ��ȭ
	Acceleration    // ������ ������� ���� ���ӵ� ��ȭ
};

class Collider : public Component
{
public:
	Collider(Entity* _entity, CollsionManager* _collisionmanager);
	virtual ~Collider();

	virtual void Start() override;
	virtual void FixedUpdate(float _deltaTime);
	virtual void Update(float _deltaTime) override;
	virtual void Finalize() override;
	void UpdateTransform(Vector3 _worldPosition, Quaternion _worldQuaternion);
	PxTransform MatToPxTransform(Matrix mat);

	//void SetLayerCollision(FilterGroup _filter);

	const unsigned int GetId() const { return id; }
	DirectX::SimpleMath::Matrix GetTransformMatrix() const { return transformMatrix; }
	DirectX::SimpleMath::Vector3 GetTranslation() const { return translation; }

	Vector3 ToEulerAngle(Quaternion _q);

	//�������迡�� �츮����� ��ǥ ���� �� ���� get �Լ�
	DirectX::SimpleMath::Vector3 GetRotation() const { return rotation; }
	DirectX::SimpleMath::Vector3 GetScale() const { return scale; }
	DirectX::SimpleMath::Quaternion GetQuaternionRotation() const { return quaternionRotation; }

public:
	void OnCollisionEnter(const CollisionInfo& _collision);
	void OnCollisionStay(const CollisionInfo& _collision);
	void OnCollisionExit(const CollisionInfo& _collision);

	void OnTriggerEnter(ColliderInfo* _collision);
	void OnTriggerExit(ColliderInfo* _collision);

	virtual bool IsRigid() const = 0;

	void AddForce(Vector3 _force, ForceMode _forceMode);
	
	bool IsGravity;
	PxRigidDynamic* rigidDynamic;

protected:
	enum class ShapeType
	{
		Plane,
		NonePlane,
	};
protected:
	const unsigned int id;

	CollsionManager* collisionManager;
	Matrix transformMatrix;
	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;
	Quaternion quaternionRotation;

	PxPhysics* physics;
	//PxRigidBody* rigidbody;
	PxRigidStatic* rigidStatic;
	PxShape* shape;
	PxMaterial* material;

	//���� ���� �ȵ�
	//float dynamicFriction = 0.5f;   // ���� ����
	//float staticFriction = 0.5f;   // ���� ����
	//float restitution = 0.0f;	  // �ݹ߷� (0.0 ��ź���浹 ~ 1.0 ź���浹) 
	//float lineardamping = 0.0f;   // ��� ����Ǵ� ���ӵ� (0.0 ~ 1, 0.47:������ ��ü, 0.2:����,�����)
	//float angularDamping = 0.5f;	// �ָ��� �԰��� ���� �ǳ� �� �ȴٴ��� �ٷ� ���� ���������ݾ� ���� ���� �ָ��

	float dynamicFriction;   // ���� ����
	float staticFriction;   // ���� ����
	float restitution;	  // �ݹ߷� (0.0 ��ź���浹 ~ 1.0 ź���浹) 
	//float lineardamping;   // ��� ����Ǵ� ���ӵ� (0.0 ~ 1, 0.47:������ ��ü, 0.2:����,�����)
	//float angularDamping;	// �ָ��� �԰��� ���� �ǳ� �� �ȴٴ��� �ٷ� ���� ���������ݾ� ���� ���� �ָ��

	void CallbackDeleteTrigger(unsigned int id);

	std::map<unsigned int, Collider*> triggerOthers;

	BodyType type = BodyType::Dynamic;
	ShapeType shapeType = ShapeType::NonePlane;
};

//�̰� ������ �ݶ��̴��� �������ִ� ��
struct ColliderInfo
{
	Collider* collider;
	ColliderInfo(Collider* _collider)
		:collider(_collider)
	{}
};

//�̰Ŵ� �ΰ��� �ݶ��̴��� �浹�ϱ� ���� ������� ����ü ���� �⺻���� ����
struct Collision
{
	Collider* thisCollider;
	Collider* otherCollider;
	//Contact* contact;

	Collision(Collider* _thisCollider, Collider* _otherCollider)
		:thisCollider(_thisCollider), otherCollider(_otherCollider)
	{ }
	Collision()
		:thisCollider(nullptr), otherCollider(nullptr)
	{}
};

//�浹�� collision���� ��Ƽ� �����ϴ� ����ü
struct CollisionInfo
{
	Collision collision;

	CollisionInfo(ColliderInfo* _thisInfo, ColliderInfo* _otherInfo)
	{
		collision.thisCollider = _thisInfo->collider;
		if (_otherInfo != nullptr)
		{
			collision.otherCollider = _otherInfo->collider;
		}
	}
};
