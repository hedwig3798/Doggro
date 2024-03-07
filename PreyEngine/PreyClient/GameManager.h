#pragma once
#include <string>

#include "Singleton.h"


class IGraphicsEngine;

/// <summary>
/// 스테이지를 관리하게될 친구
/// 스테이지 별 상태관리도 합니다.
/// 따라서 싱글톤.
/// </summary>
class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();

	void Initialize(IGraphicsEngine* _iGraphicsEngine);
public:
	//캡처된 사진을 저장하기 위해 IgraphicEngine이 필요하네유
	IGraphicsEngine* gmGraphics;
	
	//각 스테이지 별 상태 체크를 위한 변수
	bool isStage1Clear;
	bool isStage2Clear;
	bool isStage3Clear;
	bool isStage4Clear;

	//현재 무슨 앨범을 보여줄지 알려주는 변수
	int nowStage;
	std::string nowStageName;

};

