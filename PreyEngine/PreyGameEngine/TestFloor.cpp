#include "TestFloor.h"
#include "CollsionManager.h"
#include "IGraphicsEngine.h"
#include "ShoebillPxEventCallback.h"

TestFloor::TestFloor(Entity* _entity, CollsionManager* _collisionManager)
	: Collider(_entity, _collisionManager)
{
	type = BodyType::Static; //정적타입
	shapeType = ShapeType::Plane;
}

TestFloor::~TestFloor()
{
}

void TestFloor::Start()
{
	rigidStatic = PxCreatePlane(*physics, PxPlane(0, 1, 0, 0), *material);
	collisionManager->AddActor(rigidStatic);
}

void TestFloor::Update(float _deltaTime)
{
}

void TestFloor::Finalize()
{
	Collider::Finalize();
}
