#pragma once
#include "Scene.h"

/// <summary>
/// 스테이지 선택 창.
/// 어떤 때 이든 게임이 클리어가 된다면 스테이지 선택창으로 오게 된다.
/// </summary>

class ManagerSet;

class StageSelect : public Scene
{
public:
	StageSelect(std::string _name);
	virtual ~StageSelect();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;

public:
	Entity* selectAlbum;

	int currentAlbumNumber;

	float blink;
	float stageChangeTimer;
	
	bool isEffectOn;


};

