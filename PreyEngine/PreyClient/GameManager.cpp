#include "GameManager.h"
#include "IGraphicsEngine.h"

GameManager::GameManager()
	: isStage1Clear(false)
	, isStage2Clear(false)
	, isStage3Clear(false)
	, isStage4Clear(false)
	, nowStage(0)
	, nowStageName("Stage1")
{

}

GameManager::~GameManager()
{

}

void GameManager::Initialize(IGraphicsEngine* _iGraphicsEngine)
{
	gmGraphics = _iGraphicsEngine;
}
