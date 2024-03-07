#include "MainScene.h"

#include "DrawType.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIObject.h"
#include "Button.h"
#include "AudioManager.h"
#include "UIButton.h"
#include "GameManager.h"

MainScene::MainScene(std::string _name)
	:Scene(_name)
{
	
}

MainScene::~MainScene()
{

}

void MainScene::Start()
{
	GameManager::GetInstance()->isStage1Clear = false;
	GameManager::GetInstance()->isStage2Clear = false;
	GameManager::GetInstance()->isStage3Clear = false;
	GameManager::GetInstance()->isStage4Clear = false;


	Entity* title = new UIObject("Title", managerSet, OBJECT_TYPE::TILE, UITYPE::TITLE);
	Entity* titleContract = new UIObject("TitleContract", managerSet, OBJECT_TYPE::BACKGROUND, UITYPE::TITLECONTRACT);
	titleStart = new UIObject("Start", managerSet, OBJECT_TYPE::TILE, UITYPE::TITLESTART);
	titleStart2 = new UIObject("Start2", managerSet, OBJECT_TYPE::TILE, UITYPE::TITLESTART2);
	titleExit = new UIObject("Exit", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::EXIT_BUTTON);
	titleExit2 = new UIObject("Exit2", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::EXIT_BUTTON2);
	titleCredit = new UIObject("Credit", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::CREDITBUTTON);
	titleCredit2 = new UIObject("Credit2", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::CREDITBUTTON2);
	stamp = new UIObject("Stamp", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::STAMP);
	Entity* credit = new UIObject("Credit", managerSet, OBJECT_TYPE::FRONT_UI, UITYPE::CREDIT);

	titleStart->GetComponent<DrawType>()->SetUIVisible(true);
	titleExit->GetComponent<DrawType>()->SetUIVisible(true);
	titleCredit->GetComponent<DrawType>()->SetUIVisible(true);
	credit->GetComponent<DrawType>()->SetUIVisible(false);

	Entity* uiStartButton = new UIButton("StartButton", managerSet, OBJECT_TYPE::UI);
	uiStartButton->CreateComponent<Button>(uiStartButton);
	uiStartButton->GetComponent<Button>()->SetEnable();
	uiStartButton->GetComponent<Button>()->SetImage(0, titleStart->GetComponent<DrawType>());
	uiStartButton->GetComponent<Button>()->SetImage(1, titleStart2->GetComponent<DrawType>());
	uiStartButton->GetComponent<Button>()->SetImage(2, titleStart2->GetComponent<DrawType>());
	uiStartButton->GetComponent<Button>()->SetImage(3, stamp->GetComponent<DrawType>());
	uiStartButton->GetComponent<Button>()->SetButtonPos(RECT{ 970,150,1271,18 });
	uiStartButton->GetComponent<Button>()->SetOnHover([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		});
	uiStartButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("stageSelect");
		});

	Entity* uiExitButton = new UIButton("ExitButton", managerSet, OBJECT_TYPE::UI);
	uiExitButton->CreateComponent<Button>(uiExitButton);
	uiExitButton->GetComponent<Button>()->SetEnable();
	uiExitButton->GetComponent<Button>()->SetImage(0, titleExit->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetImage(1, titleExit2->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetImage(2, titleExit->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetImage(3, titleExit->GetComponent<DrawType>());
	uiExitButton->GetComponent<Button>()->SetButtonPos(RECT{ 1785,1080,1917,954 });
	uiExitButton->GetComponent<Button>()->SetOnHover([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		});
	uiExitButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		PostQuitMessage(0);
		});

	Entity* uiCreditButton = new UIButton("CreditButton", managerSet, OBJECT_TYPE::UI);
	uiCreditButton->CreateComponent<Button>(uiCreditButton);
	uiCreditButton->GetComponent<Button>()->SetEnable();
	uiCreditButton->GetComponent<Button>()->SetImage(0, titleCredit->GetComponent<DrawType>());
	uiCreditButton->GetComponent<Button>()->SetImage(1, titleCredit2->GetComponent<DrawType>());
	uiCreditButton->GetComponent<Button>()->SetImage(2, titleCredit->GetComponent<DrawType>());
	uiCreditButton->GetComponent<Button>()->SetImage(3, titleCredit->GetComponent<DrawType>());
	uiCreditButton->GetComponent<Button>()->SetButtonPos(RECT{ 10,1080,142,954 });
	uiCreditButton->GetComponent<Button>()->SetOnClick([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		credit->GetComponent<DrawType>()->isUIVisible = !credit->GetComponent<DrawType>()->isUIVisible;
		//titleStart->GetComponent<DrawType>()->SetUIVisible(false);
		if (credit->GetComponent<DrawType>()->isUIVisible == true)
			titleStart->GetComponent<DrawType>()->SetUIVisible(false);
		else
			titleStart->GetComponent<DrawType>()->SetUIVisible(true);
		});
	uiCreditButton->GetComponent<Button>()->SetOnHover([=]() {
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
		});


	AddGameObject(title);
	AddGameObject(titleContract);
	AddGameObject(uiExitButton);
	AddGameObject(uiCreditButton);
	AddGameObject(credit);
	AddGameObject(uiStartButton);

	AudioManager::GetInstance()->StopAllSound();
	AudioManager::GetInstance()->PlayBGM(BGM::STAGE4);
}

void MainScene::Update(float deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();

	if (inputManager->IsKeyState(KEY::L, KEY_STATE::TAP))
	{
		DeleteLiveObject();
		managerSet->GetSceneManager()->ChangeScene("Stage1");
	}

	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
	{
		AudioManager::GetInstance()->StopEffect(EFFECT::Click);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Click);
	}

	/*if (titleContract->GetComponent<DrawType>()->contractUp <= 590.f)
	{
		titleContract->GetComponent<DrawType>()->contractUp++;
	}*/
}

void MainScene::DeleteLiveObject()
{
	this->titleStart->Finalize();
	this->titleStart2->Finalize();
	this->titleExit->Finalize();
	this->titleExit2->Finalize();
	this->titleCredit->Finalize();
	this->titleCredit2->Finalize();
	this->stamp->Finalize();

	delete this->titleStart;
	delete this->titleStart2;
	delete this->titleExit;
	delete this->titleExit2;
	delete this->titleCredit;
	delete this->titleCredit2;
	delete this->stamp;
}
