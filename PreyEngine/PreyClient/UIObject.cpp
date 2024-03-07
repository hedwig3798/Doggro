#include "UIObject.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "DrawType.h"

UIObject::UIObject(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type, UITYPE _uiType)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(10.0f, 30.0f, 0.0f));
	DrawUIType(_uiType);
	
}

UIObject::~UIObject()
{

}

void UIObject::DrawUIType(UITYPE _uiType)
{
	switch (_uiType)
	{
	case UITYPE::TITLE:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::TITLE, managerSet->GetGraphics());
		break;
	case UITYPE::TITLECONTRACT:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::TITLECONTRACT, managerSet->GetGraphics());
		break;
	case UITYPE::EXIT_BUTTON:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::EXIT_BUTTON, managerSet->GetGraphics());
		break;
	case UITYPE::EXIT_BUTTON2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::EXIT_BUTTON2, managerSet->GetGraphics());
		break;
	case UITYPE::CREDITBUTTON:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CREDITBUTTON, managerSet->GetGraphics());
		break;
	case UITYPE::CREDITBUTTON2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CREDITBUTTON2, managerSet->GetGraphics());
		break;
	case UITYPE::SETTING:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::SETTING, managerSet->GetGraphics());
		break;
	case UITYPE::SETTING2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::SETTING2, managerSet->GetGraphics());
		break;
	case UITYPE::KEYGUIDE:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::KEYGUIDE, managerSet->GetGraphics());
		break;
	case UITYPE::KEYGUIDE2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::KEYGUIDE2, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPER:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPER, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPER2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPER2, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPER3:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPER3, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPER4:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPER4, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPERPIECE1:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPERPIECE1, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPERPIECE2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPERPIECE2, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPERPIECE3:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPERPIECE3, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPERPIECE4_1:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPERPIECE4_1, managerSet->GetGraphics());
		break;
	case UITYPE::MISSIONPAPERPIECE4_2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MISSIONPAPERPIECE4_2, managerSet->GetGraphics());
		break;
	case UITYPE::CHECK1:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CHECK1, managerSet->GetGraphics());
		break;
	case UITYPE::CHECK2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CHECK2, managerSet->GetGraphics());
		break;
	case UITYPE::CHECK3:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CHECK3, managerSet->GetGraphics());
		break;
	case UITYPE::CHECK4:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CHECK4, managerSet->GetGraphics());
		break;
	case UITYPE::CHECK5:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CHECK5, managerSet->GetGraphics());
		break;
	case UITYPE::CHECK6:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CHECK6, managerSet->GetGraphics());
		break;

	case UITYPE::MENUBOARD:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUBOARD, managerSet->GetGraphics());
		break;
	case UITYPE::MENUGUIDEBOARD:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUGUIDEBOARD, managerSet->GetGraphics());
		break;
	case UITYPE::MENUGUIDE:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUGUIDE, managerSet->GetGraphics());
		break;
	case UITYPE::MENUGUIDE2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUGUIDE2, managerSet->GetGraphics());
		break;
	case UITYPE::CLOSE:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CLOSE, managerSet->GetGraphics());
		break;
	case UITYPE::CLOSE2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CLOSE2, managerSet->GetGraphics());
		break;
	case UITYPE::MENUALBUM:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUALBUM, managerSet->GetGraphics());
		break;
	case UITYPE::MENUALBUM2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUALBUM2, managerSet->GetGraphics());
		break;
	case UITYPE::MENUGAMEEXIT:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUGAMEEXIT, managerSet->GetGraphics());
		break;
	case UITYPE::MENUGAMEEXIT2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::MENUGAMEEXIT2, managerSet->GetGraphics());
		break;
	case UITYPE::TITLESTART:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::TITLESTART, managerSet->GetGraphics());
	break; 
	case UITYPE::TITLESTART2:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::TITLESTART2, managerSet->GetGraphics());
	break;
	case UITYPE::STAMP:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::STAMP, managerSet->GetGraphics());
	break;
	case UITYPE::CREDIT:
		GetComponent<DrawType>()->CreateRenderType(DRAW_TYPE::CREDIT, managerSet->GetGraphics());
		break;
	default:
		break;
	}
}
