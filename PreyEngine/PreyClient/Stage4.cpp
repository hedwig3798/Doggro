#include "Stage4.h"

#include "ManagerSet.h"
#include "SceneManager.h"
#include "LoadMapData.h"
#include "QuestManager.h"
#include "InputManager.h"
#include "DrawType.h"
#include "GameManager.h"
#include "IGraphicsEngine.h"
#include "Transform.h"

#include "Dog.h"
#include "DogSight.h"
#include "DogScript.h"

#include "Wall.h"
#include "Floor.h"
#include "BackgroundWall.h"
#include "BackgroundWindow.h"

#include "Soju.h"
#include "Cabinet.h"
#include "Calendar.h"
#include "DisplayCupBoard.h"
#include "Door.h"
#include "Pot.h"
#include "ShelfLiving.h"
#include "ShoeRack.h"
#include "ShoesL.h"
#include "ShoesR.h"
#include "Slippers.h"
#include "Sofa.h"
#include "Table.h"
#include "Paper.h"
#include "Human.h"

#include "WallObject.h"
#include "Lighting.h"

#include "DisplayCupBoardCollider.h"
#include "TableCollider4.h"
#include "WallCollider2Stage.h"
#include "Wall4.h"
#include "WallCollider2Stage2.h"
#include "DisplayCupCollider4.h"
#include "PotCollider.h"


#include "UIObject.h"
#include "UIButton.h"
#include "Button.h"
#include "ImagineCutScene.h"
#include "MiniGame.h"
#include "StageStart.h"

#include "AudioManager.h"


#include "InputManager.h"

Stage4::Stage4(std::string _name)
	: Scene(_name)
	, currentScene(0)
	, currentStartCutScene(0)
	, isStartSceneEnd(false)
	, isEndSceneEnd(false)
	, timerMan(0)
	, whiteOnlyone(false)
{
	humanPosition.resize(3);
	humanRotation.resize(4);
}

Stage4::~Stage4()
{
}

void Stage4::Start()
{
	// reset 시 필요
	currentScene = 0;
	currentStartCutScene = 0;
	isEndSceneEnd = false;
	whiteOnlyone = false;
	isStartSceneEnd = false;
	timerMan = 0;

	//컷씬을 위한 인풋메니저 가져오기
	GameManager::GetInstance()->isStage1Clear = false;
	GameManager::GetInstance()->isStage2Clear = false;
	GameManager::GetInstance()->isStage3Clear = false;
	GameManager::GetInstance()->isStage4Clear = false;

	inputManager = managerSet->GetInputManager();

	///맵 데이터 불러오는 부분
	objectManager = new LoadMapData(managerSet->GetGraphics());
	objectManager->LoadMapMesh("stage_4_bellydance.fbx");

	///퀘스트 메니저 생성
	stage4QuestManager = new QuestManager(4);
	stage4QuestManager->quest2Flag = -1;
	stage4QuestManager->quest3Flag = -1;


	///cutScene
	imagineCutScene = new ImagineCutScene("imagineCutScene3", managerSet, OBJECT_TYPE::UI, CUTSCENETYPE::STAGE3);
	imagineCutScene->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(imagineCutScene);

	///Dog
	Entity* dogSight = new DogSight("DogSight", managerSet, OBJECT_TYPE::TILE, stage4QuestManager);
	AddGameObject(dogSight);
	Entity* playDog2 = new Dog("Dog", managerSet, OBJECT_TYPE::TILE, DogType::Stage4, objectManager, stage4QuestManager, dogSight, imagineCutScene);
	AddGameObject(playDog2);

	///Background
	//wall
	Entity* wall = new Wall("wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall);
	Entity* wall2 = new WallCollider2Stage("wall2", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall2);
	Entity* wall3 = new Wall4("wall3", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall3);
	//floor
	Entity* floor = new Floor("floor", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(floor);
	Entity* backgroundWall = new BackgroundWall("stage4_background_wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWall);
	Entity* backgroundWindow = new BackgroundWindow("background_window", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWindow);

	///Interation
	//door
	Entity* door = new Door("door", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(door);
	//shoeRack
	Entity* shoeRack = new ShoeRack("shoe_rack", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(shoeRack);
	//shoesL
	Entity* shoesL = new ShoesL("shoes_L", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(shoesL);
	//shoesR
	Entity* shoesR = new ShoesR("shoes_R", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(shoesR);
	//Slippers
	Entity* slippers = new Slippers("slippers", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(slippers);
	//Shelf_living
	Entity* shelfLiving = new ShelfLiving("shelf_livingroom", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(shelfLiving);
	//Sofa
	Entity* sofa = new Sofa("sofa", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(sofa);
	//Pot
	Entity* pot = new Pot("pot", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(pot);
	Entity* pot2 = new PotCollider("pot2", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(pot2);
	//Cabinet
	Entity* cabinet = new Cabinet("cabinet", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(cabinet);
	//Calendar
	Entity* calendar = new Calendar("calendar", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(calendar);
	//DisplayCupBoard
	Entity* displayCupBoard = new DisplayCupBoard("display_cupboard", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(displayCupBoard);
	Entity* displayCupBoardCollider = new DisplayCupCollider4("display_cupboardCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(displayCupBoardCollider);
	//Table
	Entity* tableLiving = new Table("table", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(tableLiving);
	Entity* tableLivingCollider = new TableCollider4("tableCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(tableLivingCollider);
	//Paper
	Entity* paper = new Paper("paperpile", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(paper);
	//human
	Entity* human = new Human("human", managerSet, OBJECT_TYPE::TILE, objectManager, stage4QuestManager);
// 	human->GetComponent<Transform>()->SetPosition(Vector3(205.f, 40.f, -390.f));
// 	human->GetComponent<Transform>()->SetRotation(Quaternion(0.0f, 0.70f, 0.0f, 0.70f));
	dynamic_cast<Dog*>(playDog2)->GetHuman(human);
	AddGameObject(human);

	Vector3 humanVector = human->GetComponent<Transform>()->GetPosition();
	humanPosition[0] = humanVector.x;
	humanPosition[1] = humanVector.y;
	humanPosition[2] = humanVector.z;

	Quaternion humanVector4 = human->GetComponent<Transform>()->GetRotation();
	humanRotation[0] = humanVector4.x;
	humanRotation[1] = humanVector4.y;
	humanRotation[2] = humanVector4.z;
	humanRotation[3] = humanVector4.w;
	
	///soju
	Entity* soju1 = new Soju("01_soju", managerSet, OBJECT_TYPE::TILE, objectManager, stage4QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(soju1);
	Entity* soju2 = new Soju("02_soju", managerSet, OBJECT_TYPE::TILE, objectManager, stage4QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(soju2);
	Entity* soju3 = new Soju("03_soju", managerSet, OBJECT_TYPE::TILE, objectManager, stage4QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(soju3);
	

	///NonInteration
	//wallObject
	Entity* wallObject = new WallObject("ornaments", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wallObject);
	//wallObject
	Entity* lighting = new Lighting("lamp", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(lighting);

	///UI
	Entity* uiKeyGuide = new UIObject("KeyGuide", managerSet, OBJECT_TYPE::UI, UITYPE::KEYGUIDE);
	uiKeyGuide->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiKeyGuide);

	Entity* uiMissionPaper = new UIObject("MissionPaper", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPER4);
	uiMissionPaper->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiMissionPaper);

	uiMissionPaperPiece1 = new UIObject("MissionPaperPiece1", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPERPIECE4_1);
	uiMissionPaperPiece1->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiMissionPaperPiece1);

	uiMissionPaperPiece2 = new UIObject("MissionPaperPiece2", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPERPIECE4_2);
	uiMissionPaperPiece2->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiMissionPaperPiece2);

	Entity* uiMenuBoard = new UIObject("MenuBoard", managerSet, OBJECT_TYPE::UI, UITYPE::MENUBOARD);
	AddGameObject(uiMenuBoard);

	Entity* uiGuideBoard = new UIObject("GuideBoard", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUGUIDEBOARD);


	uiSetting = new UIObject("Setting", managerSet, OBJECT_TYPE::UI, UITYPE::SETTING);
	uiSetting2 = new UIObject("Setting2", managerSet, OBJECT_TYPE::UI, UITYPE::SETTING2);
	uiMenuClose = new UIObject("MenuClose", managerSet, OBJECT_TYPE::UI, UITYPE::CLOSE);
	uiMenuClose2 = new UIObject("MenuClose2", managerSet, OBJECT_TYPE::UI, UITYPE::CLOSE2);
	uiMenuAlbum = new UIObject("MenuAlbum", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUALBUM);
	uiMenuAlbum2 = new UIObject("MenuAlbum2", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUALBUM2);
	uiMenuExit = new UIObject("MenuExit", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUGAMEEXIT);
	uiMenuExit2 = new UIObject("MenuExit2", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUGAMEEXIT2);
	uiMenuGuide = new UIObject("MenuGuide", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUGUIDE);
	uiMenuGuide2 = new UIObject("MenuGuide2", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUGUIDE2);


	uiMenuBoard->GetComponent<DrawType>()->SetUIVisible(false);
	uiMenuAlbum->GetComponent<DrawType>()->SetUIVisible(true);
	uiMenuGuide->GetComponent<DrawType>()->SetUIVisible(true);
	uiMenuExit->GetComponent<DrawType>()->SetUIVisible(true);
	uiMenuClose->GetComponent<DrawType>()->SetUIVisible(true);
	uiGuideBoard->GetComponent<DrawType>()->SetUIVisible(false);

	Entity* uiButton = new UIButton("Button", managerSet, OBJECT_TYPE::UI);
	Entity* uiAlbumButton = new UIButton("AlbumButton", managerSet, OBJECT_TYPE::UI);
	Entity* uiGuideButton = new UIButton("GuideButton", managerSet, OBJECT_TYPE::UI);
	Entity* uiExitButton = new UIButton("ExitButton", managerSet, OBJECT_TYPE::UI);
	Entity* uiCloseButton = new UIButton("CloseButton", managerSet, OBJECT_TYPE::UI);

	uiButton->CreateComponent<Button>(uiButton);
	uiAlbumButton->CreateComponent<Button>(uiAlbumButton);
	uiGuideButton->CreateComponent<Button>(uiGuideButton);
	uiExitButton->CreateComponent<Button>(uiExitButton);
	uiCloseButton->CreateComponent<Button>(uiCloseButton);

	uiButton->GetComponent<Button>()->SetEnable();
	uiButton->GetComponent<Button>()->SetImage(0, uiSetting->GetComponent<DrawType>());
	uiButton->GetComponent<Button>()->SetImage(1, uiSetting2->GetComponent<DrawType>());
	uiButton->GetComponent<Button>()->SetImage(2, uiSetting->GetComponent<DrawType>());
	uiButton->GetComponent<Button>()->SetImage(3, uiSetting->GetComponent<DrawType>());
	uiButton->GetComponent<Button>()->SetButtonPos(RECT{ 1785, 1080, 1917, 954 });
	uiButton->GetComponent<Button>()->SetOnClick([=]() {
		uiMenuBoard->GetComponent<DrawType>()->isUIVisible = !uiMenuBoard->GetComponent<DrawType>()->isUIVisible;
		if (uiButton->GetComponent<Button>()->isClick == true)
		{
			uiAlbumButton->GetComponent<Button>()->SetEnable();
			uiGuideButton->GetComponent<Button>()->SetEnable();
			uiExitButton->GetComponent<Button>()->SetEnable();
		}
		else
		{
			uiAlbumButton->GetComponent<Button>()->SetDisabled();
			uiGuideButton->GetComponent<Button>()->SetDisabled();
			uiExitButton->GetComponent<Button>()->SetDisabled();
		}
		});
	AddGameObject(uiButton);



	uiAlbumButton->GetComponent<Button>()->SetImage(0, uiMenuAlbum->GetComponent<DrawType>());
	uiAlbumButton->GetComponent<Button>()->SetImage(1, uiMenuAlbum->GetComponent<DrawType>());
	uiAlbumButton->GetComponent<Button>()->SetImage(2, uiMenuAlbum2->GetComponent<DrawType>());
	uiAlbumButton->GetComponent<Button>()->SetImage(3, uiMenuAlbum->GetComponent<DrawType>());
	uiAlbumButton->GetComponent<Button>()->SetButtonPos(RECT{ 800,850, 1217, 725 });
	uiAlbumButton->GetComponent<Button>()->SetOnHover([=]() {
		if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiAlbumButton->GetComponent<Button>()->SetEnable();
		if (uiGuideBoard->GetComponent<DrawType>()->isUIVisible == true)
			uiAlbumButton->GetComponent<Button>()->SetEnable();
		});
	uiAlbumButton->GetComponent<Button>()->SetOnClick([=]() {
		//managerSet->GetSceneManager()->ChangeScene("stageSelect");
		});


	uiGuideButton->GetComponent<Button>()->SetImage(0, uiMenuGuide->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetImage(1, uiMenuGuide->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetImage(2, uiMenuGuide2->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetImage(3, uiMenuGuide->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetButtonPos(RECT{ 800,700, 1217, 575 });
	uiGuideButton->GetComponent<Button>()->SetOnHover([=]() {
		if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiGuideButton->GetComponent<Button>()->SetEnable();
		});
	uiGuideButton->GetComponent<Button>()->SetOnClick([=]() {
		uiGuideBoard->GetComponent<DrawType>()->isUIVisible = true;
		uiAlbumButton->GetComponent<Button>()->SetDisabled();
		uiCloseButton->GetComponent<Button>()->SetEnable();
		});
	AddGameObject(uiGuideButton);

	uiExitButton->GetComponent<Button>()->SetImage(0, uiMenuExit->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetImage(1, uiMenuExit->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetImage(2, uiMenuExit2->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetImage(3, uiMenuExit->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetButtonPos(RECT{ 800,550, 1217, 425 });
	uiExitButton->GetComponent<Button>()->SetOnHover([=]() {
		if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiExitButton->GetComponent<Button>()->SetEnable();
		});
	uiExitButton->GetComponent<Button>()->SetOnClick([=]() {
		PostQuitMessage(0);
		});
	AddGameObject(uiExitButton);

	uiCloseButton->GetComponent<Button>()->SetImage(0, uiMenuClose->GetComponent<DrawType>());
	uiCloseButton->GetComponent<Button>()->SetImage(1, uiMenuClose2->GetComponent<DrawType>());
	uiCloseButton->GetComponent<Button>()->SetImage(2, uiMenuClose->GetComponent<DrawType>());
	uiCloseButton->GetComponent<Button>()->SetImage(3, uiMenuClose->GetComponent<DrawType>());
	uiCloseButton->GetComponent<Button>()->SetButtonPos(RECT{ 1570,1020, 1670, 980 });
	uiCloseButton->GetComponent<Button>()->SetOnHover([=]() {
		/*if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiCloseButton->GetComponent<Button>()->SetEnable();*/
		});
	uiCloseButton->GetComponent<Button>()->SetOnClick([=]() {
		uiGuideBoard->GetComponent<DrawType>()->isUIVisible = false;
		uiAlbumButton->GetComponent<Button>()->SetEnable();
		uiCloseButton->GetComponent<Button>()->SetDisabled();
		});
	AddGameObject(uiCloseButton);
	AddGameObject(uiGuideBoard);

	//Check
	uiCheck1 = new UIObject("Check1", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK1);
	uiCheck1->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck1);
	uiCheck2 = new UIObject("Check2", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK2);
	uiCheck2->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck2);
	uiCheck3 = new UIObject("Check3", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK3);
	uiCheck3->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck3);
	
	//MiniGame
	miniGame = new MiniGame("miniGame", managerSet, OBJECT_TYPE::UI);
	miniGame->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(miniGame);

	//StartCutScene
	startScene = new StageStart("stageStart", managerSet, OBJECT_TYPE::UI);
	startScene->GetComponent<DrawType>()->SetUIVisible(true);
	dynamic_cast<StageStart*>(startScene)->SetCutScene(currentStartCutScene);
	AddGameObject(startScene);

	//EndCutScene
	endScene = new StageStart("stageend", managerSet, OBJECT_TYPE::UI);
	endScene->GetComponent<DrawType>()->SetUIVisible(false);
	dynamic_cast<StageStart*>(endScene)->SetCutScene(currentStartCutScene);
	AddGameObject(endScene);

	AddGameObject(uiAlbumButton);
	AudioManager::GetInstance()->StopAllSound();
	AudioManager::GetInstance()->PlayBGM(BGM::STAGE4CUT);
}

void Stage4::Update(float _deltaTime)
{

	//startCutSceneUpdate
	if ((inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP) && isStartSceneEnd == false))
	{
		dynamic_cast<StageStart*>(startScene)->SetCutScene(currentStartCutScene);
		currentStartCutScene++;

		if (currentStartCutScene == 1)
		{
			AudioManager::GetInstance()->PlayEffect(EFFECT::Cut_Paper);
		}

		if (currentStartCutScene == 3)
		{
			AudioManager::GetInstance()->PlayEffect(EFFECT::Cut_Rope);
		}

		if (currentStartCutScene == 4)
		{
			AudioManager::GetInstance()->PlayEffect(EFFECT::Rope);
		}

		//컷씬종료
		if (currentStartCutScene > 4)
		{
			startScene->GetComponent<DrawType>()->SetUIVisible(false);
			isStartSceneEnd = true;
			AudioManager::GetInstance()->StopAllSound();
			AudioManager::GetInstance()->PlayBGM(BGM::STAGE4);
		}
	}

	//EndCutSceneUpdate
	if (stage4QuestManager->isStageClear == true && timerMan < 3)
	{
		timerMan += _deltaTime;

		if (timerMan > 1 && whiteOnlyone == false)
		{
			GameManager::GetInstance()->gmGraphics->SetWhiteOutEffect(_deltaTime, true);
			whiteOnlyone = true;
			
		}
		if (whiteOnlyone == true && timerMan > 2)
		{
			dynamic_cast<StageStart*>(startScene)->SetCutScene(currentStartCutScene);
			startScene->GetComponent<DrawType>()->SetUIVisible(true);
		}
	}

	if ((inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP) && isEndSceneEnd == false && stage4QuestManager->isStageClear == true))
	{	
		currentStartCutScene++;
		dynamic_cast<StageStart*>(startScene)->SetCutScene(currentStartCutScene);
		
		//컷씬종료
		if (currentStartCutScene > 9)
		{
			startScene->GetComponent<DrawType>()->SetUIVisible(false);
			isEndSceneEnd = true;

			//managerSet->GetSceneManager()->ChangeScene("mainScene");
		}
	}

	if (inputManager->IsKeyState(KEY::P, KEY_STATE::TAP))
	{
		managerSet->GetSceneManager()->ResetScene("Stage4");
		return;
	}

	
	///퀘스트를 위한 함수들
	stage4QuestManager->Update(_deltaTime);

	/// 디버깅을 위한 퀘스트 완료
	//일단은 키
	if (inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
		stage4QuestManager->quest1Flag = true;

	if (inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
		stage4QuestManager->quest2Flag = true;

	if (inputManager->IsKeyState(KEY::F3, KEY_STATE::TAP))
		stage4QuestManager->quest2Flag = true;

	//퀘스트 완료시, 체크표시 해주세요
	if (stage4QuestManager->quest1Flag == true)
	{
		uiCheck1->GetComponent<DrawType>()->SetUIVisible(true);
		uiMissionPaperPiece1->GetComponent<DrawType>()->SetUIVisible(false);
	}
		
	if (stage4QuestManager->quest2Flag == true)
	{
		uiCheck2->GetComponent<DrawType>()->SetUIVisible(true);
		
		if (stage4QuestManager->quest3Flag != 1)
		{
			stage4QuestManager->quest3Flag = 0;
			stage4QuestManager->isQuest3Start = true;
		}

		uiMissionPaperPiece2->GetComponent<DrawType>()->SetUIVisible(false);
	}
		
	if (stage4QuestManager->quest3Flag == true)
	{
		uiCheck3->GetComponent<DrawType>()->SetUIVisible(true);
		stage4QuestManager->isStageClear = true;
	}
		
	if (stage4QuestManager->startMiniGame == true && !firstIn)
	{
		AudioManager::GetInstance()->StopAllSound();
		AudioManager::GetInstance()->PlayBGM(BGM::MINIGAME);
		firstIn = true;
	}

	//미니게임 시작(ui를 안투명하게 바꾸기)
	if (stage4QuestManager->startMiniGame == true)
	{
		miniGame->GetComponent<DrawType>()->SetUIVisible(true);
	}

	//컷씬 재생
	if(inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP) && stage4QuestManager->startMiniGame == true)
	{



		dynamic_cast<MiniGame*>(miniGame)->SetCutScene(currentScene);
		currentScene++;

		//미니게임 종료
		if (currentScene > 20)
		{
			miniGame->GetComponent<DrawType>()->SetUIVisible(false);
			stage4QuestManager->isQuest1Clear = true;
			stage4QuestManager->startMiniGame = false;
			firstIn = false;

			stage4QuestManager->quest2Flag = 0;
		}		
	}

	if (isEndSceneEnd == true)
	{
		//컷씬을 위한 인풋메니저 가져오기
		GameManager::GetInstance()->isStage1Clear = false;
		GameManager::GetInstance()->isStage2Clear = false;
		GameManager::GetInstance()->isStage3Clear = false;
		GameManager::GetInstance()->isStage4Clear = false;

		GameManager::GetInstance()->nowStage = 0;
		GameManager::GetInstance()->nowStageName = "Stage1";

		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("mainScene");
	}
}

void Stage4::DeleteLiveObject()
{
	this->uiSetting->Finalize();
	this->uiSetting2->Finalize();
	this->uiMenuClose->Finalize();
	this->uiMenuClose2->Finalize();
	this->uiMenuAlbum->Finalize();
	this->uiMenuAlbum2->Finalize();
	this->uiMenuExit->Finalize();
	this->uiMenuExit2->Finalize();
	this->uiMenuGuide->Finalize();
	this->uiMenuGuide2->Finalize();

	delete this->uiSetting;
	delete this->uiSetting2;
	delete this->uiMenuClose;
	delete this->uiMenuClose2;
	delete this->uiMenuAlbum;
	delete this->uiMenuAlbum2;
	delete this->uiMenuExit;
	delete this->uiMenuExit2;
	delete this->uiMenuGuide;
	delete this->uiMenuGuide2;
}
