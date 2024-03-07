#include "StageStart.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "DrawType.h"
#include "UObject.h"

StageStart::StageStart(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type)
	:Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));

	nowCutScene = new UObject;
}

StageStart::~StageStart()
{

}

void StageStart::SetCutScene(int _currentIndex)
{
	///Final Stage Start ÄÆ¾À
	if (_currentIndex == 0)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_paper.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "final", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 1)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_rope.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "final", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 2)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_rope_broken.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "final", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 3)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_rope_dog.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "final", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 4)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_paper.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "stage1CutScene", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 5)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_end_tresh.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "stage1CutScene", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 6)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\cut_end_flower.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "stage1CutScene", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 7)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\credits.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "stage1CutScene", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (_currentIndex == 8)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\CutScene\\title.png";
		nowCutScene->Initalize(this->GetManagerset()->GetGraphics(), "stage1CutScene", upath, texturePath, 0, 1080, 1920, 1080);
	}
	GetComponent<DrawType>()->SetUObject(nowCutScene);
}
