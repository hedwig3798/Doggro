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

	//stage1 Quest3 �� �ٴڿ� ������ 
	//�ٴڰ��� �浹�� Ȯ��. �浹�Ǵ� ���� ����Ʈ�� ����� �� ������ ��Ÿ����.
	if (name == "floor")
	{
		questManager->isQuest3Start = true;
	}

	
}

void CupScript::OnCollisionExit(const Collision& _collision)
{
}
