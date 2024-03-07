#include "SphereCollider.h"
#include "CollsionManager.h"
#include "Entity.h"
#include "Transform.h"
#include "ShoebillPxEventCallback.h"

SphereCollider::SphereCollider(Entity* _entity, CollsionManager* _collisionManager)
	:Collider(_entity, _collisionManager), lineardamping(0.05f), angularDamping(0.05f)
	/*,radius{10.0f}*/
{
}

SphereCollider::~SphereCollider()
{

}

void SphereCollider::Start()
{
	Matrix mat = entity->GetComponent<Transform>()->GetLocalMatrix();
	rigidDynamic = physics->createRigidDynamic(MatToPxTransform(mat));
	rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);

	shape = physics->createShape(PxSphereGeometry(radius), &material,1, true);

	/*rigidDynamic->attachShape(*shape);

	rigidDynamic->detachShape(*shape);*/
	//entity->SetLayerCollision(FilterGroup::SPHERE);
	//SetLayerCollision(entity->GetLayerCollision());
	rigidDynamic->setLinearDamping(lineardamping);
	rigidDynamic->setAngularDamping(angularDamping);
	rigidDynamic->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*rigidDynamic, 1.0f);
	SetUpFiltering(shape, FilterGroup::eSPHERE, FilterGroup::DEFAULT);
	shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	ColliderInfo* userData = new ColliderInfo(this);
	rigidDynamic->userData = userData;
	collisionManager->AddActor(rigidDynamic);
}

void SphereCollider::FixedUpdate(float _deltaTime)
{
	Collider::FixedUpdate(_deltaTime);
}

void SphereCollider::Update(float _deltaTime)
{
	
	Collider::Update(_deltaTime);
}

void SphereCollider::Finalize()
{
	Collider::Finalize();
}

bool SphereCollider::ISCollision()
{
	return false;
}
