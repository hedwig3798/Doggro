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

	//stage3 Quest2 침대에 올려놓기
	//침대와 충돌 시, 없애버리자.

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
