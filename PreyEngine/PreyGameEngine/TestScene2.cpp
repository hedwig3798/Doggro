#include "TestScene2.h"

#include "Move.h"
#include "Entity.h"
#include "Debug.h"
#include "ManagerSet.h"
#include "RenderType.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "IGraphicsEngine.h"
#include "CameraComponent.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "SphereCollider.h"
#include "TestFloor.h"

TestScene2::TestScene2(std::string _name)
	: Scene(_name)
{

}

TestScene2::~TestScene2()
{
}

void TestScene2::Start()
{
	ManagerSet* managerSet = GetManagerSet();

	Entity* testFloor = new Entity("TestFloor", GetManagerSet(), OBJECT_TYPE::TILE);
	testFloor->CreateComponent2<TestFloor>(testFloor, GetManagerSet()->GetCollisionManager());
	testFloor->CreateComponent<RenderType>(testFloor);
	testFloor->GetComponent<TestFloor>()->Start();
	testFloor->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBACKGROUND, managerSet->GetGraphics());


	Entity* player1 = new Entity("Player", GetManagerSet(), OBJECT_TYPE::TILE);
	player1->CreateComponent2<BoxCollider>(player1, GetManagerSet()->GetCollisionManager());
	player1->CreateComponent<RenderType>(player1);
	player1->CreateComponent<CameraComponent>(player1);
	player1->CreateComponent<Move>(player1);
	player1->CreateComponent<Debug>(player1);
	player1->GetComponent<BoxCollider>()->SetSize(Vector3(1.f, 1.f, 1.f));
	player1->GetComponent<BoxCollider>()->Start();
	player1->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBOX, GetManagerSet()->GetGraphics());

	Entity* player2 = new Entity("Player2", GetManagerSet(), OBJECT_TYPE::TILE);
	player2->CreateComponent2<BoxCollider>(player2, GetManagerSet()->GetCollisionManager());
	player2->CreateComponent<RenderType>(player2);
	player2->CreateComponent<CameraComponent>(player2);
	player2->CreateComponent<Move>(player2);
	player2->CreateComponent<Debug>(player2);
	player2->GetComponent<BoxCollider>()->SetSize(Vector3(1.f, 1.f, 1.f));
	player2->GetComponent<BoxCollider>()->Start();
	player2->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBOX, GetManagerSet()->GetGraphics());


	AddGameObject(testFloor);
	AddGameObject(player1);
	AddGameObject(player2);
	
}

void TestScene2::Update(float _deltaTime)
{
	InputManager* inputManager = GetManagerSet()->GetInputManager();

	// Scene Change Test
	if (inputManager->IsKeyState(KEY::O, KEY_STATE::TAP))
	{
		GetManagerSet()->GetSceneManager()->ChangeScene("TestScene1");
	}

	// Reset Scene Test
	if (inputManager->IsKeyState(KEY::R, KEY_STATE::TAP))
	{
		GetManagerSet()->GetSceneManager()->ResetScene("TestScene2");
	}
}
