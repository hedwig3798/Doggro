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
/// ���� ��ü�Ѵ�.
/// ���� �ϰ� �ִ� scene�� ��������.
/// </summary>
/// <param name="_name">�ٲٰ� ���� Scene�� �̸�</param>
void SceneManager::ChangeScene(std::string _name)
{
	// ���� Scene Name�� �ٲٰ��� �ϴ� Scene Name�� ���ٸ� �׳� return �Ѵ�.

	// 1. currentScene�� �̸��� �޾ƿ´�.
	std::string preSceneName = currentScene->GetSceneName();

	// 2. ���� scene�� ã��
	auto preSceneIter = changeSceneMap.find(preSceneName);

	// ���� Scene�� changeSceneMap�� ��������.
	if (preSceneIter != changeSceneMap.end())
	{
		preSceneIter->second = currentScene;
	}

	// 3. �� ���� �ٲٰ� ���� scene���� ����. ������ ���â�� ���ش�.
	auto currentSceneIter = changeSceneMap.find(_name);

	if (currentSceneIter != changeSceneMap.end())
	{
		// 4. ���� Scene�� �ִ� Object ���� �����ϰ� �Ѿ��.
		// endRender�� �� �ϰ� �� ������ scene�� �����ؾ� �Ѵ�.
		currentScene->Finalize();
		currentScene->GetManagerSet()->GetCollisionManager()->Finalize();
		currentScene = currentSceneIter->second;
		currentScene->Intialize(managerSet);
		changeScene = true;
	}
	else assert(false && "Does not exist Scene");
}

/// <summary>
/// ���� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <param name="_name">�ʱ�ȭ�� Scene�� �̸�</param>
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
/// �ʱ⿡ ���� Scene�� ������ Map�� �ִ´�.
/// </summary>
void SceneManager::CreateScene(Scene* _scene)
{
	sceneMap.insert(std::make_pair(_scene->GetSceneName(), _scene));
	changeSceneMap.insert(std::make_pair(_scene->GetSceneName(), _scene));
}

Scene* SceneManager::GetScene(std::string _name)
{
	// map ���鼭 ã�ٰ�
	auto iter = sceneMap.find(_name);

	// �������� �����ϸ� nullptr, ã������ Scene�� ��´�.
	if (iter != sceneMap.end())
	{
		return iter->second;
	}
	else return nullptr;
}

void SceneManager::UnloadScene()
{
	// Scene �ȿ� ���� �����ϰ� sceneMap�� clear �ϴ� ���� �°ڴ�.
	// Scene Map�� ��ȸ�ؼ� ���� ���� �ϵ��� �ұ�?

	currentScene->Finalize();

}
