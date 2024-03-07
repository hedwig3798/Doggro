#include "BowlScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

BowlScript::BowlScript(Entity* _entity)
	: Component(_entity, "DollScript")
{

}

BowlScript::~BowlScript()
{

}

void BowlScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage2 Quest1 å�� ��׸� �ø���
	if (name == "tableCollider")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isBowlPutting = true;
		}
	}
	

}

void BowlScript::OnCollisionExit(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage2 Quest1 å�� ��׸� �ø���
	if (name == "table")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isBowlPutting = false;
		}
	}
}
