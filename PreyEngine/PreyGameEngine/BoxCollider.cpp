#include "BoxCollider.h"
#include "CollsionManager.h"
#include "Transform.h"
#include "Entity.h"
#include "ShoebillPxEventCallback.h"

BoxCollider::BoxCollider(Entity* _entity, CollsionManager* _collisionManager)
	:Collider(_entity,_collisionManager),lineardamping(0.5f), angularDamping(0.5f)
	/*, size{ 10.f,10.f,10.f }*/
{

}

BoxCollider::~BoxCollider()
{
//	Finalize();
	
}

void BoxCollider::Start()
{

	Matrix mat = entity->GetComponent<Transform>()->GetLocalMatrix();
	rigidDynamic = physics->createRigidDynamic(MatToPxTransform(mat));

	rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);

	shape = physics->createShape(
		PxBoxGeometry(size.x*0.5f, size.y* 0.5f, size.z* 0.5f),
		&material, 1, true);


	//rigidDynamic->attachShape(*shape);
	rigidDynamic->setLinearDamping(lineardamping);
	rigidDynamic->setAngularDamping(angularDamping);
	rigidDynamic->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 1.0f);
	//rigidDynamic->setMassSpaceInertiaTensor(PxVec3{ 0.1f, 1.0f, 0.1f });
	//rigidDynamic->detachShape(*shape);
	//entity->SetLayerCollision(FilterGroup::BOX);
	//SetLayerCollision(entity->GetLayerCollision());
	SetUpFiltering(shape, FilterGroup::eBox, FilterGroup::DEFAULT);
	shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	ColliderInfo* userData = new ColliderInfo(this);
	rigidDynamic->userData = userData;
	
	collisionManager->AddActor(rigidDynamic);

	//rigidDynamic->addForce(PxVec3(10.f, 10.f, 10.f), PxForceMode::eFORCE);

	//rigidDynamic->addForce(PxVec3(10.f, 10.f, 10.f), PxForceMode::eIMPULSE, true);
}

void BoxCollider::FixedUpdate(float _deltaTime)
{
	Collider::FixedUpdate(_deltaTime);
}

void BoxCollider::Update(float _deltaTime)
{
	Collider::Update(_deltaTime);
}

void BoxCollider::Finalize()
{
	Collider::Finalize();
}