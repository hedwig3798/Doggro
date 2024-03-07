#include "Collider.h"
#include "CollsionManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Define.h"


Collider::Collider(Entity* _entity, CollsionManager* _collisionmanager)
	:Component(_entity, "Collider")
	, collisionManager(_collisionmanager)
	, physics(nullptr), material(nullptr), rigidDynamic(nullptr), rigidStatic(nullptr)
	, shape(nullptr), dynamicFriction(0.5f), staticFriction(0.5f), restitution(0.5f)
	, id(_collisionmanager->GetColliderID())
{
	physics = collisionManager->GetPhysics();
	material = physics->createMaterial(dynamicFriction, staticFriction, restitution);
}

Collider::~Collider()
{
	//Finalize();
}


void Collider::Start()
{

}

void Collider::FixedUpdate(float _deltaTime)
{
	//이건 물리 세계에서 우리세계로 좌표를 바꿀 때 우리세계에서 위치를 계속 바꿔주기 위해서 받아온다.
	if (this->entity->GetName() == "Dog")
	{
		entity->GetComponent<Transform>()->SetPosition(GetTranslation());
		return;
	}
	entity->GetComponent<Transform>()->SetPosition(GetTranslation());
	entity->GetComponent<Transform>()->SetRotation(GetQuaternionRotation());
}

void Collider::Update(float _deltaTime)
{
	Matrix mat = entity->GetComponent<Transform>()->GetFinalMatrix();
	//동적인지 정적인지 나눠서 위치를 업데이트 해줌 
	switch (type)
	{
	case BodyType::Static:
		rigidStatic->setGlobalPose(MatToPxTransform(mat));
		break;

	case BodyType::Dynamic:
		rigidDynamic->setGlobalPose(MatToPxTransform(mat));
		break;
	}
}

void Collider::Finalize()
{
	Collision* userdt = nullptr;
	auto me = this;

	switch (type)
	{
	case BodyType::Static:
		userdt = static_cast<Collision*>(rigidStatic->userData);
		collisionManager->RemoveActor(rigidStatic);
		break;

	case BodyType::Dynamic:
		userdt = static_cast<Collision*>(rigidDynamic->userData);
		collisionManager->RemoveActor(rigidDynamic);
		break;
	}

	//if (userdt)
	//{
	//	userdt->thisCollider = nullptr;
	//	userdt->otherCollider = nullptr;
 //	//	delete userdt;
	//}
}

void Collider::UpdateTransform(Vector3 _worldPosition, Quaternion _worldQuaternion)
{
	Vector3 pos(_worldPosition.x, _worldPosition.y, -_worldPosition.z);
	Quaternion _quaternionRotation(_worldQuaternion.x, _worldQuaternion.y, _worldQuaternion.z, _worldQuaternion.w);
	//Vector3 tmpRotation = ToEulerAngle(_quaternionRotation);
	//tmpRotation = Vector3{ tmpRotation.x, tmpRotation.y, -tmpRotation.z };

	//_quaternionRotation = Quaternion::CreateFromYawPitchRoll(tmpRotation.x, tmpRotation.y, -tmpRotation.z);

	transformMatrix = Matrix::CreateFromQuaternion(_quaternionRotation) * Matrix::CreateTranslation(pos);

	//물리세계에서 우리 세계로 좌표를 넘겨줄때 한번에 뽑는 것
	transformMatrix.Decompose(scale, _quaternionRotation, translation);

	quaternionRotation = _quaternionRotation;

	//쿼터니언에서 오일러 각도로 담아준다. Vector로 바꾸기 위해
	rotation = ToEulerAngle(quaternionRotation);
	rotation = quaternionRotation.ToEuler();
	if (this->entity->GetName() == "Dog")
	{
		rotation.x = 0;
		rotation.z = 0;
		rotation.y = 0;
	}
}


physx::PxTransform Collider::MatToPxTransform(Matrix mat)
{
	Vector3 position = {};
	Quaternion quaternion = {};
	Vector3 scale = {};

	mat.Decompose(scale, quaternion, position);

	//오프셋 적용
	//position += offset;

	// 추출한 위치와 회전을 사용하여 PxTransform 생성
	physx::PxVec3 pxPosition(position.x, position.y, -position.z);
	physx::PxQuat pxQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);

	return physx::PxTransform(pxPosition, pxQuaternion);
}

//void Collider::SetLayerCollision(FilterGroup _filter)
//{
//	if (shapeType == ShapeType::Plane)
//		return;
//
//	switch (type)
//	{
//	case BodyType::Static:
//		//collisionManager->SetUpFiltering(shape, _filter);
//		break;
//
//	case BodyType::Dynamic:
//		//collisionManager->SetUpFiltering(shape, _filter);
//		break;
//	}
//}

DirectX::SimpleMath::Vector3 Collider::ToEulerAngle(Quaternion _q)
{
	Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (_q.w * _q.x + _q.y * _q.z);
	double cosr_cosp = 1 - 2 * (_q.x * _q.x + _q.y * _q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (_q.w * _q.y - _q.x * _q.z));
	double cosp = std::sqrt(1 - 2 * (_q.w * _q.y - _q.x * _q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (_q.w * _q.z + _q.x * _q.y);
	double cosy_cosp = 1 - 2 * (_q.y * _q.y + _q.z * _q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

void Collider::OnCollisionEnter(const CollisionInfo& _collision)
{
	//IsGravity = true; //충돌하면 중력이 꺼지는거
	GetEntity()->OnCollisionEnter(_collision.collision);
}

void Collider::OnCollisionStay(const CollisionInfo& _collision)
{

}

void Collider::OnCollisionExit(const CollisionInfo& _collision)
{
	//IsGravity = false;
	GetEntity()->OnCollisionExit(_collision.collision);
}

void Collider::OnTriggerEnter(ColliderInfo* _collider)
{
	GetEntity()->OnTriggerEnter(_collider->collider);
}

void Collider::OnTriggerExit(ColliderInfo* _collider)
{
	GetEntity()->OnTriggerExit(_collider->collider);
}

void Collider::AddForce(Vector3 _force, ForceMode _forceMode)
{
	switch (_forceMode)
	{
	case ForceMode::Force:
		rigidDynamic->addForce(PxVec3(_force.x, _force.y, _force.z), PxForceMode::eFORCE);
		break;
	case ForceMode::Impulse:
		rigidDynamic->addForce(PxVec3(_force.x, _force.y, _force.z), PxForceMode::eIMPULSE);
		break;
	case ForceMode::VelocityChange:
		rigidDynamic->addForce(PxVec3(_force.x, _force.y, _force.z), PxForceMode::eVELOCITY_CHANGE);
		break;
	case ForceMode::Acceleration:
		rigidDynamic->addForce(PxVec3(_force.x, _force.y, _force.z), PxForceMode::eACCELERATION);
		break;
	}
}
