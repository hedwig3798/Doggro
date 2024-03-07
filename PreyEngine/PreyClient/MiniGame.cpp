#include "MiniGame.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "DrawType.h"
#include "UObject.h"

MiniGame::MiniGame(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));
	
	nowCutScene = new UObject;
}

MiniGame::~MiniGame()
{

}

void MiniGame::SetCutScene(int _currentIndex)
{
	if (_currentIndex == 0)
	{
	
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\scene1.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 1)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\2.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 2)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\3.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 3)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\4.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 4)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\5.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 5)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\6.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 6)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\7.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 7)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\8.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 8)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\9.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 9)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\10.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 10)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\11.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 11)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\12.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 12)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\13.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 13)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\14.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 14)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\15.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 15)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\16.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 16)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\MiniGame\\17.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 17)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_1_promise.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 18)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_2_promise.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}
	if (_currentIndex == 19)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_3_promise.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "miniGame", upath, texturePath, 0, 1080, 1920, 1080);
	}

	GetComponent<DrawType>()->SetUObject(nowCutScene);
}
