#include "GetSoul.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "DrawType.h"
#include "UObject.h"

GetSoul::GetSoul(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type)
	:Entity(_name, _managerSet, _type)
	, heightTop(1232)
{
	managerSet = _managerSet;
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));

	topInventory = new UObject;
}

GetSoul::~GetSoul()
{
	
}

void GetSoul::QuestClear(float _heightTop)
{
	std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Top.png";
	topInventory->Initalize(this->GetManagerset()->GetGraphics(), "Top", upath, texturePath, 201, heightTop, 1518, 152);

	heightTop = _heightTop;

	if (topInventory != nullptr)
		GetComponent<DrawType>()->SetUObject(topInventory);
}

