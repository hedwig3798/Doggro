#include "HumanScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

HumanScript::HumanScript(Entity* _entity)
	:Component(_entity, "HumanScript")
{

}

HumanScript::~HumanScript()
{

}

void HumanScript::OnCollisionEnter(const Collision& _collision)
{

}

void HumanScript::OnCollisionExit(const Collision& _collision)
{

}

void HumanScript::OnTriggerEnter(Collider* collider)
{
	//stage4 Quest 2, 3번을 위한 Trigger
	std::string name = collider->GetEntity()->GetName();
	
	if (name == "door")
	{
		if (questManager->stageNumber == 4)
		{
			questManager->isManArrive = true;
		}
	}

	if (name == "Dog")
	{
		if (questManager->stageNumber == 4)
			questManager->isQuest2Start = true;
	}
}

void HumanScript::OnTriggerExit(Collider* collider)
{
	//stage4 Quest 2, 3번을 위한 Trigger
	std::string name = collider->GetEntity()->GetName();

	if (name == "Dog")
	{
		if (questManager->stageNumber == 4)
			questManager->isQuest2Start = false;
	}
}
