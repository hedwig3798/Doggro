#include "Cup.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"
#include "LoadMapData.h"
#include "AObject.h"
#include "BoxCollider.h"
#include "CupScript.h"
#include "DogScript.h"

Cup::Cup(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager, QuestManager* _questManager, DogScript* _dogScript)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	objectManager = _objectManager;
	questManager = _questManager;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	ABoundingBox aBoundingBox;

	///자신에게 맞는 오브젝트 찾기
	for (auto i : objectManager->mapObjects)
	{
		std::string _nowName = i->GetName();

		if (_nowName == _name)
		{
			aObject = i;
			position.x = i->position[0];
			position.y = i->position[1];
			position.z = i->position[2];

			rotation.x = i->rotation[1];
			rotation.y = i->rotation[0];
			rotation.z = i->rotation[2];

			scale.x = i->scale[0];
			scale.y = i->scale[1];
			scale.z = i->scale[2];

			aBoundingBox = i->GetBoundingBox();
		}

	}

	Vector3 cPosition(aBoundingBox.cx+10, aBoundingBox.cy+30, aBoundingBox.cz);
	Vector3 cscale(aBoundingBox.xLen * 100, aBoundingBox.yLen * 100, aBoundingBox.zLen * 100);

	//기본 설정 해주기
	CreateComponent2<BoxCollider>(this, managerSet->GetCollisionManager());
	CreateComponent<DrawType>(this);

	GetComponent<Transform>()->SetPosition(cPosition);
	GetComponent<Transform>()->SetRotation(GetComponent<Transform>()->Vector3ToQuaternion(rotation));
	GetComponent<Transform>()->SetScale(scale);

	CreateComponent<CupScript>(this);
	GetComponent<CupScript>()->GetQuestManager(questManager);

	GetComponent<BoxCollider>()->SetSize(cscale);
	GetComponent<BoxCollider>()->Start();

	dogScript = _dogScript;


	///DrawType에 알맞은 AObject보내두기
	GetComponent<DrawType>()->SetAObject(aObject);
}

Cup::~Cup()
{
}

void Cup::Update(float _deltaTime)
{
	if (dogScript->GetIsDetach() && this->GetName() == dogScript->GetAttachName())
	{
		std::vector<float> dogPosition = dogScript->GetDogPosition();
		Vector3 dogSetPositon = { dogPosition[0], dogPosition[1], dogPosition[2] };
		this->GetComponent<Transform>()->SetPosition(dogSetPositon);
		dogScript->SetIsDetach(false);
	}
	Entity::Update(_deltaTime);
}
