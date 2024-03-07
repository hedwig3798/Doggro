#pragma once
#include "PxPhysicsAPI.h"
#include "headers.h"
#include "SimpleMath.h"

/// <summary>
/// �ϴ� �ϳ��� �� ���Ƴ��� ������ ������ �����ͺ���
/// ����� ����
/// 2024.01.31 chlaudrl
/// </summary>

enum class eActorType
{
	Static,
	Dynamic
};

class PhysxEngine
{
public:
	PhysxEngine();
	~PhysxEngine();

	void Initialize();
	void PhysxMaterialInitialize();
	void Update(double _deltaTime);

	//DirectX::SimpleMath::Matrix PxTransformToSimpleMathMatrix(const physx::PxTransform& pxTrans);

	physx::PxDefaultAllocator allocator;
	physx::PxDefaultErrorCallback errorcallback;
	physx::PxFoundation* foundation = NULL;
	physx::PxPhysics* physics = NULL;
	physx::PxDefaultCpuDispatcher* dispatcher = NULL;
	physx::PxScene* scene = NULL;
	physx::PxMaterial* material = NULL;
	physx::PxPvd* pvd = NULL;

	std::unordered_map<std::string, physx::PxMaterial*> m_PhysicsMaterialMap;
	std::unordered_map<std::string, physx::PxRigidActor*> m_PhysicsActors;

	void SetMaterial(physx::PxU32 _id, std::string _name);
	void AddMaterial(std::string _materialName, float _staticFriction, float _dynamicFriction, float _restitution);
	physx::PxMaterial* FindMaterial(std::string _materialName);

	void MakeBoxCollider(std::string _name, const physx::PxTransform& _pose, const physx::PxVec3& _size, physx::PxMaterial* _material, float _density, eActorType _type);
	void MakeBoxCollider(std::string _name, const physx::PxTransform& _pose, float _x, float _y, float _z, physx::PxMaterial* _material, float _density, eActorType _type);
	void MakeCapsuleCollider(std::string name, const physx::PxTransform& _pose, float _radius, float _halfHeight, physx::PxMaterial* _material, float _density);
	//���ӿ�����ƮID, ���� ����, ���� ũ��
	void AddForce(std::string _GameObjectid, const physx::PxVec3 _forcedir, float _force);

	void Finalize();

};

namespace Physics
{
	PhysxEngine* GetInstance();

	void Destroy();
}
