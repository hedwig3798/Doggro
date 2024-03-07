#include "Album.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "DrawType.h"
#include "UObject.h"

Album::Album(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type)
	: Entity(_name, _managerSet, _type)
	, selectX(0)
	, selectY(0)
{
	managerSet = _managerSet;
	CreateComponent<DrawType>(this);
	GetComponent<Transform>()->SetPosition(Vector3(0.f, 0.f, 0.f));

	nowAlbum = new UObject;
	nowSelect = new UObject;
}

Album::~Album()
{

}

void Album::SetCurrentAlbum(int _currentIndex)
{
	//아무것도 안 깼을때
	if (_currentIndex == 0)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\album1_board.png";
		nowAlbum->Initalize(this->GetManagerset()->GetGraphics(), "album", upath, texturePath, 0, 1080, 1920, 1080);
	}

	//1스테이지 깻을 때
	if (_currentIndex == 1)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\album2_board.png";
		nowAlbum->Initalize(this->GetManagerset()->GetGraphics(), "album", upath, texturePath, 0, 1080, 1920, 1080);
	}

	//2스테이지 깻을 때
	if (_currentIndex == 2)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\album3_board.png";
		nowAlbum->Initalize(this->GetManagerset()->GetGraphics(), "album", upath, texturePath, 0, 1080, 1920, 1080);
	}

	//3스테이지 깻을 때
	if (_currentIndex == 3)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\album4_board.png";
		nowAlbum->Initalize(this->GetManagerset()->GetGraphics(), "album", upath, texturePath, 0, 1080, 1920, 1080);
	}

	if (nowAlbum != nullptr)
		GetComponent<DrawType>()->SetUObject(nowAlbum);
}

void Album::SetCurrentStage(int _currentIndex)
{
	//아무것도 안 깼을때
	if (_currentIndex == 0)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\stage_select_g.png";
		nowSelect->Initalize(this->GetManagerset()->GetGraphics(), "albumSelectBlue", upath, texturePath, 210, 950, 560, 315);
		selectX = 210.f;
		selectY = 950.f;
	}

	//1스테이지 깻을 때
	if (_currentIndex == 1)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\stage_select_g.png";
		nowSelect->Initalize(this->GetManagerset()->GetGraphics(), "albumSelectBlue", upath, texturePath, 210, 470, 560, 315);
		selectX = 210.f;
		selectY = 470.f;
	}

	//2스테이지 깻을 때
	if (_currentIndex == 2)
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\Album\\stage_select_g.png";
		nowSelect->Initalize(this->GetManagerset()->GetGraphics(), "albumSelectBlue", upath, texturePath, 1150, 725, 560, 315);
		selectX = 1150.f;
		selectY = 725.f;
	}

	if (nowSelect != nullptr)
		GetComponent<DrawType>()->SetUObject(nowSelect);
		
	
		
}
