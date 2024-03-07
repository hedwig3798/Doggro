#include "DogScript.h"

#include "Entity.h"
#include "Collider.h"

#include "Dog.h"

#include "AObject.h"
#include "QuestManager.h"
#include "LoadMapData.h"

#include "ManagerSet.h"
#include "CollsionManager.h"
#include "Transform.h"
#include "DogSightScript.h"
#include "SceneManager.h"
#include "Scene.h"
#include "AudioManager.h"

#include "Chewbone.h"


DogScript::DogScript(Entity* _entity)
	: Component(_entity, "DogScript")
	, isHolding(false)
{
	dogPosition.resize(3);
}


DogScript::~DogScript()
{
}

void DogScript::Update(float _deltaTime)
{

}

void DogScript::Render()
{
}

void DogScript::OnCollisionEnter(const Collision& _collision)
{
	Transform* transform = entity->GetComponent<Transform>();
	
	Vector3 position = transform->GetPosition();

	std::string name = _collision.otherCollider->GetEntity()->GetName();
	std::string sightName = dogSight->GetComponent<DogSightScript>()->setName();
	std::string pickingname = entity->GetManagerset()->GetCollisionManager()->GetRayColliderName();
	OutputDebugString(TEXT("Picking Name: ")); 
	OutputDebugString(std::wstring(pickingname.begin(), pickingname.end()).c_str());

	if (name != "floor")
	{
		isCollision = true;
	}

	//stage1 Quest1 clock�� ¢�� 
	//�ϴ��� �ð�÷��� �ſ� �ε���ü�� ¢�� ��� ����Ʈ �Ϸ�� ����
	if (sightName == "shelf_bedroom2" || name == "shelf_bedroom2")
	{
		if (questManager->stageNumber == 1)
			questManager->isQuest1Start = true;
	}
	
	//stage1 Quest2 å�� �ö󰡱�
	//å���� ������ ����� �ϴ� ħ�뿡 �ö󰡱�� ������.
	if (name == "deskCollider")
	{
		if(questManager->stageNumber == 1)
			questManager->isQuest2Start = true;
	}

	//stage1 finalQuest ���� ��ƴ���
	//������ �ʹ� ���� ����� closet�̶� �浹�� ���� ����.
	if (name == "closetCollider" || sightName == "closetCollider")
	{
		if(questManager->stageNumber == 1)
			questManager->isFinalQuestStart = true;
	}

	//stage2 Quest1 å�� ��׸� �÷��α�
	if (sightName == "tableCollider")
	{
		if (questManager->stageNumber == 2)
			questManager->isQuest1Start = true;
	}
	
	//stage2 Quest2 ���� �Ź��忡 �α�
	if (sightName == "shoe_rack")
	{
		if (questManager->stageNumber == 2)
			questManager->isQuest2Start = true;
	}

	//stage2 Quest3 �Ź� �����ñ�
	if (sightName == "shoes_L" || sightName == "shoes_R")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isQuest3Start = true;
		}
	}
		
	//stage2 Quest4 ���� ¢��
	if (sightName == "door")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isQuest4Start = true;
		}
	}

	if (name == "door")
	{
	//	if (questManager->stageNumber == 4)
			//questManager->isManArrive = true;
	}
		
	
	//stage3 Quest1 ħ�� ���� �ñ�
	//stage1 Quest4 ħ�뿡 �÷�����
	if (name == "bedCollider")
	{
		if (questManager->stageNumber == 1)
			questManager->isQuest4Start = true;

		if(questManager->stageNumber == 3)
			questManager->isQuest1Start = true;
	}
	
	//stage3 Quest3 �ʿ��� ���� �ñ�
	//stage3 FinalQuest �ʿ��� �ڱ�
	if (name == "clothes")
	{
		if (questManager->stageNumber == 3)
		{
			questManager->isQuest3Start = true;
			questManager->isFinalQuestStart = true;
		}
	}
		
	//stage4 Quest1 ��� �ǻ츮��
	if (sightName == "paperpile")
	{
		if (questManager->stageNumber == 4)
			questManager->isQuest1Start = true;
	}

	// Attach�� �����ô�.
	// Ư�� ��ü�� �ε����ְ�, isBite? �� true�� ���, attach�� �۵��ؾ� ��.
	// isBite�� FSM���� �޾ƿ� �� �ְ���? 
	// ������ ������� �ʾ�����. �׷����� �ұ��ϰ� �츮���� QuestSystem�̶�� �߰��ٸ��� �ֽ��ϴ�.
	// �Ǵ� ������ ��ü�� ������ �����δ°͵� ���b �ϰٱ���!
	// ������ �̹� QuestSystem���� ���¸� ������Ʈ �ϴ� �Լ��� �ձ� ������ �̰� �̿��ϰٽ��ϴ�.
	
	if (isHolding)
	{
		// �ٷ� ���� ���´�.
		if (!questManager->isBiting && !questManager->isHoldBiting)
		{
			myMesh->Detach(attachMesh);

			// �̸� ������ �ش� �̸��� �ش��ϴ� Object�� ��ġ�� �̵� ���Ѿ� �Ѵ�.
			std::string _name = attachMesh->GetName();
			attachMesh->position;
			dogPosition[0] = attachMesh->finalPos[0];
			dogPosition[1] = attachMesh->finalPos[1];
			dogPosition[2] = attachMesh->finalPos[2];
			
			isAttach = false;
			isDetach = true;
			isHolding = false;
		}
	}


	///Attach
	//�ٴ��̶��� ��� �ε����� �ִ�. �ٴڰ� �ε������� �ƴ� ��, Ȯ���� �ؾߵȴ�.
	if (sightName != "floor" )
	{
		// ħ�븦 �������� �ȵǴϱ� ���ǹ����� �صӽô�.
		// stage1 : ball, bigball, clock, cup, doll, chewbone
		// stage2 : shoes_L, shoes_R, slippers, soju, leash, doll, boll, bigball, 
		// stage3 : ball, doll, chewbone, cup
		// stage4 : shoes_L, shoes_R, slippers, soju
		if ((name == "ball" ||
			name == "bigball" ||
			name == "clock" ||
			name == "cup" ||
			name == "doll" ||
			name == "chewbone" ||
			name == "shoes_L" ||
			name == "shoes_R" ||
			name == "slippers" ||
			name == "01_soju" ||
			name == "02_soju" ||
			name == "03_soju" ||
			name == "leash" ||
			name == "bowl" ||
			name == "calendar_letter") && !isAttach)
		{
			// ���� 1. �������� ���� ������ ��
			if (questManager->isBiting == true || questManager->isHoldBiting == true)
			{
				AObject* _nowObject = nullptr;

				//���� �ε��� ��ü�� �̸��� ���� AObject�� ã�Ƶд�.
				for (auto i : this->objectManager->mapObjects)
				{
					std::string _nowName = i->GetName();
					if (_nowName == name)
					{
						attachName = _nowName;
						_nowObject = i;
						break;
					}
				}

				//���� ����ġ!
				if (_nowObject != nullptr)
				{		
					AudioManager::GetInstance()->StopAllEffect();
					AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Pick_Up);
					
					this->myMesh->Attach(_nowObject, "c_skull_03.x");
					isHolding = true;
					isAttach = true;
					isDetach = false;
					attachMesh = _nowObject;

					//stage2 Quest5 �޷� ���
					if (name == "calendar_letter")
					{
						questManager->isQuest5Start = true;
						questManager->isCalenderPutting = true;
					}
						
				}				
			}
		}
	}
}


void DogScript::OnCollisionExit(const Collision& _collision)
{
	std::string name = _collision.otherCollider->GetEntity()->GetName();
	std::string sightName = dogSight->GetComponent<DogSightScript>()->setName();
	
	if (name != "floor" && name != "background_window" && name != "stage1_background_wall")
	{
		isCollision = false;
	}


	//stage1 Quest1 clock�� ¢�� 
	//�� �̻� �浹 ���°� �ƴ� ���, ����Ʈ�� ����Ǹ� �ȵȴ�.
	if (sightName == "shelf_bedroom")
	{
		if(questManager->stageNumber == 1)
			questManager->isQuest1Start = false;
	}
	

	if (name == "bedCollider")
	{
		if (questManager->stageNumber == 1)
			questManager->isQuest4Start = false;

		if (questManager->stageNumber == 3)
			questManager->isQuest1Start = false;
	}

	//stage1 Quest2 å�� �ö󰡱�
	if (name == "deskCollider")
	{
		if(questManager->stageNumber == 1)
			questManager->isQuest2Start = false;
	}

	//stage2 Quest1 å�� ��׸� �÷��α�
	if (sightName == "tableCollider")
	{
		if (questManager->stageNumber == 2)
			questManager->isQuest1Start = false;
	}

	//stage2 Quest3 �Ź� �����ñ�
	if (sightName == "shoes_L" || sightName == "shoes_R")
	{
		if(questManager->stageNumber == 2)
			questManager->isQuest3Start = false;
	}
		
	//stage2 Quest4 ���� ¢��
	if (sightName == "door")
	{
		if(questManager->stageNumber == 2)
			questManager->isQuest4Start = false;
	}
		
	//stage3 Quest3 �ʿ��� ���� �ñ�
	//stage3 FinalQuest �ʿ��� �ڱ�
	if (name == "clothes")
	{
		if (questManager->stageNumber == 3)
		{
			questManager->isQuest3Start = false;
			questManager->isFinalQuestStart = false;
		}
	}

	//stage4 Quest1 ��� �ǻ츮��
	if (sightName == "paperpile")
	{
		if (questManager->stageNumber == 4)
			questManager->isQuest1Start = false;
	}


}


