#include "CollsionManager.h"
#include "Collider.h"
#include "headers.h"
#include "ShoebillPxEventCallback.h"
#include "Filter.h"
#include "../PhysX/extensions/PxSceneQueryExt.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "ICamera.h"
#include "Entity.h"

void CollsionManager::Initialize(ManagerSet* _managerSet)
{
	managerSet = _managerSet;
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

	pvd = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, pvd);

	assert(physics && "PxCreatePhysics failed!");

	//사용자 콜백 함수 정의
	static ShoebillPxEventCallback collisionCallback;

	dispatcher = PxDefaultCpuDispatcherCreate(2);
	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -98.1f, 0.0f);
	sceneDesc.cpuDispatcher = dispatcher;
	//sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	sceneDesc.filterShader = boxCollisionFilterShader;
	sceneDesc.simulationEventCallback = &collisionCallback;
	sceneDesc.flags |= PxSceneFlag::eENABLE_ACTIVE_ACTORS;
	sceneDesc.flags |= PxSceneFlag::eENABLE_STABILIZATION;

	scene = physics->createScene(sceneDesc);
	scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	scene->setSimulationEventCallback(&eventCallback);

	PxPvdSceneClient* pvdClient = scene->getScenePvdClient();
	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	//filter = new Filter(managerSet);
}

void CollsionManager::Start()
{

}

void CollsionManager::Update(double _deltaTime)
{
	scene->simulate(_deltaTime);
	physx::PxU32 a;
	bool c = scene->fetchResults(true, &a);

	PxU32 nbActiveActors;
	PxActor** activeActors = scene->getActiveActors(nbActiveActors);

	for (PxU32 i = 0; i < nbActiveActors; ++i)
	{
		PxRigidActor* rigidActor = activeActors[i]->is<PxRigidActor>();
		if (rigidActor)
		{
			ColliderInfo* collider = static_cast<ColliderInfo*>(rigidActor->userData);
			if (collider)
			{
				Collider* myCollider = collider->collider;
				if (myCollider != nullptr)
				{
					//myCollider->rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, myCollider->IsGravity);
					PxVec3 pos = rigidActor->getGlobalPose().p;
					PxQuat rotq = rigidActor->getGlobalPose().q;
					Quaternion rot{ rotq.x,rotq.y,rotq.z,rotq.w };

					myCollider->UpdateTransform(Vector3(pos.x, pos.y, pos.z), rot);
					myCollider->FixedUpdate(_deltaTime);
				}
			}
		}
	}


}

void CollsionManager::Finalize()
{
	PX_RELEASE(scene);
	PX_RELEASE(dispatcher);
	PX_RELEASE(physics);
	PX_RELEASE(foundation);
}

std::vector<Entity*> CollsionManager::PickedObject(ICamera* _camera)
{
	std::vector<Entity*> result;
	if (this->managerSet->GetInputManager()->GetKeyState(KEY::LMOUSE) == KEY_STATE::HOLD)
	{
		{
			std::vector<float> cameraPos = _camera->GetPostion();
			POINT mousePos = this->managerSet->GetInputManager()->GetCurrentMousePos();
			std::vector<float> clickVector = _camera->GetClickVector(mousePos.x, mousePos.y);

			PxVec3 origin = { cameraPos[0], cameraPos[1], -cameraPos[2] };                 // [in] Ray origin
			PxVec3 unitDir = { clickVector[0], clickVector[1], -clickVector[2] };               // [in] Normalized ray direction
			unitDir = unitDir.getNormalized();
			PxReal maxDistance = 10000;            // [in] Raycast max distance
			PxRaycastBuffer hit;                 // [out] Raycast results
			// const PxSceneQueryFlags outputFlags = PxSceneQueryFlag::eANY_HIT;
			// PxRaycastHit hitBuffer[16];
			// Raycast against all static & dynamic objects (no filtering)
			// The main result from this call is the closest hit, stored in the 'hit.block' structure
			const PxU32 bufferSize = 16;        // [in] size of 'hitBuffer'
			PxRaycastHit hitBuffer[bufferSize];  // [out] User provided buffer for results
			PxRaycastBuffer buf(hitBuffer, bufferSize); // [out] Blocking and touching hits stored here
			bool status = scene->raycast(origin, unitDir, maxDistance, buf);

			// 	PxSceneQueryExt::raycastMultiple(
			// 		*this->scene,
			// 		origin, unitDir,
			// 		maxDistance,
			// 		outputFlags,
			// 		hitBuffer,
			// 		16,
			// 		status);

			if (status)
			{
				for (PxU32 i = 0; i < buf.nbTouches; i++)
				{
					PxRigidActor* actor = buf.getTouch(i).actor->is<PxRigidActor>();
					ColliderInfo* collider = static_cast<ColliderInfo*>(actor->userData);
					if (collider != nullptr)
					{
						result.push_back(collider->collider->GetEntity());
						rayColliderName = collider->collider->GetEntity()->GetName();
					}
				}

			}
		}
	}
	return result;
}

void CollsionManager::AddActor(PxActor* _actor)
{
	scene->addActor(*_actor);
}

void CollsionManager::RemoveActor(PxActor* _actor)
{
	if (_actor && scene != nullptr)
	{
		scene->removeActor(*_actor);
		bool a = _actor->isReleasable();
		_actor->release();
	}
	scene->forceDynamicTreeRebuild(true, true);
}

void CollsionManager::Clear()
{

}

/// <summary>
/// 최명기가 짱이다
/// 아무도 날 막을 수 없어
/// 내 코드 훔쳐가지마- 김유진씀
/// </summary>
/// <param name="_pair"></param>
/// <param name="_events"></param>
void CollsionManager::onContactNotify(PxContactPair& _pair, PxU32 _events)
{
	/*USERDATA* userData1 = NULL;
	USERDATA* userData2 = NULL;

	switch (_events)
	{
	case PxPairFlag::eNOTIFY_TOUCH_FOUND:
		userData1 = (USERDATA*)_pair.actors[0]->userData;


	}*/
}

//void CollsionManager::SetUpFiltering(PxRigidActor* actor, PxU32 _filterGroup, PxU32 _filterMask)
//{
//	PxFilterData filterData;
//	filterData.word0 = _filterGroup; // word0 = own ID
//	filterData.word1 = _filterMask;	// word1 = ID mask to filter pairs that trigger a contact callback;
//	const PxU32 numShapes = actor->getNbShapes();
//	PxShape** shapes = (PxShape**)allocator.allocate(sizeof(PxShape*) * numShapes, 0, __FILE__, __LINE__);
//	actor->getShapes(shapes, numShapes);
//	for (PxU32 i = 0; i < numShapes; i++)
//	{
//		PxShape* shape = shapes[i];
//		shape->setSimulationFilterData(filterData);
//	}
//	allocator.deallocate(shapes);
//}

//
//void CollsionManager::SetUpFiltering(PxShape* _shape, FilterGroup _filterGroup)
//{
//	filter->SetupFiltering(_shape, _filterGroup);
//}
