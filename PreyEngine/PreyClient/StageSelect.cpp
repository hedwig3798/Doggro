#include "StageSelect.h"

#include "GameManager.h"
#include "ManagerSet.h"
#include "SceneManager.h"
#include "IGraphicsEngine.h"

#include "DrawType.h"
#include "Button.h"

#include "Album.h"


StageSelect::StageSelect(std::string _name)
	:Scene(_name)
	, blink(0)
	, stageChangeTimer(0)
	, isEffectOn(false)
{

}

StageSelect::~StageSelect()
{

}

void StageSelect::Start()
{
	currentAlbumNumber = GameManager::GetInstance()->nowStage;
	std::string currentStageName = GameManager::GetInstance()->nowStageName;

	Entity* album = new Album("Album", managerSet, OBJECT_TYPE::TILE);
	dynamic_cast<Album*>(album)->SetCurrentAlbum(currentAlbumNumber);
	AddGameObject(album);

	if (currentAlbumNumber != 3)
	{
		selectAlbum = new Album("Select", managerSet, OBJECT_TYPE::UI);
		dynamic_cast<Album*>(selectAlbum)->SetCurrentStage(currentAlbumNumber);
		int nowX = dynamic_cast<Album*>(selectAlbum)->selectX;
		int nowY = dynamic_cast<Album*>(selectAlbum)->selectY;

		selectAlbum->CreateComponent<Button>(selectAlbum);
		selectAlbum->GetComponent<Button>()->SetEnable();
		selectAlbum->GetComponent<Button>()->haveImage = false;
		selectAlbum->GetComponent<Button>()->SetButtonPos(RECT{ nowX, nowY, nowX + 560, nowY - 315 });
		selectAlbum->GetComponent<Button>()->SetOnClick([=]() {managerSet->GetSceneManager()->ChangeScene(currentStageName); });
		AddGameObject(selectAlbum);
	}
	
	float blink = 0;
	float stageChangeTimer = 0;


}

void StageSelect::Update(float deltaTime)
{
	blink += deltaTime;
	stageChangeTimer += deltaTime;

	if (currentAlbumNumber != 3)
	{
		//¹öÆ° ±ôºýÀÌ±â
		if (blink > 1)
			selectAlbum->GetComponent<DrawType>()->SetUIVisible(false);
		if (blink > 2)
		{
			selectAlbum->GetComponent<DrawType>()->SetUIVisible(true);
			blink = 0;
		}
	}

	if (currentAlbumNumber == 1)
	{
		GameManager::GetInstance()->gmGraphics->ShowChaptueredImage("Stage1", RECT{ 210, 635, 770, 950 });
	}

	if (currentAlbumNumber == 2)
	{
		GameManager::GetInstance()->gmGraphics->ShowChaptueredImage("Stage1", RECT{ 210, 635, 770, 950 });
		GameManager::GetInstance()->gmGraphics->ShowChaptueredImage("Stage2", RECT{ 210, 155, 770, 470 });
	}

	if (currentAlbumNumber == 3)
	{
		GameManager::GetInstance()->gmGraphics->ShowChaptueredImage("Stage1", RECT{ 210, 635, 770, 950 });
		GameManager::GetInstance()->gmGraphics->ShowChaptueredImage("Stage2", RECT{ 210, 155, 770, 500 });
		GameManager::GetInstance()->gmGraphics->ShowChaptueredImage("Stage3", RECT{ 1150, 410, 1710, 725 });
	}
	
	if (currentAlbumNumber == 3)
	{
		
		/*if (stageChangeTimer > 1 && isEffectOn == false)
		{
			GameManager::GetInstance()->gmGraphics->SetWhiteOutEffect(deltaTime, true);
			isEffectOn = true;
		}*/

		if (stageChangeTimer > 3)
		{
			managerSet->GetSceneManager()->ChangeScene("Stage4");
			currentAlbumNumber = 1;
		}
			
	}



}
