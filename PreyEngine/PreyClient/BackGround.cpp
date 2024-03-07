#include "BackGround.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "DrawType.h"

BackGround::BackGround(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, BACKGROUNDTYPE _backType)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;

	//기본 설정 해주기
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

	DrawBackgroundType(_backType);
}

BackGround::~BackGround()
{

}

void BackGround::DrawBackgroundType(BACKGROUNDTYPE _uiType)
{
	switch (_uiType)
	{
	case BACKGROUNDTYPE::FLOOR1:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::FLOOR1, managerSet->GetGraphics());
		break;

	case BACKGROUNDTYPE::WALL1:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::WALL1, managerSet->GetGraphics());
		break;

	default:
		break;
	}
}
