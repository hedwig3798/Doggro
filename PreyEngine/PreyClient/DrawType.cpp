#include "DrawType.h"
#include "Entity.h"
#include "AObject.h"
#include "UObject.h"
#include "Transform.h"
#include "SimpleMath.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "PreyGameEngine.h"
#include "LoadMapData.h"



DrawType::DrawType(Entity* _entity)
	: Component(_entity, "DrawType")
	, isUIVisible(true)
	, isAObjectVisible(true)
	, contractUp(0)
{
	// 여기서 Aobject를 생성한다.
	//window크기를 받아온당

	windowHeight = _entity->GetManagerset()->GetPreyGame()->GetScreenHeight();
	windowWidth = _entity->GetManagerset()->GetPreyGame()->GetScreenWidth();
}

DrawType::~DrawType()
{

}

void DrawType::CreateRenderType(DRAW_TYPE _drawType, IGraphicsEngine* _renderer)
{
	// Render Type에 따라 적용된다. mk-1
	switch (_drawType)
	{
	case DRAW_TYPE::TESTBOX:
	{
		aObjectRender = new AObject("adult_dog.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
	}
	break;
	case DRAW_TYPE::TESTGUN:
	{

	}
	break;
	case DRAW_TYPE::TESTDOG:
	{
		aObjectRender = new AObject("adult_dog.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
	}
	break;
	///UI
	case DRAW_TYPE::TITLE:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\title.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "title", upath, texturePath, 0, 1080, 1920, 1080);
	}
	break;
	case DRAW_TYPE::TITLESTART:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\start_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "start", upath, texturePath, 970, 150, 301, 132);
	}
	break;
	case DRAW_TYPE::TITLESTART2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\start_button_3.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "start2", upath, texturePath, 970, 150, 301, 132);
	}
	break;
	case DRAW_TYPE::STAMP:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\stamp.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "stamp", upath, texturePath, 970, 150, 177, 164);
	}
	break;
	case DRAW_TYPE::TITLECONTRACT:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\contract.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "contract", upath, texturePath, 340, 590, 1310, 600);
	}
	break;
	case DRAW_TYPE::CREDITBUTTON:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\credit_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "credit", upath, texturePath, 10, 1080, 132, 126);
	}
	break;
	case DRAW_TYPE::CREDITBUTTON2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\credit_button_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "credit2", upath, texturePath, 10, 1080, 132, 126);
	}
	break;
	case DRAW_TYPE::EXIT_BUTTON:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Exit_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "exit", upath, texturePath, 1785, 1080, 132, 126);
	}
	break;
	case DRAW_TYPE::EXIT_BUTTON2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Exit_button_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "exit2", upath, texturePath, 1785, 1080, 132, 126);
	}
	break;
	case DRAW_TYPE::SETTING:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Settings_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "setting", upath, texturePath, 1785, 1080, 132, 126);
	}
	break;
	case DRAW_TYPE::SETTING2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Settings_button_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "setting2", upath, texturePath, 1785, 1080, 132, 126);
	}
	break;
	case DRAW_TYPE::KEYGUIDE:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_guide_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "keySetting", upath, texturePath, 70, 400, 318, 320);
	}
	break;
	case DRAW_TYPE::KEYGUIDE2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_guide_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "keySetting2", upath, texturePath, 70, 400, 318, 320);
	}
	break;
	case DRAW_TYPE::MISSIONPAPER:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Stage1_Memo.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaper", upath, texturePath, 1500, 500, 375, 444);
	}
	break;
	case DRAW_TYPE::MISSIONPAPER2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Stage2_Memo.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaper2", upath, texturePath, 1500, 500, 375, 444);
	}
	break;
	case DRAW_TYPE::MISSIONPAPER3:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Stage3_Memo.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaper3", upath, texturePath, 1500, 500, 375, 444);
	}
	break;
	case DRAW_TYPE::MISSIONPAPER4:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Stage4_Memo.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaper4", upath, texturePath, 1500, 500, 375, 444);
	}
	break;
	case DRAW_TYPE::MISSIONPAPERPIECE1:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_Piece.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaperPiece1", upath, texturePath, 1530, 225, 324, 35);
	}
	break;
	case DRAW_TYPE::MISSIONPAPERPIECE2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_Piece.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaperPiece2", upath, texturePath, 1530, 180, 324, 35);
	}
	break;
	case DRAW_TYPE::MISSIONPAPERPIECE3:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_Piece.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaperPiece3", upath, texturePath, 1530, 270, 324, 35);
	}
	break;
	case DRAW_TYPE::MISSIONPAPERPIECE4_1:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_Piece.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaperPiece4_1", upath, texturePath, 1530, 360, 324, 35);
	}
	break;
	case DRAW_TYPE::MISSIONPAPERPIECE4_2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_Piece.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "missionPaperPiece4_2", upath, texturePath, 1530, 315, 324, 35);
	}
	break;
	case DRAW_TYPE::CHECK1:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_check.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "check1", upath, texturePath, 1540, 420, 46, 40);
	}
	break;
	case DRAW_TYPE::CHECK2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_check.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "check2", upath, texturePath, 1540, 370, 46, 40);
	}
	break;
	case DRAW_TYPE::CHECK3:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_check.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "check3", upath, texturePath, 1540, 320, 46, 40);
	}
	break;
	case DRAW_TYPE::CHECK4:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_check.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "check4", upath, texturePath, 1540, 280, 46, 40);
	}
	break;
	case DRAW_TYPE::CHECK5:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_check.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "check5", upath, texturePath, 1540, 240, 46, 40);
	}
	break;
	case DRAW_TYPE::CHECK6:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\Memo_check.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "check6", upath, texturePath, 1540, 200, 46, 40);
	}
	break;

	case DRAW_TYPE::MENUGUIDEBOARD:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_guide_3.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuGuideBoard", upath, texturePath, 250, 1000, 1500, 860);
	}
	break;
	case DRAW_TYPE::MENUBOARD:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_menu_board.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuBoard", upath, texturePath, 610, 980, 800, 650);
	}
	break;
	case DRAW_TYPE::CLOSE:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_exit.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "close", upath, texturePath, 1570, 1020, 100, 40);
	}
	break;
	case DRAW_TYPE::CLOSE2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_exit_push.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "close2", upath, texturePath, 1570, 1020, 100, 40);
	}
	break;
	case DRAW_TYPE::MENUALBUM:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_album_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuAlbum", upath, texturePath, 800, 850, 417, 125);
	}
	break;
	case DRAW_TYPE::MENUALBUM2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_album_button_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuAlbum2", upath, texturePath, 780, 870, 442, 162);
	}
	break;
	case DRAW_TYPE::MENUGUIDE:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_guide_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuGuide", upath, texturePath, 800, 700, 417, 125);
	}
	break;
	case DRAW_TYPE::MENUGUIDE2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_guide_button_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuGuide2", upath, texturePath, 780, 720, 442, 162);
	}
	break;
	case DRAW_TYPE::MENUGAMEEXIT:
	{ 
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_game_close_button_1.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuGameExit", upath, texturePath, 800, 550, 417, 125);
	}
	break;
	case DRAW_TYPE::MENUGAMEEXIT2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\UI_game_close_button_2.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "menuGameExit2", upath, texturePath, 780, 570, 442, 162);
	}
	break;
	case DRAW_TYPE::IMAGINECUTSCENE1:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\speechbubble_2_1.png";
		uObjectRender = new UObject();
		//uObjectRender->AnimationInitailze(entity->GetManagerset()->GetGraphics(), "AniimagineCutscene1", texturePath, 0, 500, 461, 348, 461, 2);//uObjectRender->AttachTo()
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "imagineCutscene1", upath, texturePath, 0, 500, 461, 348);

	}
	break;
	case DRAW_TYPE::IMAGINECUTSCENE2:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\speechbubble_1_1.png";
		uObjectRender = new UObject();
		//uObjectRender->AnimationInitailze(entity->GetManagerset()->GetGraphics(), "AniimagineCutscene2", texturePath, 0, 500, 461, 348, 461, 2);
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "imagineCutscene2", upath, texturePath, 0, 500, 461, 348);
		
	}
	break;
	case DRAW_TYPE::IMAGINECUTSCENE3:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\speechbubble_3_1.png";
		uObjectRender = new UObject();
		//uObjectRender->AnimationInitailze(entity->GetManagerset()->GetGraphics(), "AniimagineCutscene3", texturePath, 0, 500, 461, 348, 461, 2);
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "imagineCutscene3", upath, texturePath, 0, 500, 461, 348);
	}
	break;
	case DRAW_TYPE::CREDIT:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\credits.png";
		uObjectRender = new UObject();
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "creditscene", upath, texturePath, 120, 1000, 1670, 965);
	}
	break;
	default:
	{
		path[0] = L" ";
		path[1] = L" ";
		texturePath = L" ";
	}
	break;
	}

}




void DrawType::Update(float _deltatime)
{
	DirectX::SimpleMath::Matrix currentfinalMatrix = entity->GetComponent<Transform>()->GetFinalMatrix();

	Vector3 position = {};
	Quaternion quaternionRotation = {};
	Vector3 rotation = {};
	Vector3 scale = {};

	// Final Transform을 position, rotation, scale을 각각 분리해준다.
	currentfinalMatrix.Decompose(scale, quaternionRotation, position);

	// 쿼터니언으로 받은 회전 값을 vector로 돌려준다.
	//rotation = ToEulerAngles(quaternionRotation);

	rotation = entity->GetComponent<Transform>()->QuaternionToVector3(quaternionRotation);

	// 위치를 세팅한다.

	dt += _deltatime;

	if (aObjectRender != nullptr)
	{
		aObjectRender->SetPosition(position.x, position.y, position.z);
		aObjectRender->SetRotation(rotation.x, rotation.y, rotation.z);
		//aObjectRender->SetRotation(quaternionRotation);
		aObjectRender->SetScale(scale.x, scale.y, scale.z);

	}

	if (uObjectRender != nullptr)
	{
		if(dogAObject != nullptr)
			uObjectRender->AttachTo(dogAObject, -500, 400);
	}

	/*if (uObjectRender->name == "contract" && contractUp <= 590.f)
	{
		contractUp++;
		std::wstring texturePath = L"..\\Resource\\Texture\\UI\\contract.png";
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "contract", upath, texturePath, 340, contractUp, 1310, 600);
	}*/
		
}

void DrawType::Render()
{
	
	if (aObjectRender != nullptr && isAObjectVisible == true)
	{
		aObjectRender->Render();
	}

	if (uObjectRender != nullptr && isUIVisible == true)
	{
		uObjectRender->Render();
	}

	

}

void DrawType::SetAObject(AObject* _nowObject)
{
	aObjectRender = _nowObject;
}

AObject* DrawType::GetAObject()
{
	return aObjectRender;
}

DirectX::SimpleMath::Vector3 DrawType::ToEulerAngles(DirectX::SimpleMath::Quaternion _q)
{
	Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (_q.w * _q.x + _q.y * _q.z);
	double cosr_cosp = 1 - 2 * (_q.x * _q.x + _q.y * _q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (_q.w * _q.y - _q.x * _q.z));
	double cosp = std::sqrt(1 - 2 * (_q.w * _q.y - _q.x * _q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (_q.w * _q.z + _q.x * _q.y);
	double cosy_cosp = 1 - 2 * (_q.y * _q.y + _q.z * _q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}
