#include "Calendar.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"
#include "LoadMapData.h"
#include "StaticCollider.h"
#include "AObject.h"

Calendar::Calendar(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	objectManager = _objectManager;

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

	Vector3 cPosition(aBoundingBox.cx, aBoundingBox.cy, aBoundingBox.cz);
	Vector3 cscale(aBoundingBox.xLen * 100, aBoundingBox.yLen * 100, aBoundingBox.zLen * 100);

	//기본 설정 해주기
	CreateComponent2<StaticCollider>(this, managerSet->GetCollisionManager());
	CreateComponent<DrawType>(this);

	GetComponent<Transform>()->SetPosition(cPosition);
	GetComponent<Transform>()->SetRotation(GetComponent<Transform>()->Vector3ToQuaternion(rotation));
	GetComponent<Transform>()->SetScale(scale);

	GetComponent<StaticCollider>()->SetSize(cscale);
	GetComponent<StaticCollider>()->Start();



	///DrawType에 알맞은 AObject보내두기
	GetComponent<DrawType>()->SetAObject(aObject);
}

Calendar::~Calendar()
{

}
