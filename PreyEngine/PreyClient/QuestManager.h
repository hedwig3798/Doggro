#pragma once
/// <summary>
/// 퀘스트를 담당하게 될 친구이다. 
/// Script에서 값을 받아서 퀘스트 완료를 확인할 예정.
/// 각 스테이지마다 특정 퀘스트를 완료하면 특정 값을 반환해준다.
/// 반환 값에 따라 씬 업데이트에서 일어나야 될 일을 처리해준다. 
/// -> UI 체크표시 업데이트, 최종 퀘스트 생기기
/// </summary>

class Animation;

class QuestManager
{
public:
	QuestManager(int _stageNumber);
	~QuestManager();

	void Update(float _dt);
	void StateUpdate(bool _isBark, bool _isSmell, bool _isBiting, bool _isHoldBiting, bool _isSleeping, bool _isRopeBite);
	void HeightUpdate(float _dogHeight);
	void HumanStateUpdate(int _stateMent);

	Animation* dogAni;
	void GetDogAnimation(Animation* _dogAni) { dogAni = _dogAni; }

public:
	/// Stage1
	bool ClockBark();				//quest1
	bool DeskUp(float _dt);			//quest2
	bool CupDown(float _dt);		//quest3
	bool ChewBonePut();				//quest4
	bool RopeHolding(float _dt);	//finalQuest

	/// Stage2(완)
	bool BowlPut();					//quest1
	bool LeashPut();				//quest2
	bool ShoseSmell();				//quest3
	bool DoorBark();				//quest4
	bool CalanderBite();			//quest5
	bool SojuHiding();				//finalQuest

	/// Stage3 (완)
	bool BedSmell();				//quest1
	bool ObjectHiding();			//quest2
	bool ClothSmell();				//quest3
	bool ClothSleep(float _dt);		//finalQuest;

	/// Stage4
	//bool miniGame();				//quest1
	bool ManWakeup();				//quest2
	bool SayGoodBye();				//quest3

public:
	//현재 몇 스테이지인지
	int stageNumber;

	//강아지 상태
	bool isBark;
	bool isSmell;
	bool isBiting;
	bool isHoldBiting;
	bool isSleeping;
	bool isRopeBite;
	bool isGhost;
	float dogHeight;
	

	// 사람 상태
	int stateMent;

	//각 퀘스트별로 실행 가능한 상태인지 확인하는 변수
	bool isQuest1Start;
	bool isQuest2Start;
	bool isQuest3Start;
	bool isQuest4Start;
	bool isQuest5Start;
	bool isFinalQuestStart;

	//각 퀘스트가 클리어 됬는지 확인하는 변수
	bool isQuest1Clear;
	bool isQuest2Clear;
	bool isQuest3Clear;
	bool isQuest4Clear;
	bool isQuest5Clear;
	bool isFianlQuestClear;

	//퀘스트 별 클리어 플래그
	//0 ->  퀘스트 활성화
	//1 ->  퀘스트 클리어
	//-1 -> 퀘스트 비활성화
	int quest1Flag;
	int quest2Flag;
	int quest3Flag;
	int quest4Flag;
	int quest5Flag;
	int finalQuestFlag;

	//모든 퀘스트 완료
	bool isStageClear;

	//stage1 Qeust4를 위한 변수
	bool isChewbonePutting;

	//stage2 Quest1를 위한 변수
	bool isBowlPutting;
	//stage2 Quest2를 위한 변수
	bool isLeashPutting;
	//stage2 Quest5를 위한 변수
	bool isCalenderPutting;
	//stage2 FinalQuest를 위한 변수
	int isSojiHiding;

	//stage3 Quest2를 위한 변수
	bool isDollHiding;
	bool isBallHiding;
	bool isChewboneHiding;

	//stage4 Quest1을 위한 변수
	bool startMiniGame;

	//stage4 Quest3을 위한 변수
	bool isManArrive;

//퀘스트에 필요한 변수들 저장
private:
	float timer1;
	float timer2;
	float timer3;
	float timer4;
	float timer5;
	float timerFinal;

};

