#pragma once
#include "headers.h"
#include "Define.h"

#include "PxPhysicsAPI.h"
#include "ShoebillPxErrorCallback.h"
#include "ShoebillPxEventCallback.h"
#include "Filter.h"
#include "ManagerSet.h"
using namespace physx;

/// <summary>
/// collider를 관리하는 매니저
/// 추가와 삭제 등을 담당한다.
/// 
/// 여기에 PhysX를 붙인 걸 관리한다.
/// 2024.01.25 chlaudrl
/// </summary>

class Collider;

class ICamera;

class CollsionManager
{
public:
	CollsionManager() = default;
	~CollsionManager() = default;

	void Initialize(ManagerSet* _managerSet);
	void Start();
	void Update(double _deltaTime);
	void Finalize();

	std::vector<Entity*> PickedObject(ICamera* _camera);

	static unsigned int GetColliderID() { static unsigned int ID = 0; return ID++; }

	void AddActor(PxActor* _actor);
	void RemoveActor(PxActor* _actor);
	void Clear();

	physx::PxPhysics* GetPhysics() const { return physics; }

	void onContactNotify(PxContactPair& _pair, PxU32 _events);
	//void SetUpFiltering(PxRigidActor* actor, PxU32 _filterGroup, PxU32 _filterMask);

	physx::PxDefaultAllocator GetAllocator() const { return allocator; }

	float getGravity() const { return gravity; }
	void setGravity(float val) { gravity = val; }

	std::string GetRayColliderName() const { return rayColliderName; }

	PxScene* scene;
private:
	ShoebillPxErrorCallback errorCallback;
	ShoebillPxEventCallback eventCallback;
	PxDefaultAllocator allocator;
	PxFoundation* foundation;
	PxPhysics* physics;
	PxDefaultCpuDispatcher* dispatcher;
	PxPvd* pvd;

	ManagerSet* managerSet;
	float gravity;

	std::string rayColliderName;
};

 