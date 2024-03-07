#include "PhysxEngine.h"
#include "headers.h"
#include <crtdbg.h>
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;
using namespace physx;

PhysxEngine::PhysxEngine()
{

}

PhysxEngine::~PhysxEngine()
{

}

Matrix PxTransformToSimpleMathMatrix(const PxTransform& pxTrans)
{
	Vector3 position(pxTrans.p.x, pxTrans.p.y, -pxTrans.p.z);
	Quaternion rotation(pxTrans.q.x, pxTrans.q.y, pxTrans.q.z, pxTrans.q.w);

	Matrix simpleMathMatrix = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(position);

	return simpleMathMatrix;
}

//DirectX::SimpleMath::Matrix PhysxEngine::PxTransformToSimpleMathMatrix(const physx::PxTransform& pxTrans)
//{
//	Vector3 position(pxTrans.p.x, pxTrans.p.y, -pxTrans.p.z);
//	Quaternion rotation(pxTrans.q.x, pxTrans.q.y, pxTrans.q.z, pxTrans.q.w);
//
//	Matrix simpleMathMatrix = Matrix::CreateFromQuaternion(rotation) * Matrix::CreateTranslation(position);
//
//	return simpleMathMatrix;
//}

void PhysxEngine::Initialize()
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorcallback);

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true);

	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -981.f, 0.0f);

	dispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;

	scene = physics->createScene(sceneDesc);
	scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);

	PhysxMaterialInitialize();
}

void PhysxEngine::PhysxMaterialInitialize()
{
	AddMaterial("Character1", 0.1f, 0.1f, 0.1f);
	AddMaterial("Character2", 0.1f, 0.1f, 0.1f);
	AddMaterial("Character3", 0.1f, 0.1f, 0.1f);
	AddMaterial("Character4", 0.1f, 0.1f, 0.1f);
}

void PhysxEngine::Update(double _deltaTime)
{
	scene->simulate(_deltaTime);
	scene->fetchResults(true);

	for (auto& actor : m_PhysicsActors)
	{
		// 바뀐 트랜스폼을 렌더매니저에 연결해야됨
		// physx 트랜스폼은 
		PxTransform temp = actor.second->getGlobalPose();
		Matrix result = PxTransformToSimpleMathMatrix(temp);
	}
}

void PhysxEngine::SetMaterial(physx::PxU32 _id, std::string _name)
{
	physx::PxMaterial* tempMaterial = FindMaterial(_name);
}

void PhysxEngine::AddMaterial(std::string _materialName, float _staticFriction, float _dynamicFriction, float _restitution)
{
	if (m_PhysicsMaterialMap.find(_materialName) == m_PhysicsMaterialMap.end())
	{
		physx::PxMaterial* newMaterial = nullptr;
		newMaterial = physics->createMaterial(_staticFriction, _dynamicFriction, _restitution);
		m_PhysicsMaterialMap.insert(std::make_pair(_materialName, newMaterial));
	}
	else
	{
		OutputDebugStringA(_materialName.c_str());
		OutputDebugStringA(": 같은 이름의 PhysicsMaterial(이)가 추가 되었습니다.\n");
	}
}

physx::PxMaterial* PhysxEngine::FindMaterial(std::string _materialName)
{
	assert(m_PhysicsMaterialMap.find(_materialName) != m_PhysicsMaterialMap.end());

	return m_PhysicsMaterialMap[_materialName];
}

void PhysxEngine::MakeBoxCollider(std::string _name, const physx::PxTransform& _pose, const physx::PxVec3& _size, physx::PxMaterial* _material, float _density, eActorType _type)
{
	PxBoxGeometry* box = new PxBoxGeometry(_size);

	if (_type == eActorType::Static)
	{
		PxRigidStatic* actor = physics->createRigidStatic(_pose);
		//actor->setActorFlag(PxActorFlag::eVISUALIZATION, true);

		PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, PxBoxGeometry(*box), *material);
		//shape->setFlag(PxShapeFlag::eVISUALIZATION, true);

		scene->addActor(*actor);
		m_PhysicsActors.insert(std::make_pair(_name, actor));
	}

	else
	{
		PxRigidDynamic* actor = physics->createRigidDynamic(_pose);
		//actor->setActorFlag(PxActorFlag::eVISUALIZATION, true);

		PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, PxBoxGeometry(*box), *material);
		//shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
		PxRigidBodyExt::updateMassAndInertia(*actor, _density);

		actor->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
			PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
			PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

		scene->addActor(*actor);
		m_PhysicsActors.insert(std::make_pair(_name, actor));
	}
}

void PhysxEngine::MakeBoxCollider(std::string _name, const physx::PxTransform& _pose, float _x, float _y, float _z, physx::PxMaterial* _material, float _density, eActorType _type)
{
	PxVec3 temp = { _x, _y, _z };
	MakeBoxCollider(_name, _pose, temp, material, _density, _type);
}

void PhysxEngine::MakeCapsuleCollider(std::string name, const physx::PxTransform& _pose, float _radius, float _halfHeight, physx::PxMaterial* _material, float _density)
{
	float boxheight = _halfHeight - _radius;
	PxCapsuleGeometry* capsule = new PxCapsuleGeometry(_radius, boxheight);


	PxTransform originalTransform(_pose);
	// x축 주위의 90도 회전 각도
	const PxReal rotationAngle = PxPi / 2.0f;
	// 회전 축 설정 (여기서는 x축 주위로 회전하므로 PxVec3(1, 0, 0)을 사용)
	PxVec3 rotationAxis(.0f, .0f, 1.0f);
	// 새로운 회전 행렬 생성
	PxQuat rotationQuaternion(rotationAngle, rotationAxis);
	// 새로운 PxTransform 객체 생성 및 원래의 위치 정보 및 새로운 회전 정보 적용
	PxTransform transformedTransform(originalTransform.p, rotationQuaternion);
	PxRigidDynamic* actor = physics->createRigidDynamic(transformedTransform);
	//actor->setActorFlag(PxActorFlag::eVISUALIZATION, true);


	PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, PxCapsuleGeometry(*capsule), *material);
	//shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	PxRigidBodyExt::updateMassAndInertia(*actor, _density);
	scene->addActor(*actor);
	actor->setRigidDynamicLockFlags(PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
		PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z);

	// actor들 관리할 자료형 있어야 될듯?
	m_PhysicsActors.insert(std::make_pair(name, actor));
}

void PhysxEngine::AddForce(std::string _GameObjectid, const physx::PxVec3 _forcedir, float _force)
{
	assert(m_PhysicsActors.find(_GameObjectid) != m_PhysicsActors.end());

	if (m_PhysicsActors[_GameObjectid]->getType() == PxActorType::eRIGID_DYNAMIC)
	{
		physx::PxVec3 direction = { _forcedir.x,_forcedir.y,-_forcedir.z };
		direction = direction.getNormalized();

		auto GameObejectRigidDyamic = static_cast<PxRigidDynamic*>(m_PhysicsActors[_GameObjectid]);
		if (GameObejectRigidDyamic)
		{
			//크기가 1을 m가 아닌 cm로 취급을 해서 *100을 해줬음.
			GameObejectRigidDyamic->addForce(_force * 100 * direction, PxForceMode::Enum::eIMPULSE);
		}
	}
	else
	{
		OutputDebugStringA(_GameObjectid.c_str());
		OutputDebugStringA(": StaticMesh에는 AddForce를 사용할 수 없습니다.\n");
	}
}

void PhysxEngine::Finalize()
{

}

PhysxEngine* Physics::GetInstance()
{
	static PhysxEngine* instance = nullptr;
	if (instance == nullptr)
	{
		instance = new PhysxEngine();
	}
	return instance;
}

void Physics::Destroy()
{
	PhysxEngine* instance = GetInstance();
	if (instance != nullptr)
	{
		instance->Finalize();
		delete instance;
		instance = nullptr;
	}
}
