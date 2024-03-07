#include "FilterCollider.h"
#include "CollsionManager.h"
#include "Transform.h"
#include "Entity.h"
#include "ShoebillPxEventCallback.h"

FilterCollider::FilterCollider(Entity* _entity, CollsionManager* _collisionManager)
	: Collider(_entity, _collisionManager), lineardamping(1.0f), angularDamping(1.0f)
{

}

FilterCollider::~FilterCollider()
{

}

void FilterCollider::Start()
{
	Matrix mat = entity->GetComponent<Transform>()->GetLocalMatrix();
	rigidDynamic = physics->createRigidDynamic(MatToPxTransform(mat));
	rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);

	shape = physics->createShape(
		PxBoxGeometry(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f),
		&material, 1, true);

	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);

	//rigidDynamic->attachShape(*shape);
	rigidDynamic->setLinearDamping(lineardamping);
	rigidDynamic->setAngularDamping(angularDamping);
	rigidDynamic->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 1.0f);

	//rigidDynamic->detachShape(*shape);
	//entity->SetLayerCollision(FilterGroup::BOX);
	//SetLayerCollision(entity->GetLayerCollision());
	SetUpFiltering(shape, FilterGroup::eFILTER, FilterGroup::DEFAULT);
	// 	shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	// 	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	ColliderInfo* userData = new ColliderInfo(this);
	rigidDynamic->userData = userData;

	collisionManager->AddActor(rigidDynamic);
}

void FilterCollider::FixedUpdate(float _deltaTime)
{
	Collider::FixedUpdate(_deltaTime);
}

void FilterCollider::Update(float _deltaTime)
{
	Collider::Update(_deltaTime);
}

void FilterCollider::Finalize()
{
	Collider::Finalize();
}
