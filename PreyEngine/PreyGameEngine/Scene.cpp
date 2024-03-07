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
	// vector에 담겨 있는 gameObject들을 삭제한다.
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
		// 여기서 이름을 비교해서 찾고 넘기자.
		if (gameObject->GetName() == _name)
		{
			return gameObject;
		}
	}
	return nullptr;
}

