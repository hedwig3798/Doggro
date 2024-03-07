#include "CutScene.h"
#include "ManagerSet.h"
#include "Webtoon.h"
#include "InputManager.h"
#include "SceneManager.h"

CutScene::CutScene(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type)
	: Entity(_name, _managerSet, _type)
{
	managerSet = _managerSet;
	CreateComponent<Webtoon>(this);
	//StartScene();
	IndexLoad(++currentIndex);
}
CutScene::~CutScene()
{

}

void CutScene::StartScene()
{
	//IndexLoad(++currentIndex);
	//NextScene();
}

void CutScene::NextScene()
{
	//IndexLoad(++currentIndex);
}

void CutScene::IndexLoad(int _index)
{
	if (_index == 1)
	{
		GetComponent<Webtoon>()->CutSceneLoad(_index, managerSet->GetGraphics());
	}
	else if (_index == 2)
	{
		GetComponent<Webtoon>()->CutSceneLoad(_index, managerSet->GetGraphics());
	}
	else if (_index == 3)
	{
		GetComponent<Webtoon>()->CutSceneLoad(_index, managerSet->GetGraphics());
	}
}
