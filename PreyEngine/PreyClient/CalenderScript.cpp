#include "CalenderScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

CalenderScript::CalenderScript(Entity* _entity)
	: Component(_entity, "CalenderScript")
{

}

CalenderScript::~CalenderScript()
{

}

void CalenderScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	
}

void CalenderScript::OnCollisionExit(const Collision& _collision)
{

}
