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

	//stage1 Quest1 clock에 짖기 
	//일단은 시계올려둔 거에 부딛힌체로 짖을 경우 퀘스트 완료로 하자
	if (sightName == "shelf_bedroom2" || name == "shelf_bedroom2")
	{
		if (questManager->stageNumber == 1)
			questManager->isQuest1Start = true;
	}
	
	//stage1 Quest2 책상에 올라가기
	//책상이 먹통인 관계로 일단 침대에 올라가기로 만들자.
	if (name == "deskCollider")
	{
		if(questManager->stageNumber == 1)
			questManager->isQuest2Start = true;
	}

	//stage1 finalQuest 로프 잡아당기기
	//로프는 너무 작은 관계로 closet이랑 충돌일 경우로 하자.
	if (name == "closetCollider" || sightName == "closetCollider")
	{
		if(questManager->stageNumber == 1)
			questManager->isFinalQuestStart = true;
	}

	//stage2 Quest1 책상에 밥그릇 올려두기
	if (sightName == "tableCollider")
	{
		if (questManager->stageNumber == 2)
			questManager->isQuest1Start = true;
	}
	
	//stage2 Quest2 목줄 신발장에 두기
	if (sightName == "shoe_rack")
	{
		if (questManager->stageNumber == 2)
			questManager->isQuest2Start = true;
	}

	//stage2 Quest3 신발 냄새맡기
	if (sightName == "shoes_L" || sightName == "shoes_R")
	{
		if (questManager->stageNumber == 2)
		{
			questManager->isQuest3Start = true;
		}
	}
		
	//stage2 Quest4 문에 짖기
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
		
	
	//stage3 Quest1 침대 냄새 맡기
	//stage1 Quest4 침대에 올려놓기
	if (name == "bedCollider")
	{
		if (questManager->stageNumber == 1)
			questManager->isQuest4Start = true;

		if(questManager->stageNumber == 3)
			questManager->isQuest1Start = true;
	}
	
	//stage3 Quest3 옷에서 냄새 맡기
	//stage3 FinalQuest 옷에서 자기
	if (name == "clothes")
	{
		if (questManager->stageNumber == 3)
		{
			questManager->isQuest3Start = true;
			questManager->isFinalQuestStart = true;
		}
	}
		
	//stage4 Quest1 약속 되살리기
	if (sightName == "paperpile")
	{
		if (questManager->stageNumber == 4)
			questManager->isQuest1Start = true;
	}

	// Attach를 만들어봅시다.
	// 특정 물체와 부딛혀있고, isBite? 가 true일 경우, attach가 작동해야 함.
	// isBite는 FSM에서 받아올 수 있겟죠? 
	// 하지만 열어두지 않았음요. 그럼에도 불구하고 우리에겐 QuestSystem이라는 중간다리가 있습니다.
	// 또는 강아지 자체에 변수를 만들어두는것도 낫밷 하겟군요!
	// 하지만 이미 QuestSystem에서 상태를 업데이트 하는 함수가 잇기 때문에 이걸 이용하겟습니다.
	
	if (isHolding)
	{
		// 바로 내려 놓는다.
		if (!questManager->isBiting && !questManager->isHoldBiting)
		{
			myMesh->Detach(attachMesh);

			// 이름 가지고 해당 이름에 해당하는 Object의 위치를 이동 시켜야 한다.
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
	//바닥이랑은 계속 부딪히고 있다. 바닥과 부딛힌것이 아닐 때, 확인을 해야된다.
	if (sightName != "floor" )
	{
		// 침대를 들어버리면 안되니까 조건문으로 해둡시다.
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
			// 조건 1. 강아지가 물기 상태일 때
			if (questManager->isBiting == true || questManager->isHoldBiting == true)
			{
				AObject* _nowObject = nullptr;

				//먼저 부딪힌 물체의 이름을 통해 AObject를 찾아둔다.
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

				//이후 어테치!
				if (_nowObject != nullptr)
				{		
					AudioManager::GetInstance()->StopAllEffect();
					AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Pick_Up);
					
					this->myMesh->Attach(_nowObject, "c_skull_03.x");
					isHolding = true;
					isAttach = true;
					isDetach = false;
					attachMesh = _nowObject;

					//stage2 Quest5 달력 뜯기
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


	//stage1 Quest1 clock에 짖기 
	//더 이상 충돌 상태가 아닐 경우, 퀘스트는 진행되면 안된다.
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

	//stage1 Quest2 책상에 올라가기
	if (name == "deskCollider")
	{
		if(questManager->stageNumber == 1)
			questManager->isQuest2Start = false;
	}

	//stage2 Quest1 책상에 밥그릇 올려두기
	if (sightName == "tableCollider")
	{
		if (questManager->stageNumber == 2)
			questManager->isQuest1Start = false;
	}

	//stage2 Quest3 신발 냄새맡기
	if (sightName == "shoes_L" || sightName == "shoes_R")
	{
		if(questManager->stageNumber == 2)
			questManager->isQuest3Start = false;
	}
		
	//stage2 Quest4 문에 짖기
	if (sightName == "door")
	{
		if(questManager->stageNumber == 2)
			questManager->isQuest4Start = false;
	}
		
	//stage3 Quest3 옷에서 냄새 맡기
	//stage3 FinalQuest 옷에서 자기
	if (name == "clothes")
	{
		if (questManager->stageNumber == 3)
		{
			questManager->isQuest3Start = false;
			questManager->isFinalQuestStart = false;
		}
	}

	//stage4 Quest1 약속 되살리기
	if (sightName == "paperpile")
	{
		if (questManager->stageNumber == 4)
			questManager->isQuest1Start = false;
	}


}


