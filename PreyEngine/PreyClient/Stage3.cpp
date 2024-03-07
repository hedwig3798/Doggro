#include "Stage3.h"

#include "LoadMapData.h"
#include "QuestManager.h"
#include "CameraModule.h"
#include "Transform.h"
#include "DrawType.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "GameManager.h"

#include "Dog.h"
#include "DogSight.h"
#include "DogScript.h"

#include "Wall.h"
#include "Floor.h"
#include "BackgroundWall.h"
#include "BackgroundWindow.h"

#include "Desk.h"
#include "Bed.h"
#include "BedBlock.h"
#include "DogCushion.h"
#include "Chair.h"
#include "Doll.h"
#include "BedShelf.h"
#include "Closet.h"
#include "Clock.h"
#include "Cup.h"
#include "Trashcan.h"
#include "Cloths.h"
#include "Ball.h"
#include "Chewbone.h"

#include "WallObject.h"
#include "DeskCollider.h"
#include "Chair3Collider.h"
#include "ClosetCollider.h"
#include "BedCollider.h"
#include "ClockCollider.h"
#include "BedShelfCollider.h"
#include "DollCollider.h"

#include "UIObject.h"
#include "Button.h"
#include "UIButton.h"
#include "ImagineCutScene.h"

#include "WallCollider.h"
#include "WallCollider2.h"

#include "InputManager.h"
#include "SceneManager.h"
#include "AudioManager.h"

Stage3::Stage3(std::string _name)
	: Scene(_name)
	, isStageOver(false)
	, cutSceneTimer(0)
	, zoomTimer(0)
	, waitForSec(0)
{
	chewBonePosition.resize(3);
	dollPosition.resize(3);
}

Stage3::~Stage3()
{
	delete objectManager;
}

void Stage3::Start()
{
	GameManager::GetInstance()->isStage1Clear = false;
	GameManager::GetInstance()->isStage2Clear = false;
	GameManager::GetInstance()->isStage3Clear = false;

	///맵 데이터 불러오는 부분
	objectManager = new LoadMapData(managerSet->GetGraphics());
	objectManager->LoadMapMesh("stage_3_bellydance.fbx");

	///퀘스트 메니저 생성
	stage3QuestManager = new QuestManager(3);

	///cutScene
	imagineCutScene = new ImagineCutScene("imagineCutScene3", managerSet, OBJECT_TYPE::UI, CUTSCENETYPE::STAGE3);
	AddGameObject(imagineCutScene);
	imagineCutScene->GetComponent<DrawType>()->SetUIVisible(false);

	///Dog
	Entity* dogSight = new DogSight("DogSight", managerSet, OBJECT_TYPE::TILE, stage3QuestManager);
	AddGameObject(dogSight);
	Entity* playDog2 = new Dog("Dog", managerSet, OBJECT_TYPE::TILE, DogType::Stage3, objectManager, stage3QuestManager, dogSight, imagineCutScene);
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
	Entity* backgroundWall = new BackgroundWall("stage3_background_wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWall);
	Entity* backgroundWindow = new BackgroundWindow("background_window", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWindow);

	///NonInteractionObjects
	//wallObject
	Entity* wallObject = new WallObject("ornaments", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wallObject);

	///Interaction Objects
	//ball
	Entity* ball = new Ball("ball", managerSet, OBJECT_TYPE::TILE, objectManager, stage3QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(ball);
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
	Entity* cup = new Cup("cup", managerSet, OBJECT_TYPE::TILE, objectManager, stage3QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(cup);
	//Chair
	Entity* chair = new Chair("chair", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(chair);
	Entity* chairCollider = new Chair3Collider("chair3Collider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(chairCollider);
	//Doll
	Entity* doll = new Doll("doll", managerSet, OBJECT_TYPE::TILE, objectManager, stage3QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(doll); 

	Vector3 dollVector = doll->GetComponent<Transform>()->GetPosition();
	dollPosition[0] = dollVector.x;
	dollPosition[1] = dollVector.y;
	dollPosition[2] = dollVector.z;

	//Trashcan
	Entity* trashcan = new Trashcan("trashcan", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(trashcan);
	//ChewBone
	Entity* chewbone = new Chewbone("chewbone", managerSet, OBJECT_TYPE::TILE, objectManager, stage3QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(chewbone);

	Vector3 chewboneVector = chewbone->GetComponent<Transform>()->GetPosition();
	chewBonePosition[0] = chewboneVector.x;
	chewBonePosition[1] = chewboneVector.y;
	chewBonePosition[2] = chewboneVector.z;

	//Closet
	Entity* closet = new Closet("closet", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(closet);
	Entity* closetCollider = new ClosetCollider("closetCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(closetCollider);
	//Cloths
	Entity* clothes = new Cloths("clothes", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(clothes);

	///UI
	Entity* uiKeyGuide = new UIObject("KeyGuide", managerSet, OBJECT_TYPE::UI, UITYPE::KEYGUIDE);
	AddGameObject(uiKeyGuide);
	uiKeyGuide->GetComponent<DrawType>()->SetUIVisible(true);
	
	Entity* uiMissionPaper = new UIObject("MissionPaper", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPER3);
	AddGameObject(uiMissionPaper);
	uiMissionPaper->GetComponent<DrawType>()->SetUIVisible(true);
	
	uiMissionPaperPiece = new UIObject("MissionPaperPiece", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPERPIECE3);
	uiMissionPaperPiece->GetComponent<DrawType>()->SetUIVisible(true);
	AddGameObject(uiMissionPaperPiece);

	Entity* uiMenuBoard = new UIObject("MenuBoard", managerSet, OBJECT_TYPE::UI, UITYPE::MENUBOARD);
	AddGameObject(uiMenuBoard);

	Entity* uiGuideBoard = new UIObject("GuideBoard", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUGUIDEBOARD);

	uiSetting = new UIObject("Setting", managerSet, OBJECT_TYPE::UI, UITYPE::SETTING);
	uiSetting2 = new UIObject("Setting2", managerSet, OBJECT_TYPE::UI, UITYPE::SETTING2);
	uiMenuClose = new UIObject("MenuClose", managerSet, OBJECT_TYPE::UI, UITYPE::CLOSE);
	uiMenuClose2 = new UIObject("MenuClose2", managerSet, OBJECT_TYPE::UI, UITYPE::CLOSE2);
	Entity* uiMenuAlbum = new UIObject("MenuAlbum", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::MENUALBUM);
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
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		/*if (uiMenuBoard->GetComponent<DrawType>()->isUIVisible == false)
			uiCloseButton->GetComponent<Button>()->SetEnable();*/
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
	uiCheck1->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheck2 = new UIObject("Check2", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK2);
	AddGameObject(uiCheck2);
	uiCheck2->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheck3 = new UIObject("Check3", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK3);
	AddGameObject(uiCheck3);
	uiCheck3->GetComponent<DrawType>()->SetUIVisible(false);
	uiCheckFinal = new UIObject("Check4", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK4);
	AddGameObject(uiCheckFinal);
	uiCheckFinal->GetComponent<DrawType>()->SetUIVisible(false);

	AddGameObject(uiAlbumButton);

	AudioManager::GetInstance()->StopAllSound();
	AudioManager::GetInstance()->PlayBGM(BGM::STAGE3);
}

void Stage3::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();

	//스테이지 넘어가기용 빠른 키
	if (inputManager->IsKeyState(KEY::M, KEY_STATE::TAP))
	{
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("Stage4");
	}

	if (inputManager->IsKeyState(KEY::P, KEY_STATE::TAP))
	{
		GetGameObject("chewbone")->GetComponent<Transform>()->SetPosition(Vector3(chewBonePosition[0], chewBonePosition[1], chewBonePosition[2]));
		GetGameObject("doll")->GetComponent<Transform>()->SetPosition(Vector3(dollPosition[0], dollPosition[1], dollPosition[2]));
	}

	///퀘스트를 위한 함수들
	stage3QuestManager->Update(0.03);

	///디버깅용
	/*stage3QuestManager->quest2Flag = true;
	stage3QuestManager->quest1Flag = true;*/

	//퀘스트 완료시, 체크표시 해주세요
	if (inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
		stage3QuestManager->isQuest1Clear = true;

	if (inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
		stage3QuestManager->quest2Flag = true;

	if (inputManager->IsKeyState(KEY::F3, KEY_STATE::TAP))
		stage3QuestManager->isQuest3Clear = true;

	if (inputManager->IsKeyState(KEY::F4, KEY_STATE::TAP))
		stage3QuestManager->isQuest4Clear = true;
	
	//퀘스트 완료시, 체크표시 해주세요
	if (stage3QuestManager->quest1Flag == 1)
		uiCheck1->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage3QuestManager->quest2Flag == 1)
		uiCheck2->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage3QuestManager->quest3Flag == 1)
		uiCheck3->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage3QuestManager->finalQuestFlag == 1)
		uiCheckFinal->GetComponent<DrawType>()->SetUIVisible(true);


	//final퀘스트 전에 컷씬 출력
	if (stage3QuestManager->finalQuestFlag == 0)
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
	if (stage3QuestManager->isStageClear == true && isStageOver == false)
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
			GameManager::GetInstance()->gmGraphics->ChaptuerScreen("Stage3");
			GameManager::GetInstance()->isStage3Clear = true;
			GameManager::GetInstance()->nowStage = 3;
			GameManager::GetInstance()->nowStageName = "Stage4";

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

void Stage3::DeleteLiveObject()
{
	this->uiSetting->Finalize();
	this->uiSetting2->Finalize();
	this->uiMenuClose->Finalize();
	this->uiMenuClose2->Finalize();
	this->uiMenuAlbum2->Finalize();
	this->uiMenuExit->Finalize();
	this->uiMenuExit2->Finalize();
	this->uiMenuGuide->Finalize();
	this->uiMenuGuide2->Finalize();

	delete this->uiSetting;
	delete this->uiSetting2;
	delete this->uiMenuClose;
	delete this->uiMenuClose2;
	delete this->uiMenuAlbum2;
	delete this->uiMenuExit;
	delete this->uiMenuExit2;
	delete this->uiMenuGuide;
	delete this->uiMenuGuide2;
}
