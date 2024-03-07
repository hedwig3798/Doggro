#pragma once
#include "Component.h"
#include "SimpleMath.h"
#include "PxPhysicsAPI.h"
#include "Define.h"

using namespace DirectX::SimpleMath;
using namespace physx;

/// <summary>
/// 충돌체들의 부모클래스라 할까,,,
/// 충돌체 인터페이스 같은 거
/// 2024.01.16 chlaudrl
/// physx를 붙인 collider를 다시 만들어보자 
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
	Force,			// 시간동안 일정한 크기와 방향을 유지
	Impulse,		// 힘의 크기와 방향이 순간적으로 적용됨
	VelocityChange,	// 즉각적인 속도 변화
	Acceleration    // 질량을 고려하지 않은 가속도 변화
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

	//물리세계에서 우리세계로 좌표 얻어올 때 쓰는 get 함수
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

	//여기 맘에 안듦
	//float dynamicFriction = 0.5f;   // 동적 마찰
	//float staticFriction = 0.5f;   // 정지 마찰
	//float restitution = 0.0f;	  // 반발력 (0.0 비탄성충돌 ~ 1.0 탄성충돌) 
	//float lineardamping = 0.0f;   // 운동에 적용되는 감속도 (0.0 ~ 1, 0.47:공구형 물체, 0.2:차량,비행기)
	//float angularDamping = 0.5f;	// 최명기면 쌉가능 봐봐 맨날 안 된다더니 바로 물리 끝내버렸잖아 역시 역시 최명기

	float dynamicFriction;   // 동적 마찰
	float staticFriction;   // 정지 마찰
	float restitution;	  // 반발력 (0.0 비탄성충돌 ~ 1.0 탄성충돌) 
	//float lineardamping;   // 운동에 적용되는 감속도 (0.0 ~ 1, 0.47:공구형 물체, 0.2:차량,비행기)
	//float angularDamping;	// 최명기면 쌉가능 봐봐 맨날 안 된다더니 바로 물리 끝내버렸잖아 역시 역시 최명기

	void CallbackDeleteTrigger(unsigned int id);

	std::map<unsigned int, Collider*> triggerOthers;

	BodyType type = BodyType::Dynamic;
	ShapeType shapeType = ShapeType::NonePlane;
};

//이건 생성된 콜라이더를 저장해주는 것
struct ColliderInfo
{
	Collider* collider;
	ColliderInfo(Collider* _collider)
		:collider(_collider)
	{}
};

//이거는 두개의 콜라이더가 충돌하기 위해 만들어진 구조체 제일 기본적인 유형
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

//충돌한 collision들을 담아서 저장하는 구조체
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
