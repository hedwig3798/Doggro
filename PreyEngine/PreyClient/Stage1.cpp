#include "Stage1.h"

#include "Entity.h"
#include "Debug.h"
#include "DrawType.h"
#include "DogFSM.h"
#include "Transform.h"
#include "TestFloor.h"
#include "BoxCollider.h"
#include "CameraModule.h"
#include "ManagerSet.h"
#include "AudioManager.h"
#include "CollsionManager.h"
#include "IGraphicsEngine.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LoadMapData.h"
#include "QuestManager.h"
#include "AudioManager.h"
#include "GameManager.h"

#include "Dog.h"
#include "DogScript.h"
#include "DogSight.h"

#include "Wall.h"
#include "Floor.h"
#include "BackgroundWall.h"
#include "BackgroundWindow.h"

#include "Ball.h"
#include "BigBall.h"
#include "BedShelf.h"
#include "Clock.h"
#include "Bed.h"
#include "BedBlock.h"
#include "DogCushion.h"
#include "Desk.h"
#include "Cup.h"
#include "Chair.h"
#include "Doll.h"
#include "Trashcan.h"
#include "Chewbone.h"
#include "Closet.h"
#include "RopeFront.h"
#include "StaticCollider.h"
#include "DeskCollider.h"
#include "ClosetCollider.h"
#include "ClockCollider.h"
#include "BedCollider.h"
#include "ChairCollider.h"
#include "WallCollider.h"
#include "WallCollider2.h"
#include "BedShelfCollider.h"

#include "WallObject.h"
#include "RopeBack.h"

#include "UIObject.h"
#include "ImagineCutScene.h"
#include "CutScene.h"
#include "Button.h"
#include "UIButton.h"
#include "StageStart.h"
#include "GetSoul.h"
//#include "Souls.h"

Stage1::Stage1(std::string _name)
	: Scene(_name)
	, alarmTimer(0)
	, sec(0)
	, cutSceneTimer(0)
	, currentStartCutScene(4)
	, isStartSceneEnd(false)
	, popupTimer(0)
	, popupHeight(1232)
	, isUpDown(0)
	, isUpdownEnd(false)
	, isStageOver(false)
	, waitForSec(0)
	, zoomTimer(0)
{
	cupPosition.resize(3);
	chewbonePosition.resize(3);
}

Stage1::~Stage1()
{
	delete objectManager;
}

void Stage1::Start()
{
	GameManager::GetInstance()->isStage1Clear = false;

	isStartSceneEnd = false;
	
	//AudioManager::GetInstance()->PlayBGM(BGM::TEST1);
	//Get EveryMesh
	///맵 데이터 불러오는 부분
	objectManager = new LoadMapData(managerSet->GetGraphics());
	objectManager->LoadMapMesh("stage_1_bellydance.fbx");

	///퀘스트 메니저 생성
	stage1QuestManager = new QuestManager(1);

	///cutScene
	imagineCutScene = new ImagineCutScene("imagineCutScene1", managerSet, OBJECT_TYPE::UI, CUTSCENETYPE::STAGE1);
	AddGameObject(imagineCutScene);
	imagineCutScene->GetComponent<DrawType>()->SetUIVisible(false);

	///Dog
	Entity* dogSight = new DogSight("DogSight", managerSet, OBJECT_TYPE::TILE, stage1QuestManager);
	AddGameObject(dogSight);
	Entity* playDog2 = new Dog("Dog", managerSet, OBJECT_TYPE::TILE, DogType::Stage1, objectManager, stage1QuestManager, dogSight, imagineCutScene);
	AddGameObject(playDog2);

	///BackgroundObjects
	Entity* wall = new Wall("wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall);
	Entity* wallCollider = new WallCollider("wallCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wallCollider);
	Entity* wallCollider2 = new WallCollider2("wallCollider2", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wallCollider2);
	Entity* floor = new Floor("floor", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(floor);
	Entity* backgroundWall = new BackgroundWall("stage1_background_wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWall);
	Entity* backgroundWindow = new BackgroundWindow("background_window", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWindow);

	///NonInteractionObjects
	//wallObject
	Entity* wallObject = new WallObject("ornaments", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wallObject);
	//RopeBack
	Entity* ropeBack = new RopeBack("rope_2_broken", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(ropeBack);

	///Interaction Objects
	//ball
	Entity* ball = new Ball("ball", managerSet, OBJECT_TYPE::TILE, objectManager, stage1QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(ball);
	//bigball
	Entity* bigBall = new BigBall("bigball", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(bigBall);
	//bedShelf
	Entity* bedShelf = new BedShelf("shelf_bedroom", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(bedShelf);
	Entity* bedShelf2 = new BedShelfCollider("shelf_bedroom2", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(bedShelf2);
	//Clock
	Entity* clock = new Clock("clock", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(clock);
	Entity* clockCollider = new ClockCollider("clockCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(clockCollider);
	//bed
	Entity* bed = new Bed("bed", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(bed); 
	Entity* bedCollider = new BedCollider("bedCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(bedCollider);
	//bedBlock
	Entity* bedBlock = new BedBlock("bed_block", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(bedBlock);
	//dog Cushion
	Entity* dogCushion = new DogCushion("dog_cushion", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(dogCushion);
	//Desk
	Entity* desk = new Desk("desk", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(desk);
	Entity* deskCollider = new DeskCollider("deskCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(deskCollider);
	//Cup
	Entity* cup = new Cup("cup", managerSet, OBJECT_TYPE::TILE, objectManager, stage1QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(cup);

	Vector3 cupVector = cup->GetComponent<Transform>()->GetPosition();
	cupPosition[0] = cupVector.x;
	cupPosition[1] = cupVector.y;
	cupPosition[2] = cupVector.z;

	//Chair
	Entity* chair = new Chair("chair", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(chair);
	Entity* chairCollider = new ChairCollider("chairCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(chairCollider);
	//Doll
	Entity* doll = new Doll("doll", managerSet, OBJECT_TYPE::TILE, objectManager, stage1QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(doll);
	//Trashcan
	Entity* trashcan = new Trashcan("trashcan", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(trashcan);
	//ChewBone
	Entity* chewbone = new Chewbone("chewbone", managerSet, OBJECT_TYPE::TILE, objectManager, stage1QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(chewbone);

	Vector3 chewPosition = chewbone->GetComponent<Transform>()->GetPosition();
	chewbonePosition[0] = chewPosition.x;
	chewbonePosition[1] = chewPosition.y;
	chewbonePosition[2] = chewPosition.z;

	//Closet
	Entity* closet = new Closet("closet", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(closet);
	Entity* closetCollider = new ClosetCollider("closetCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(closetCollider);
	//RopeFront
	Entity* ropeFront = new RopeFront("rope_1_broken", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(ropeFront);

	//Entity* title = new UIObject("Title", managerSet, OBJECT_TYPE::UI, UITYPE::TITLE);
	//AddGameObject(title);

	///UI

	Entity* uiKeyGuide = new UIObject("KeyGuide", managerSet, OBJECT_TYPE::UI, UITYPE::KEYGUIDE);
	uiKeyGuide->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiKeyGuide);

	Entity* uiMissionPaper = new UIObject("MissionPaper", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPER);
	uiMissionPaper->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiMissionPaper);

	uiMissionPaperPiece = new UIObject("MissionPaperPiece", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPERPIECE1);
	uiMissionPaperPiece->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiMissionPaperPiece);

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
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		uiMenuBoard->GetComponent<DrawType>()->isUIVisible =!uiMenuBoard->GetComponent<DrawType>()->isUIVisible;
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
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiAlbumButton->GetComponent<Button>()->SetEnable();
		if (uiGuideBoard->GetComponent<DrawType>()->isUIVisible == true)
			uiAlbumButton->GetComponent<Button>()->SetEnable();
		});
	uiAlbumButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("stageSelect");
		return;
		});

	uiGuideButton->GetComponent<Button>()->SetImage(0, uiMenuGuide->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetImage(1, uiMenuGuide->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetImage(2, uiMenuGuide2->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetImage(3, uiMenuGuide->GetComponent<DrawType>());
	uiGuideButton->GetComponent<Button>()->SetButtonPos(RECT{ 800,700, 1217, 575 });
	uiGuideButton->GetComponent<Button>()->SetOnHover([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiGuideButton->GetComponent<Button>()->SetEnable();
		});
	uiGuideButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
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
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiExitButton->GetComponent<Button>()->SetEnable();
		});
	uiExitButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
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
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		});
	uiCloseButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		uiGuideBoard->GetComponent<DrawType>()->isUIVisible = false;
		uiAlbumButton->GetComponent<Button>()->SetEnable();
		uiCloseButton->GetComponent<Button>()->SetDisabled();
		});
	AddGameObject(uiCloseButton);
	AddGameObject(uiGuideBoard);

	uiCheck1 = new UIObject("Check1", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK1);
	AddGameObject(uiCheck1);
	stage1QuestManager->quest1Flag = -1;
	uiCheck1->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheck2 = new UIObject("Check2", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK2);
	AddGameObject(uiCheck2);
	uiCheck2->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheck3 = new UIObject("Check3", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK3);
	AddGameObject(uiCheck3);
	uiCheck3->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheck4 = new UIObject("Check4", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK4);
	AddGameObject(uiCheck4);
	uiCheck4->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheckFinal = new UIObject("Check5", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK5);
	AddGameObject(uiCheckFinal);
	uiCheckFinal->GetComponent<DrawType>()->SetUIVisible(false);

	//StartCutScene
	startScene = new StageStart("stageStart", managerSet, OBJECT_TYPE::UI);
	startScene->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(startScene);
	dynamic_cast<StageStart*>(startScene)->SetCutScene(currentStartCutScene);

	//iven
	uiSoulInventory = new GetSoul("GetSoul", managerSet, OBJECT_TYPE::UI);
	AddGameObject(uiSoulInventory);
	dynamic_cast<GetSoul*>(uiSoulInventory)->QuestClear(0.f);

	uiSoulInventory2 = new GetSoul("GetSoul", managerSet, OBJECT_TYPE::UI);
	AddGameObject(uiSoulInventory2);
	dynamic_cast<GetSoul*>(uiSoulInventory)->QuestClear(1080.f);
	uiSoulInventory2->GetComponent<DrawType>()->SetUIVisible(false);
	
	/*souls = new Souls("Souls", managerSet, OBJECT_TYPE::UI);
	AddGameObject(souls);
	uiSoulInventory2->GetComponent<DrawType>()->SetUIVisible(false);*/

	AddGameObject(uiAlbumButton);
	AudioManager::GetInstance()->StopAllSound();
	AudioManager::GetInstance()->PlayBGM(BGM::STAGE1);
}

void Stage1::Update(float _deltaTime)
{	
	
	// 여기서 퀘스트가 끝나면 넘어가도록 계속 확인하자.
	InputManager* inputManager = managerSet->GetInputManager();

	if (inputManager->IsKeyState(KEY::P, KEY_STATE::TAP))
	{
		GetGameObject("cup")->GetComponent<Transform>()->SetPosition(Vector3(cupPosition[0], cupPosition[1], cupPosition[2]));
		GetGameObject("chewbone")->GetComponent<Transform>()->SetPosition(Vector3(chewbonePosition[0], chewbonePosition[1], chewbonePosition[2]));
	}

	if (inputManager->IsKeyState(KEY::L, KEY_STATE::TAP))
	{
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("Stage2");
	}


	//마우스 클릭 시, 컷신 꺼짐
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP) && isStartSceneEnd == false)
	{
		startScene->GetComponent<DrawType>()->SetUIVisible(false);
		isStartSceneEnd = true;

	}

	///퀘스트를 위한 함수들

	///Quest1 30초 뒤에 퀘스트 시작.
	sec += _deltaTime;
	if (sec > 1)
	{
		alarmTimer++;
		sec = 0;
	}

	if (alarmTimer > 10 && stage1QuestManager->quest1Flag != 1)
	{	
		stage1QuestManager->quest1Flag = 0;
		AudioManager::GetInstance()->PlayEffect(EFFECT::Clock);
	}

	stage1QuestManager->Update(_deltaTime);

	/// 디버깅을 위한 퀘스트 완료
	//일단은 키
	if (inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
		stage1QuestManager->isQuest1Clear = true;
	
	if (inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
		stage1QuestManager->isQuest2Clear = true;

	if (inputManager->IsKeyState(KEY::F3, KEY_STATE::TAP))
		stage1QuestManager->isQuest3Clear = true;

	if (inputManager->IsKeyState(KEY::F4, KEY_STATE::TAP))
		stage1QuestManager->quest4Flag = true;

	
	//만약 퀘스트가 클리어시, 화면위에서 바가 생기고 
	// 강아지의 영혼이 들어간 다음 다시 올라간다.
	if (stage1QuestManager->quest1Flag == 1)
	{
		uiCheck1->GetComponent<DrawType>()->SetUIVisible(true);
	
	}
		
	if (stage1QuestManager->quest2Flag == 1)
	{
		uiCheck2->GetComponent<DrawType>()->SetUIVisible(true);
	
	}

	if (stage1QuestManager->quest3Flag == 1)
	{
		uiCheck3->GetComponent<DrawType>()->SetUIVisible(true);
		
	}
		
	if (stage1QuestManager->quest4Flag == 1)
	{
		uiCheck4->GetComponent<DrawType>()->SetUIVisible(true);
	
	}
		
	if (stage1QuestManager->finalQuestFlag == 1)
	{
		uiCheckFinal->GetComponent<DrawType>()->SetUIVisible(true);
		
	}

	///Final Quest 시작 (시작 전 컷씬 출력)
	if (stage1QuestManager->finalQuestFlag == 0)
	{
		cutSceneTimer += _deltaTime;

		if (cutSceneTimer < 5)
			imagineCutScene->GetComponent<DrawType>()->SetUIVisible(true);

		else
			imagineCutScene->GetComponent<DrawType>()->SetUIVisible(false);
		
		uiMissionPaperPiece->GetComponent<DrawType>()->SetUIVisible(false);
	}

	// 스테이지가 완료됬을 경우, 스테이지를 나가기 전 해야할 일들을 처리한다. 
	// 이건 한번만 불려야 한다.
	if (stage1QuestManager->isStageClear == true && isStageOver == false)
	{
		/// 줌인 넣어주세요!
		Entity* _dog = GetGameObject("Dog");
		bool _zoom = _dog->GetComponent<CameraModule>()->Zoom;
		bool _firstZoom = _dog->GetComponent<CameraModule>()->firstZoom;
		if (_zoom && !_firstZoom)
		{
			zoomTimer += _deltaTime;
			if (zoomTimer)
				_dog->GetComponent<CameraModule>()->ZoomIn(_deltaTime);
		}
		else
		{
			AudioManager::GetInstance()->StopAllSound();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Shutter);
			AudioManager::GetInstance()->PlayBGM(BGM::NEXT);
			GameManager::GetInstance()->gmGraphics->SetFlashEffect(_deltaTime, true);
			GameManager::GetInstance()->gmGraphics->ChaptuerScreen("Stage1");
			GameManager::GetInstance()->isStage1Clear = true;
			GameManager::GetInstance()->nowStage = 1;
			GameManager::GetInstance()->nowStageName = "Stage2";

			isStageOver = true;
		}
	}

	if (isStageOver == true)
	{
		waitForSec += _deltaTime;

		if (waitForSec > 2)
		{
			DeleteLiveObject();
			managerSet->GetSceneManager()->ChangeScene("stageSelect");
		}
	}
		
}

void Stage1::stageClear(int _questNumber)
{
	
	//stop
	if (popupHeight < 1080)
	{
		//stop
		//dynamic_cast<Souls*>(souls)->SetSoul(_questNumber);
		souls->GetComponent<DrawType>()->SetUIVisible(true);
		uiSoulInventory2->GetComponent<DrawType>()->SetUIVisible(true);
		dynamic_cast<GetSoul*>(uiSoulInventory2)->QuestClear(1080.f);
		isUpDown = true;
		popupTimer += 0.3;
		
		if (popupTimer >= 300)
		{
			uiSoulInventory2->GetComponent<DrawType>()->SetUIVisible(false);
			souls->GetComponent<DrawType>()->SetUIVisible(false);
			popupTimer = 0;
			popupHeight += 0.5;
		}
		
	}
	//up
	else if (isUpDown == true)
	{
		popupHeight = popupHeight + 0.1;
		dynamic_cast<GetSoul*>(uiSoulInventory)->QuestClear(popupHeight);
		
		if (popupHeight > 1232)
		{
			isUpDown = false;
			isUpdownEnd = true;
		}
	}

	//down
	if (isUpDown == false)
	{
		popupHeight = popupHeight - 0.1;
		dynamic_cast<GetSoul*>(uiSoulInventory)->QuestClear(popupHeight);
	}
}

void Stage1::DeleteLiveObject()
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

