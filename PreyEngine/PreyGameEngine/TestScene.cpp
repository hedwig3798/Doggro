#include "TestScene.h"
#include "Entity.h"
#include "BoxCollider.h"
#include "RenderType.h"
#include "Scene.h"
#include "ManagerSet.h"
#include "TestFloor.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Debug.h"
#include "SphereCollider.h"
#include "IGraphicsEngine.h"

/// TEST 중입니다.
#include "CameraComponent.h"
#include "InputManager.h"
#include "Move.h"
#include <vector>
#include "StaticCollider.h"
#include "FilterCollider.h"

TestScene::TestScene(std::string _name)
	: Scene(_name)
{

}

TestScene::~TestScene()
{

}

void TestScene::Start()
{
	ManagerSet* managerSet = GetManagerSet();

	Entity* testFloor = new Entity("TestFloor", GetManagerSet(), OBJECT_TYPE::TILE);
	testFloor->CreateComponent2<TestFloor>(testFloor, GetManagerSet()->GetCollisionManager());
	testFloor->CreateComponent<RenderType>(testFloor);
	testFloor->GetComponent<TestFloor>()->Start();
	testFloor->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBACKGROUND, managerSet->GetGraphics());

	testBox = new Entity("TestBox", GetManagerSet(), OBJECT_TYPE::TILE);
	testBox->CreateComponent2<BoxCollider>(testBox, GetManagerSet()->GetCollisionManager());
	testBox->CreateComponent<RenderType>(testBox);
	testBox->CreateComponent<Debug>(testBox);
	testBox->CreateComponent<Move>(testBox);
	testBox->GetComponent<BoxCollider>()->SetSize(Vector3(10.f, 10.f, 10.f));
	testBox->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
	testBox->GetComponent<BoxCollider>()->Start();
	testBox->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTDOG, managerSet->GetGraphics());

// 	Entity* testBox2 = new Entity("TestBox2", GetManagerSet(), OBJECT_TYPE::TILE);
// 	testBox2->CreateComponent2<SphereCollider>(testBox2, GetManagerSet()->GetCollisionManager());
// 	testBox2->CreateComponent<RenderType>(testBox2);
// 	//testBox2->CreateComponent<Debug>(testBox2);
// 	//testBox2->CreateComponent<Move>(testBox2);
// 	testBox2->GetComponent<SphereCollider>()->SetRadius(5.0f);
// 	testBox2->GetComponent<Transform>()->SetPosition(Vector3(20.0f, 5.0f, 0.0f));
// 	testBox2->GetComponent<SphereCollider>()->Start();
// 	testBox2->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTDOG, managerSet->GetGraphics());

	//Entity* testStatic = new Entity("TestStatic", GetManagerSet(), OBJECT_TYPE::TILE);
	//testStatic->CreateComponent2<StaticCollider>(testStatic, GetManagerSet()->GetCollisionManager());
	//testStatic->CreateComponent<RenderType>(testStatic);
	//testStatic->CreateComponent<Debug>(testStatic);
	////testStatic->CreateComponent<Move>(testBox);
	//testStatic->GetComponent<StaticCollider>()->SetSize(Vector3(10.f, 20.f, 10.f));
	//testStatic->GetComponent<Transform>()->SetPosition(Vector3(50.0f, 5.0f, 0.0f));
	//testStatic->GetComponent<StaticCollider>()->Start();
	//testStatic->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBOX, managerSet->GetGraphics());

// 	/*Entity* testBox3 = new Entity("TestBox3", GetManagerSet(), OBJECT_TYPE::TILE);
// 	testBox3->CreateComponent2<BoxCollider>(testBox3, GetManagerSet()->GetCollisionManager());
// 	testBox3->CreateComponent<RenderType>(testBox3);
// 	testBox3->GetComponent<Transform>()->SetPosition(Vector3(20.0f, 50.0f, 0.0f));
// 	testBox3->GetComponent<BoxCollider>()->Start();
// 	testBox3->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBOX, managerSet->GetGraphics());*/
// 
// 	/*Entity* testSphere = new Entity("Sphere", GetManagerSet(), OBJECT_TYPE::TILE);
// 	testSphere->CreateComponent2<SphereCollider>(testSphere, GetManagerSet()->GetCollisionManager());
// 	testSphere->CreateComponent<RenderType>(testSphere);
// 	testSphere->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 50.0f, 0.0f));
// 	testSphere->GetComponent<SphereCollider>()->Start();
// 	testSphere->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBOX, managerSet->GetGraphics());*/
// 
 	Entity* testBox3 = new Entity("TestBox3", GetManagerSet(), OBJECT_TYPE::TILE);
 	testBox3->CreateComponent2<FilterCollider>(testBox3, GetManagerSet()->GetCollisionManager());
 	testBox3->CreateComponent<RenderType>(testBox3);
	testBox3->GetComponent<FilterCollider>()->SetSize(Vector3(10.f, 10.f, 10.f));
 	testBox3->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
 	testBox3->GetComponent<FilterCollider>()->Start();
 	testBox3->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTBOX, managerSet->GetGraphics());
	
	Entity* testUI = new Entity("testUI", GetManagerSet(), OBJECT_TYPE::TILE);
	testUI->CreateComponent<RenderType>(testUI);
	testUI->GetComponent<RenderType>()->CreateRenderType(RENDER_TYPE::TESTUI, managerSet->GetGraphics());
	//testUI->GetComponent<Transform>()->SetPosition(Vector3(20.0f, 5.0f, 0.0f));

	AddGameObject(testFloor);
	AddGameObject(testBox);
	//AddGameObject(testBox2);
	AddGameObject(testBox3);
	AddGameObject(testUI);
	//AddGameObject(testStatic);
	//AddGameObject(testSphere);
}

void TestScene::Update(float _deltaTime)
{
	// Update에서 돌릴려면 object List에 있는 것을 가져와서 돌려야 하네.

 	InputManager* inputManager = GetManagerSet()->GetInputManager();
 
 	// Scene Change Test
 	if (inputManager->IsKeyState(KEY::O, KEY_STATE::TAP))
 	{
 		GetManagerSet()->GetSceneManager()->ChangeScene("TestScene2");
		return;
 	}
 
 	// Reset Scene Test
 	if (inputManager->IsKeyState(KEY::R, KEY_STATE::TAP))
 	{
 		GetManagerSet()->GetSceneManager()->ResetScene("TestScene1");
 	}
 
 	if (inputManager->IsKeyState(KEY::P, KEY_STATE::TAP))
 	{
 		GetManagerSet()->GetGraphics()->SetPixelateEffect();
 	}

	/*Vector3 translation = testBox->GetComponent<BoxCollider>()->GetTranslation();
	testBox->GetComponent<Transform>()->SetPosition(translation);*/
	//testBox->GetComponent<Transform>()->SetPosition(Vector3(testFloorMatrix._41, testFloorMatrix._42, testFloorMatrix._43));

	//testBox->GetComponent<Transform>()->AddPosition(Vector3(0.0f, -0.01f, 0.0f));
}


