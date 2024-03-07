#pragma once
#include "Scene.h"

class QuestManager;
class LoadMapData;
class InputManager;

class Stage4 : public Scene
{
public:
	Stage4(std::string _name);
	virtual ~Stage4();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;

public:
	QuestManager* stage4QuestManager;
	LoadMapData* objectManager;
	InputManager* inputManager;

	//미션 가려둘 친구들
	Entity* uiMissionPaperPiece1;
	Entity* uiMissionPaperPiece2;

	//컷씬으로 사용될 친구들

	//체크표시 할 친구들
	Entity* uiCheck1;
	Entity* uiCheck2;
	Entity* uiCheck3;
	Entity* uiCheck4;

	Entity* imagineCutScene;
	Entity* miniGame;
	Entity* startScene;
	Entity* endScene;

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

	//컷씬 넘기기를 위한 변수
	int currentScene;

	int currentStartCutScene;
	bool isStartSceneEnd;
	bool isEndSceneEnd;

	bool firstIn = false;
	float timerMan;
	bool whiteOnlyone;

	std::vector<float> humanPosition;
	std::vector<float> humanRotation;

	void DeleteLiveObject();
};

