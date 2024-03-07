#include "DollScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

DollScript::DollScript(Entity* _entity)
	: Component(_entity, "DollScript")
{

}

DollScript::~DollScript()
{

}

void DollScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage3 Quest2 ħ�뿡 �÷�����
	//ħ��� �浹 ��, ���ֹ�����.
	if (name == "bedCollider")
	{
		if (questManager->stageNumber == 3)
		{
			entity->GetComponent<DrawType>()->SetAObjectVisible(false);
			questManager->isDollHiding = true;
		}
		
	}

}

void DollScript::OnCollisionExit(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	if (name == "bed")
	{
		if (questManager->stageNumber == 3)
		{
			entity->GetComponent<DrawType>()->SetAObjectVisible(false);
			questManager->isDollHiding = false;
		}

	}
}
