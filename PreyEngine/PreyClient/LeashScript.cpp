#include "LeashScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

LeashScript::LeashScript(Entity* _entity)
	: Component(_entity, "LeashScript")
{

}

LeashScript::~LeashScript()
{

}

void LeashScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage2 Quest2 신발장에 신발 올리기
	if (name == "shoe_rack")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isLeashPutting = true;
		}
	}
}

void LeashScript::OnCollisionExit(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage2 Quest2 신발장에 신발 올리기
	if (name == "shoe_rack")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isLeashPutting = false;
		}
	}
}
