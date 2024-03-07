#pragma once
#include "Scene.h"

class QuestManager;
class LoadMapData;

class Stage3 :public Scene
{
public:
	Stage3(std::string _name);
	virtual ~Stage3();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;

public:
	QuestManager* stage3QuestManager;
	LoadMapData* objectManager;

	//üũǥ�� �� ģ����
	Entity* uiCheck1;
	Entity* uiCheck2;
	Entity* uiCheck3;
	Entity* uiCheckFinal;

	Entity* uiMissionPaperPiece;

	//�ƾ�
	Entity* imagineCutScene;

	Entity* uiSetting;
	Entity* uiSetting2;
	Entity* uiMenuClose;
	Entity* uiMenuClose2;
	Entity* uiMenuAlbum2;
	Entity* uiMenuExit;
	Entity* uiMenuExit2;
	Entity* uiMenuGuide;
	Entity* uiMenuGuide2;

	float cutSceneTimer;
	float zoomTimer;

	bool isStageOver;
	float waitForSec;

	// ���ٱ�, ����
	std::vector<float> chewBonePosition;
	std::vector<float> dollPosition;

	void DeleteLiveObject();
};

