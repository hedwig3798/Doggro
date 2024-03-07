#include "CupScript.h"

#include "Entity.h"
#include "Collider.h"

#include "Cup.h"

#include"QuestManager.h"

CupScript::CupScript(Entity* _entity)
	: Component(_entity, "CupScript")
{
}

CupScript::~CupScript()
{
}

void CupScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage1 Quest3 컵 바닥에 떨구기 
	//바닥과의 충돌을 확인. 충돌되는 순간 퀘스트가 실행될 수 있음을 나타내자.
	if (name == "floor")
	{
		questManager->isQuest3Start = true;
	}

	
}

void CupScript::OnCollisionExit(const Collision& _collision)
{
}
