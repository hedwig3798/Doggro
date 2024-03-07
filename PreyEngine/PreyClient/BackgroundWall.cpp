#include "BackgroundWall.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"
#include "LoadMapData.h"
#include "AObject.h"

BackgroundWall::BackgroundWall(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	objectManager = _objectManager;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

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
		}
	}

	//기본 설정 해주기
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(position);
	GetComponent<Transform>()->SetRotation(GetComponent<Transform>()->Vector3ToQuaternion(rotation));
	GetComponent<Transform>()->SetScale(scale);

	///DrawType에 알맞은 AObject보내두기
	GetComponent<DrawType>()->SetAObject(aObject);
}

BackgroundWall::~BackgroundWall()
{
}
