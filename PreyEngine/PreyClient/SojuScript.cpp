#include "SojuScript.h"
#include "Collider.h"

#include "Entity.h"

#include"QuestManager.h"
#include "DrawType.h"

SojuScript::SojuScript(Entity* _entity)
	: Component(_entity, "SojuScript")
{

}

SojuScript::~SojuScript()
{

}

void SojuScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage2 Final quest 소파에 숨기기
	//침대와 충돌 시, 없애버리자.
	if (name == "sofa")
	{
		if (questManager->stageNumber == 2)
		{
			entity->GetComponent<DrawType>()->SetAObjectVisible(false);
			questManager->isSojiHiding++;
		}

	}
}

void SojuScript::OnCollisionExit(const Collision& _collision)
{

}
