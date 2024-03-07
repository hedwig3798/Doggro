#include "BallScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

BallScript::BallScript(Entity* _entity)
	: Component(_entity, "BallScript")
{
}

BallScript::~BallScript()
{
}

void BallScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage3 Quest2 ħ�뿡 �÷�����
	//ħ��� �浹 ��, ���ֹ�����.

	if (name == "bedCollider")
	{
		if (questManager->stageNumber == 3)
		{
			entity->GetComponent<DrawType>()->SetAObjectVisible(false);
			questManager->isBallHiding = true;
		}

	}
}

void BallScript::OnCollisionExit(const Collision& _collision)
{
}
