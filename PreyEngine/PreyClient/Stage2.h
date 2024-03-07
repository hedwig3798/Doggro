#pragma once
#include "Scene.h"

class QuestManager;
class LoadMapData;

class Stage2 : public Scene
{
public:
	Stage2(std::string _name);
	virtual ~Stage2();

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;

public:
	QuestManager* stage2QuestManager;
	LoadMapData* objectManager;

	//체크표시 할 친구들
	Entity* uiCheck1;
	Entity* uiCheck2;
	Entity* uiCheck3;
	Entity* uiCheck4;
	Entity* uiCheck5;
	Entity* uiCheckFinal;

	Entity* uiMissionPaperPiece;
	Entity* imagineCutScene;


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

	float nockTimer;
	float sec;
	float cutSceneTimer;
	float zoomTimer;

	bool isStageOver;
	float waitForSec;

	// 목줄, 밥그릇, 소주 1,2,3 초기 위치
	std::vector<float> leashPosition;
	std::vector<float> bowlPosition;

	std::vector<float> shoeLPosition;
	std::vector<float> shoeRPosition;

	std::vector<float> soju1Position;
	std::vector<float> soju2Position;
	std::vector<float> soju3Position;

	void DeleteLiveObject();
};

