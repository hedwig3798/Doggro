#include "ImagineCutScene.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "DrawType.h"

ImagineCutScene::ImagineCutScene(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, CUTSCENETYPE _cutsceneType)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
	DrawUIType(_cutsceneType);
}
ImagineCutScene::~ImagineCutScene()
{

}

void ImagineCutScene::DrawUIType(CUTSCENETYPE _cutsceneType)
{
	switch (_cutsceneType)
	{
	case CUTSCENETYPE::STAGE1:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::IMAGINECUTSCENE1, managerSet->GetGraphics());
		break;
	
	case CUTSCENETYPE::STAGE2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::IMAGINECUTSCENE2, managerSet->GetGraphics());
		break; 
	
	case CUTSCENETYPE::STAGE3:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::IMAGINECUTSCENE3, managerSet->GetGraphics());
		break;
	}
}
