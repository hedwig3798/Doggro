#include "Human.h"
#include "ManagerSet.h"
#include "CollsionManager.h"
#include "Animation.h"
#include "FilterCollider.h"
#include "LoadMapData.h"
#include "SimpleMath.h"
#include "AObject.h"
#include "Transform.h"
#include "HumanScript.h"

Human::Human(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	questManager = _questManager;

	CreateComponent2<FilterCollider>(this, _managerSet->GetCollisionManager());
	GetComponent<Transform>()->SetPosition(Vector3(205.f, 40.f, -390.f));
	GetComponent<Transform>()->SetRotation(Quaternion(0.0f, 0.70f, 0.0f, 0.70f));
	CreateComponent<Animation>(this);
	GetComponent<Animation>()->GetQuestManager(_questManager);
	GetComponent<Animation>()->SelectAnimationType(SelectAnimation::Human);
	GetComponent<FilterCollider>()->SetSize(Vector3(150.f, 150.f, 150.f));
	GetComponent<FilterCollider>()->Start();
	 
	CreateComponent<HumanScript>(this);
	GetComponent<HumanScript>()->GetQuestManager(questManager);

}

Human::~Human()
{

}

void Human::Update(float _deltaTime)
{
	Entity::Update(_deltaTime);
}
