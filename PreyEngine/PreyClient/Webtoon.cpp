#include "Webtoon.h"
#include "UObject.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "InputManager.h"
#include "Entity.h"
#include "SceneManager.h"

Webtoon::Webtoon(Entity* _entity)
	: Component(_entity, "Webtoon")
{
	managerSet = entity->GetManagerset();
}

Webtoon::~Webtoon()
{

}

void Webtoon::Update(float _deltatime)
{
	InputManager* inputManager = managerSet->GetInputManager();
	SceneManager* sceneManager = managerSet->GetSceneManager();

	if (inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
	{
		++currentIndex;
		CutSceneLoad(currentIndex, managerSet->GetGraphics());
		
		if (currentIndex > 3)
			return;
	}

	/*if (inputManager->IsKeyState(KEY::B, KEY_STATE::TAP))
	{
		sceneManager->ChangeScene("Stage2");
	}*/

	//여기서 뭘 해야할 지는 모르겠는데 일단 내생각
	//이 클래스는 컷신을 인덱스에 따라 로딩하고 
}


void Webtoon::CutSceneLoad(int _currentIndex, IGraphicsEngine* _renderer)
{
	currentIndex = _currentIndex;

	if (currentIndex == 0)
	{
		//없음
	}
	if (currentIndex == 1)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\1";
		uObjectReneder = new UObject();
		uObjectReneder->Initalize(entity->GetManagerset()->GetGraphics(), "cutScene01", upath, texturePath, 100, 600, 800, 450);
	}
	if (currentIndex == 2)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI_dummy\\d_menu_album_button.png";
		uObjectReneder = new UObject();
		uObjectReneder->Initalize(entity->GetManagerset()->GetGraphics(), "cutScene02", upath, texturePath, 350, 300, 400, 100);
	}
	if (currentIndex == 3)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI_dummy\\d_menu_board.png";
		uObjectReneder = new UObject();
		uObjectReneder->Initalize(entity->GetManagerset()->GetGraphics(), "cutScene03", upath, texturePath, 100, 600, 800, 450);
	}
}

void Webtoon::Render()
{
	if (uObjectReneder != nullptr)
	{
		uObjectReneder->Render();
	}
}
