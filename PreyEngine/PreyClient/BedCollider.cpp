#include "BedCollider.h"

#include "StaticCollider.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"
#include "LoadMapData.h"
#include "AObject.h"

BedCollider::BedCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	objectManager = _objectManager;

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	///�ڽſ��� �´� ������Ʈ ã��
	for (auto i : objectManager->mapObjects)
	{
		std::string _nowName = i->GetName();

		if (_nowName == "bed")
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

	GetComponent<Transform>()->SetPosition(Vector3(-220.f, 45.9907f, 172.f));
	GetComponent<Transform>()->SetRotation(GetComponent<Transform>()->Vector3ToQuaternion(rotation));
	GetComponent<Transform>()->SetScale(scale);

	CreateComponent2<StaticCollider>(this, managerSet->GetCollisionManager());
	GetComponent<StaticCollider>()->SetSize(Vector3(162.866f, 260.281f, 80.773f));
	GetComponent<StaticCollider>()->Start();
}

BedCollider::~BedCollider()
{

}
