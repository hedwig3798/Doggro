#include "DollCollider.h"

#include "BoxCollider.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"
#include "LoadMapData.h"
#include "AObject.h"

//DollCollider::DollCollider(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, LoadMapData* _objectManager)
//	:Entity(_name, _managerSet, _type)
//{
//	managerSet = _managerSet;
//	objectManager = _objectManager;
//
//	Vector3 position;
//	Vector3 rotation;
//	Vector3 scale;
//
//	///�ڽſ��� �´� ������Ʈ ã��
//	for (auto i : objectManager->mapObjects)
//	{
//		std::string _nowName = i->GetName();
//
//		if (_nowName == "doll")
//		{
//			aObject = i;
//			position.x = i->position[0];
//			position.y = i->position[1];
//			position.z = i->position[2];
//
//			rotation.x = i->rotation[1];
//			rotation.y = i->rotation[0];
//			rotation.z = i->rotation[2];
//
//			scale.x = i->scale[0];
//			scale.y = i->scale[1];
//			scale.z = i->scale[2];
//		}
//
//	}
//
//	GetComponent<Transform>()->SetPosition(Vector3(200.f, 13.f, -12.f));
//	GetComponent<Transform>()->SetRotation(GetComponent<Transform>()->Vector3ToQuaternion(rotation));
//	GetComponent<Transform>()->SetScale(scale);
//
//	CreateComponent2<BoxCollider>(this, managerSet->GetCollisionManager());
//	GetComponent<BoxCollider>()->SetSize(Vector3(20.f, 20.281f, 32.f));
//	GetComponent<BoxCollider>()->Start();
//}
//
//DollCollider::~DollCollider()
//{
//
//}
