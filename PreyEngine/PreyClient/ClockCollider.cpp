#include "ClockCollider.h"

#include "BoxCollider.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"
#include "LoadMapData.h"
#include "AObject.h"

ClockCollider::ClockCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager)
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

		if (_nowName == "clock")
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

	GetComponent<Transform>()->SetPosition(Vector3(-73.f, 148.9907f, 227.f));
	GetComponent<Transform>()->SetRotation(GetComponent<Transform>()->Vector3ToQuaternion(rotation));
	GetComponent<Transform>()->SetScale(scale);

	CreateComponent2<BoxCollider>(this, managerSet->GetCollisionManager());
	GetComponent<BoxCollider>()->SetSize(Vector3(15.866f, 12.281f, 17.773f));
	GetComponent<BoxCollider>()->Start();
}

ClockCollider::~ClockCollider()
{

}
