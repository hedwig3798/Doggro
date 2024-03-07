#include "DogSightScript.h"
#include "Entity.h"

#include "CollsionManager.h"
#include "ManagerSet.h"

DogSightScript::DogSightScript(Entity* _entity)
	: Component(_entity, "DogSightScript")
{

}

DogSightScript::~DogSightScript()
{

}

void DogSightScript::OnCollisionEnter(const Collision& collision)
{
	std::string name = collision.otherCollider->GetEntity()->GetName();
}

void DogSightScript::OnCollisionExit(const Collision& collision)
{
	std::string name = collision.otherCollider->GetEntity()->GetName();
}

void DogSightScript::OnTriggerEnter(Collider* collider)
{
	checkName = collider->GetEntity()->GetName();

	//std::string pickingname = entity->GetManagerset()->GetCollisionManager()->GetRayColliderName();
	//checkName = pickingname;
}

void DogSightScript::OnTriggerExit(Collider* collider)
{

}
