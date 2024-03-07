#pragma once
#include "Scene.h"

/// <summary>
/// �������� ���� â.
/// � �� �̵� ������ Ŭ��� �ȴٸ� �������� ����â���� ���� �ȴ�.
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

