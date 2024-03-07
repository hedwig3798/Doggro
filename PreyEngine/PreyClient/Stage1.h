#pragma once
#include "Scene.h"

class QuestManager;
class LoadMapData;
class AudioManager;

class Stage1 : public Scene
{
public:
	Stage1(std::string _name);
	virtual ~Stage1();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;

	void stageClear(int _questNumber);

public:
	QuestManager* stage1QuestManager;
	LoadMapData* objectManager;
	
	//체크표시 할 친구들
	Entity* uiCheck1;
	Entity* uiCheck2;
	Entity* uiCheck3;
	Entity* uiCheck4;
	Entity* uiCheckFinal;

	Entity* uiSoulInventory;
	Entity* uiSoulInventory2;

	Entity* imagineCutScene;
	Entity* uiMissionPaperPiece;
	Entity* startScene;
	Entity* souls;

	Entity* uiSetting;
	Entity* uiSetting2;
	Entity* uiMenuClose;
	Entity* uiMenuClose2;
	Entity* uiMenuAlbum;
	Entity* uiMenuAlbum2;
	Entity* uiMenuExit;
	Entity* uiMenuExit2;
	Entity* uiMenuGuide;
	Entity* uiMenuGuide2;

	float alarmTimer;
	float sec;
	float cutSceneTimer;
	float zoomTimer;

	bool isStageOver;
	float waitForSec;

	//컷씬 넘기기를 위한 변수
	int currentStartCutScene;
	bool isStartSceneEnd;

	//
	float popupTimer;
	float popupHeight;
	bool isUpDown;
	bool isUpdownEnd;

	// Object offset 초기화
	// Cup 초기 위치, 개껌 초기 위치
	std::vector<float> cupPosition;
	std::vector<float> chewbonePosition;

	void DeleteLiveObject();
};

