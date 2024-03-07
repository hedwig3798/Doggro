#include "StaticCollider.h"
#include "CollsionManager.h"
#include "Transform.h"
#include "Entity.h"
#include "ShoebillPxEventCallback.h"

StaticCollider::StaticCollider(Entity* _entity, CollsionManager* _collisionManager)
	: Collider(_entity, _collisionManager)
	, lineardamping(0.05f)
	, angularDamping(0.05f)
{
	type = BodyType::Static; //정적타입
}

StaticCollider::~StaticCollider()
{

}

void StaticCollider::Start()
{
	Matrix mat = entity->GetComponent<Transform>()->GetLocalMatrix();
	rigidStatic = physics->createRigidStatic(MatToPxTransform(mat));
	//rigidStatic->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false);

	shape = physics->createShape(
		PxBoxGeometry(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f),
		&material, 1, true);


	//rigidDynamic->attachShape(*shape);
	rigidStatic->attachShape(*shape);
	//PxRigidBodyExt::updateMassAndInertia(*rigidStatic, 100.0f);

	//rigidDynamic->detachShape(*shape);
	//entity->SetLayerCollision(FilterGroup::BOX);
	//SetLayerCollision(entity->GetLayerCollision());
	SetUpFiltering(shape, FilterGroup::eBox, FilterGroup::DEFAULT);
	shape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	ColliderInfo* userData = new ColliderInfo(this);
	rigidStatic->userData = userData;

	collisionManager->AddActor(rigidStatic);
}

void StaticCollider::FixedUpdate(float _deltaTime)
{
	Collider::FixedUpdate(_deltaTime);
}

void StaticCollider::Update(float _deltaTime)
{
	Collider::Update(_deltaTime);
}

void StaticCollider::Finalize()
{
	Collider::Finalize();
}
