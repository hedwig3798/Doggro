#include "ChewBoneScript.h"

#include "Entity.h"
#include "Collider.h"
#include "DrawType.h"

#include "Chewbone.h"

#include"QuestManager.h"

ChewBoneScript::ChewBoneScript(Entity* _entity)
	: Component(_entity, "ChewBoneScript")
{
}

ChewBoneScript::~ChewBoneScript()
{
}

void ChewBoneScript::OnCollisionEnter(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();

	//stage1 Quest3 �� �ٴڿ� ������ 
	//�ٴڰ��� �浹�� Ȯ��. �浹�Ǵ� ���� ����Ʈ�� ����� �� ������ ��Ÿ����.
	if (name == "floor")
	{
		questManager->isQuest4Start = true;
	}

	if (name == "bedCollider")
	{
		if (questManager->stageNumber == 1)
			questManager->isChewbonePutting = true;

		if (questManager->stageNumber == 3)
		{
			entity->GetComponent<DrawType>()->SetAObjectVisible(false);
			questManager->isChewboneHiding = true;
		}
	}
}

void ChewBoneScript::OnCollisionExit(const Collision& _collision)
{
}
