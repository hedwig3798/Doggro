#include "Dog.h"
#include "DogFSM.h"
#include "DogScript.h"
#include "DrawType.h"
#include "Animation.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "QuestManager.h"
#include "BoxCollider.h"
#include "AObject.h"
#include "DogSight.h"
#include "CameraModule.h"
#include "IGraphicsEngine.h"

Dog::Dog(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, DogType _dogType, LoadMapData* _loadMapData, QuestManager* _questManager, Entity* _dogSight, Entity* _dogImagine)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	questManager = _questManager;
	loadMapData = _loadMapData;
	dogSight = _dogSight;
	imagineCutScene = _dogImagine;

	CreateComponent2<BoxCollider>(this, managerSet->GetCollisionManager());
	CreateComponent<DogFSM>(this);
	GetComponent<DogFSM>()->GetQuestManager(questManager);
	GetComponent<DogFSM>()->GetDogSight(dogSight);   
	CreateComponent<Animation>(this);
	GetComponent<Animation>()->GetQuestManager(questManager);
	CreateComponent<DogScript>(this);
	GetComponent<DogScript>()->GetQuestManager(questManager);
	GetComponent<DogScript>()->GetObjectManager(loadMapData);
	GetComponent<DogScript>()->GetDogSight(dogSight);
	CreateComponent<CameraModule>(this);

	switch (_dogType)
	{
	case DogType::Stage1:
	{
		GetComponent<Animation>()->SelectAnimationType(SelectAnimation::Child);
		GetComponent<Transform>()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		GetComponent<BoxCollider>()->SetSize(Vector3(20.f, 20.f, 20.f));
		GetComponent<Transform>()->SetPosition(Vector3(-239.0f, 65.0f, -103.0f));
	}
		break;
	case DogType::Stage2:
	{
		GetComponent<Animation>()->SelectAnimationType(SelectAnimation::Adult);
		GetComponent<BoxCollider>()->SetSize(Vector3(50.f, 50.f, 50.f));
		GetComponent<Transform>()->SetPosition(Vector3(-322.0f, 39.0f, -299.7f));
	}
		break;
	case DogType::Stage3:
	{
		GetComponent<Animation>()->SelectAnimationType(SelectAnimation::Adult);
		GetComponent<BoxCollider>()->SetSize(Vector3(50.f, 50.f, 50.f));
		GetComponent<Transform>()->SetPosition(Vector3(-239.0f, 65.0f, -103.0f));
	}
		break;	
	case DogType::Stage4:
	{
		GetComponent<Animation>()->SelectAnimationType(SelectAnimation::Ghost);
		GetComponent<BoxCollider>()->SetSize(Vector3(50.f, 50.f, 50.f));
		//GetComponent<Transform>()->SetPosition(Vector3(-56.0f, 40.0f, 10.0f));
		GetComponent<Transform>()->SetPosition(Vector3(-0.0f, 25.0f, 0.0f));
	}
		break;
	default:
		break;
	}
	
	// 하드 코딩해야 할 수도 있다.
	GetComponent<BoxCollider>()->Start();
	GetComponent<CameraModule>()->GetMainCamera();
	
	//일단은 animation에서 만들고 있는 aobject를 가지고 왓다.
	//어디꺼를 가져와야될지는 나중에 한번 고민을 해보자.
	myMesh = GetComponent<Animation>()->GetAObject();
	GetComponent<DogScript>()->GetAObject(myMesh);

	imagineCutScene->GetComponent<DrawType>()->GetDog(myMesh);
}

Dog::~Dog()
{

}

void Dog::GetHuman(Entity* _human)
{
	human = _human; 
	GetComponent<DogFSM>()->GetHuman(human);
}
