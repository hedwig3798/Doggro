#include "Stage2.h"

#include "Entity.h"
#include "Debug.h"
#include "DrawType.h"
#include "DogFSM.h"
#include "Transform.h"
#include "TestFloor.h"
#include "SphereCollider.h"
#include "CameraModule.h"
#include "ManagerSet.h"
#include "CollsionManager.h"
#include "IGraphicsEngine.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "LoadMapData.h"
#include "QuestManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "DrawType.h"

#include "Dog.h"
#include "DogSight.h"
#include "DogScript.h"

#include "Wall.h"
#include "Floor.h"
#include "BackgroundWall.h"
#include "BackgroundWindow.h"

#include "Soju.h"
#include "Leash.h"
#include "ShoesL.h"
#include "ShoesR.h"
#include "Slippers.h"
#include "ShelfLiving.h"
#include "Sofa.h"
#include "Pot.h"
#include "Cabinet.h"
#include "Calendar.h"
#include "CalenderPaper.h"
#include "DisplayCupBoard.h"
#include "Door.h"
#include "ShoeRack.h"
#include "Table.h"
#include "Bowl.h"

#include "Ball.h"
#include "BigBall.h"
#include "Doll.h"
#include "Chewbone.h"

#include "WallObject.h"
#include "Lighting.h"

#include "DisplayCupBoardCollider.h"
#include "TableCollider.h"
#include "WallCollider2Stage.h"
#include "WallCollider2Stage2.h"

#include "Button.h"
#include "UIObject.h"
#include "UIButton.h"
#include "ImagineCutScene.h"
#include "AudioManager.h"

Stage2::Stage2(std::string _name)
	: Scene(_name)
	, nockTimer(0)
	, sec(0)
	, cutSceneTimer(0)
	, zoomTimer(0)
	, isStageOver(false)
	, waitForSec(0)
{
	leashPosition.resize(3);
	bowlPosition.resize(3);

	shoeLPosition.resize(3);
	shoeRPosition.resize(3);

	soju1Position.resize(3);
	soju2Position.resize(3);
	soju3Position.resize(3);
}

Stage2::~Stage2()
{

}

void Stage2::Start()
{
	GameManager::GetInstance()->isStage1Clear = false;
	GameManager::GetInstance()->isStage2Clear = false;

	///맵 데이터 불러오는 부분
	objectManager = new LoadMapData(managerSet->GetGraphics());
	objectManager->LoadMapMesh("stage_2_bellydance_final.fbx");

	///퀘스트 메니저 생성
	stage2QuestManager = new QuestManager(2);

	///cutScene
	imagineCutScene = new ImagineCutScene("imagineCutScene2", managerSet, OBJECT_TYPE::UI, CUTSCENETYPE::STAGE2);
	AddGameObject(imagineCutScene);
	imagineCutScene->GetComponent<DrawType>()->SetUIVisible(false);

	///Background
	//wall
	Entity* wall = new Wall("wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall);
	Entity* wall2 = new WallCollider2Stage("wall2", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall2); 
	Entity* wall3 = new WallCollider2Stage2("wall3", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wall3);
	//floor
	Entity* floor = new Floor("floor", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(floor);
	Entity* backgroundWall = new BackgroundWall("stage2_background_wall", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWall);
	Entity* backgroundWindow = new BackgroundWindow("background_window", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(backgroundWindow);

	///Dog
	Entity* dogSight = new DogSight("DogSight", managerSet, OBJECT_TYPE::TILE, stage2QuestManager);
	AddGameObject(dogSight);
	Entity* playDog2 = new Dog("Dog", managerSet, OBJECT_TYPE::TILE, DogType::Stage2, objectManager, stage2QuestManager, dogSight, imagineCutScene);
	AddGameObject(playDog2);

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
	
	Vector3 shoesLVector = shoesL->GetComponent<Transform>()->GetPosition();
	shoeLPosition[0] = shoesLVector.x;
	shoeLPosition[1] = shoesLVector.y;
	shoeLPosition[2] = shoesLVector.z;

	//shoesR
	Entity* shoesR = new ShoesR("shoes_R", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(shoesR);
	
	Vector3 shoesRVector = shoesR->GetComponent<Transform>()->GetPosition();
	shoeRPosition[0] = shoesRVector.x;
	shoeRPosition[1] = shoesRVector.y;
	shoeRPosition[2] = shoesRVector.z;

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
	//Cabinet
	Entity* cabinet = new Cabinet("cabinet", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(cabinet);
	//Calendar
	Entity* calendar = new Calendar("calendar_rip", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(calendar);
	//Calendar Paper
	Entity* calendarPaper = new CalenderPaper("calendar_letter", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(calendarPaper);
	//DisplayCupBoard
	Entity* displayCupBoard = new DisplayCupBoard("display_cupboard", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(displayCupBoard);
	Entity* displayCupBoardCollider = new DisplayCupBoardCollider("display_cupboardCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(displayCupBoardCollider);
	//Table
	Entity* tableLiving = new Table("table", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(tableLiving);
	Entity* tableLivingCollider = new TableCollider("tableCollider", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(tableLivingCollider);
	//Doll
	Entity* doll = new Doll("doll", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(doll);
	//ChewBone
	Entity* chewbone = new Chewbone("chewbone", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(chewbone);
	//ball
	Entity* ball = new Ball("ball", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(ball);
	//bigball
	Entity* bigBall = new BigBall("bigball", managerSet, OBJECT_TYPE::TILE, objectManager, playDog2->GetComponent<DogScript>());
	AddGameObject(bigBall);
	//Leash
	Entity* leash = new Leash("leash", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(leash);

	Vector3 leashVector = leash->GetComponent<Transform>()->GetPosition();
	leashPosition[0] = leashVector.x;
	leashPosition[1] = leashVector.y;
	leashPosition[2] = leashVector.z;

	//Bowl
	Entity* bowl = new Bowl("bowl", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(bowl);

	Vector3 bowlVector = bowl->GetComponent<Transform>()->GetPosition();
	bowlPosition[0] = bowlVector.x;
	bowlPosition[1] = bowlVector.y;
	bowlPosition[2] = bowlVector.z;

	///soju
	Entity* soju1 = new Soju("01_soju", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(soju1);

	Vector3 soju1Vector = soju1->GetComponent<Transform>()->GetPosition();
	soju1Position[0] = soju1Vector.x;
	soju1Position[1] = soju1Vector.y;
	soju1Position[2] = soju1Vector.z;

	Entity* soju2 = new Soju("02_soju", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(soju2);

	Vector3 soju2Vector = soju2->GetComponent<Transform>()->GetPosition();
	soju2Position[0] = soju2Vector.x;
	soju2Position[1] = soju2Vector.y;
	soju2Position[2] = soju2Vector.z;

	Entity* soju3 = new Soju("03_soju", managerSet, OBJECT_TYPE::TILE, objectManager, stage2QuestManager, playDog2->GetComponent<DogScript>());
	AddGameObject(soju3);
	
	Vector3 soju3Vector = soju3->GetComponent<Transform>()->GetPosition();
	soju3Position[0] = soju3Vector.x;
	soju3Position[1] = soju3Vector.y;
	soju3Position[2] = soju3Vector.z;

	///NonInteration
	//wallObject
	Entity* wallObject = new WallObject("ornaments", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(wallObject);
	//wallObject
	Entity* lighting = new Lighting("lamp", managerSet, OBJECT_TYPE::TILE, objectManager);
	AddGameObject(lighting);

	///UI
	Entity* uiKeyGuide2 = new UIObject("KeyGuide2", managerSet, OBJECT_TYPE::UI, UITYPE::KEYGUIDE2);
	AddGameObject(uiKeyGuide2);
	uiKeyGuide2->GetComponent<DrawType>()->SetUIVisible(true);
	
	Entity* uiMissionPaper2 = new UIObject("MissionPaper2", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPER2);
	AddGameObject(uiMissionPaper2);
	uiMissionPaper2->GetComponent<DrawType>()->SetUIVisible(true);
	
	uiMissionPaperPiece = new UIObject("MissionPaperPiece", managerSet, OBJECT_TYPE::UI, UITYPE::MISSIONPAPERPIECE2);
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
	uiCheck1->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck1);
	uiCheck2 = new UIObject("Check2", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK2);
	uiCheck2->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck2);
	uiCheck3 = new UIObject("Check3", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK3);
	uiCheck3->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck3);
	uiCheck4 = new UIObject("Check4", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK4);
	uiCheck4->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck4);
	stage2QuestManager->quest4Flag = -1;
	uiCheck5 = new UIObject("Check5", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK5);
	uiCheck5->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheck5);
	uiCheckFinal = new UIObject("Check6", managerSet, OBJECT_TYPE::UI, UITYPE::CHECK6);
	uiCheckFinal->GetComponent<DrawType>()->SetUIVisible(false);
	AddGameObject(uiCheckFinal);

	AudioManager::GetInstance()->StopAllSound();
	AudioManager::GetInstance()->PlayBGM(BGM::STAGE2);
	AddGameObject(uiAlbumButton);
}

void Stage2::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();

	if (inputManager->IsKeyState(KEY::P, KEY_STATE::TAP))
	{
		GetGameObject("leash")->GetComponent<Transform>()->SetPosition(Vector3(leashPosition[0], leashPosition[1], leashPosition[2]));
		GetGameObject("bowl")->GetComponent<Transform>()->SetPosition(Vector3(bowlPosition[0], bowlPosition[1], bowlPosition[2]));
		GetGameObject("shoes_L")->GetComponent<Transform>()->SetPosition(Vector3(shoeLPosition[0], shoeLPosition[1], shoeLPosition[2]));
		GetGameObject("shoes_R")->GetComponent<Transform>()->SetPosition(Vector3(shoeRPosition[0], shoeRPosition[1], shoeRPosition[2]));
		GetGameObject("01_soju")->GetComponent<Transform>()->SetPosition(Vector3(soju1Position[0], soju1Position[1], soju1Position[2]));
		GetGameObject("02_soju")->GetComponent<Transform>()->SetPosition(Vector3(soju2Position[0], soju2Position[1], soju2Position[2]));
		GetGameObject("03_soju")->GetComponent<Transform>()->SetPosition(Vector3(soju3Position[0], soju3Position[1], soju3Position[2]));
	}

	if (inputManager->IsKeyState(KEY::L, KEY_STATE::TAP))
	{
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("Stage1");
	}

	if (inputManager->IsKeyState(KEY::M, KEY_STATE::TAP))
	{
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("Stage3");
	}

	///퀘스트를 위한 함수들
	
	///Quest1 30초 뒤에 퀘스트 시작.
	sec += _deltaTime;
	if (sec > 1)
	{
		nockTimer++;
		sec = 0;
	}

	if (nockTimer > 5 && stage2QuestManager->quest4Flag != 1)
	{
		stage2QuestManager->quest4Flag = 0;
		AudioManager::GetInstance()->PlayEffect(EFFECT::Knock);
	}
	stage2QuestManager->Update(0.03);

	///디버깅을 위한 퀘스트 완료
		//일단은 키
	if (inputManager->IsKeyState(KEY::F1, KEY_STATE::TAP))
		stage2QuestManager->isQuest1Clear = true;

	if (inputManager->IsKeyState(KEY::F2, KEY_STATE::TAP))
		stage2QuestManager->isQuest2Clear = true;

	if (inputManager->IsKeyState(KEY::F3, KEY_STATE::TAP))
		stage2QuestManager->isQuest3Clear = true;

	if (inputManager->IsKeyState(KEY::F4, KEY_STATE::TAP))
		stage2QuestManager->isQuest4Clear = true;
	
	if(inputManager->IsKeyState(KEY::F6, KEY_STATE::TAP))
		stage2QuestManager->isQuest5Clear = true;
	


	//퀘스트 완료시, 체크표시 해주세요
	if (stage2QuestManager->quest1Flag == 1)
		uiCheck1->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage2QuestManager->quest2Flag == 1)
		uiCheck2->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage2QuestManager->quest3Flag == 1)
		uiCheck3->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage2QuestManager->quest4Flag == 1)
		uiCheck4->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage2QuestManager->quest5Flag == 1)
		uiCheck5->GetComponent<DrawType>()->SetUIVisible(true);
	if (stage2QuestManager->finalQuestFlag == 1)
		uiCheckFinal->GetComponent<DrawType>()->SetUIVisible(true);
	
	///Final Quest 시작 (시작 전 컷씬 출력)
	if (stage2QuestManager->finalQuestFlag == 0)
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
	if (stage2QuestManager->isStageClear == true && isStageOver == false)
	{
		///줌인 넣어주세요!
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
			GameManager::GetInstance()->gmGraphics->ChaptuerScreen("Stage2");
			GameManager::GetInstance()->isStage2Clear = true;
			GameManager::GetInstance()->nowStage = 2;
			GameManager::GetInstance()->nowStageName = "Stage3";

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

void Stage2::DeleteLiveObject()
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
