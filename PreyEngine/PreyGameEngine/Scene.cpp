#include "Scene.h"
#include "Entity.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "CollsionManager.h"

Scene::Scene(std::string _name)
	: sceneName(_name), isStop(false), entityVector{}, managerSet{}
{

}

void Scene::Intialize(ManagerSet* _managerSet)
{
	managerSet = _managerSet;
	managerSet->GetCollisionManager()->Initialize(managerSet);
	Start();
}

void Scene::SceneUpdate(float deltaTime)
{
	if (isStop) 
		return;
	
	Update(deltaTime);

	for (auto gameObject : entityVector)
	{
		gameObject->Update(deltaTime);
	}
}

void Scene::Render()
{
	managerSet->GetGraphics()->begineDraw();

	for (auto gameObject : entityVector)
	{
		gameObject->Render();
	}
	managerSet->GetGraphics()->endDraw();
}

void Scene::Finalize()
{
	// vector�� ��� �ִ� gameObject���� �����Ѵ�.
	for (auto gameObject : entityVector)
	{
		gameObject->Finalize();
		delete gameObject;
		gameObject = nullptr;
	}
	entityVector.clear();
}

void Scene::AddGameObject(Entity* _entity)
{
	entityVector.push_back(_entity);
}

Entity* Scene::GetGameObject(std::string _name)
{
	for (auto gameObject : entityVector)
	{
		// ���⼭ �̸��� ���ؼ� ã�� �ѱ���.
		if (gameObject->GetName() == _name)
		{
			return gameObject;
		}
	}
	return nullptr;
}

