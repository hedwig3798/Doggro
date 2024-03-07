#include "SceneManager.h"
#include "Scene.h"
#include <cassert>
#include "ManagerSet.h"
#include "CollsionManager.h"

SceneManager::SceneManager()
	: currentScene(), managerSet{}, sceneMap{}, changeSceneMap{}
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::Initalize(ManagerSet* _managerSet)
{
	managerSet = _managerSet;
	currentScene->Intialize(_managerSet);
}

void SceneManager::Update(float deltaTime)
{
	currentScene->SceneUpdate(deltaTime);
}

void SceneManager::Render()
{
	currentScene->Render();
}

void SceneManager::Finalize()
{
	for (auto& e : sceneMap)
	{
		e.second->Finalize();
		delete e.second;
	}
	sceneMap.clear();
}

/// <summary>
/// 씬을 교체한다.
/// 전에 하고 있던 scene은 저장하자.
/// </summary>
/// <param name="_name">바꾸고 싶은 Scene의 이름</param>
void SceneManager::ChangeScene(std::string _name)
{
	// 현재 Scene Name과 바꾸고자 하는 Scene Name이 같다면 그냥 return 한다.

	// 1. currentScene의 이름을 받아온다.
	std::string preSceneName = currentScene->GetSceneName();

	// 2. 현재 scene을 찾고
	auto preSceneIter = changeSceneMap.find(preSceneName);

	// 현재 Scene을 changeSceneMap에 저장하자.
	if (preSceneIter != changeSceneMap.end())
	{
		preSceneIter->second = currentScene;
	}

	// 3. 그 다음 바꾸고 싶은 scene으로 간다. 없으면 경고창을 내준다.
	auto currentSceneIter = changeSceneMap.find(_name);

	if (currentSceneIter != changeSceneMap.end())
	{
		// 4. 현재 Scene에 있던 Object 들을 정리하고 넘어가자.
		// endRender를 다 하고 그 다음에 scene을 정리해야 한다.
		currentScene->Finalize();
		currentScene->GetManagerSet()->GetCollisionManager()->Finalize();
		currentScene = currentSceneIter->second;
		currentScene->Intialize(managerSet);
		changeScene = true;
	}
	else assert(false && "Does not exist Scene");
}

/// <summary>
/// 씬을 초기화한다.
/// </summary>
/// <param name="_name">초기화할 Scene의 이름</param>
void SceneManager::ResetScene(std::string _name)
{
	auto iter = sceneMap.find(_name);

	if (iter != sceneMap.end())
	{
		currentScene->Finalize();
		currentScene->GetManagerSet()->GetCollisionManager()->Finalize();
		currentScene = iter->second;
		currentScene->Intialize(managerSet);
	}
	else assert(false && "Does not exist Scene");
}

/// <summary>
/// 초기에 만든 Scene을 가지고 Map에 넣는다.
/// </summary>
void SceneManager::CreateScene(Scene* _scene)
{
	sceneMap.insert(std::make_pair(_scene->GetSceneName(), _scene));
	changeSceneMap.insert(std::make_pair(_scene->GetSceneName(), _scene));
}

Scene* SceneManager::GetScene(std::string _name)
{
	// map 돌면서 찾다가
	auto iter = sceneMap.find(_name);

	// 마지막에 도달하면 nullptr, 찾았으면 Scene을 뱉는다.
	if (iter != sceneMap.end())
	{
		return iter->second;
	}
	else return nullptr;
}

void SceneManager::UnloadScene()
{
	// Scene 안에 들어가서 삭제하고 sceneMap을 clear 하는 것이 맞겠다.
	// Scene Map을 순회해서 전부 삭제 하도록 할까?

	currentScene->Finalize();

}
