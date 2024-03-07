#pragma once
/// <summary>
/// ����Ʈ�� ����ϰ� �� ģ���̴�. 
/// Script���� ���� �޾Ƽ� ����Ʈ �ϷḦ Ȯ���� ����.
/// �� ������������ Ư�� ����Ʈ�� �Ϸ��ϸ� Ư�� ���� ��ȯ���ش�.
/// ��ȯ ���� ���� �� ������Ʈ���� �Ͼ�� �� ���� ó�����ش�. 
/// -> UI üũǥ�� ������Ʈ, ���� ����Ʈ �����
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

	/// Stage2(��)
	bool BowlPut();					//quest1
	bool LeashPut();				//quest2
	bool ShoseSmell();				//quest3
	bool DoorBark();				//quest4
	bool CalanderBite();			//quest5
	bool SojuHiding();				//finalQuest

	/// Stage3 (��)
	bool BedSmell();				//quest1
	bool ObjectHiding();			//quest2
	bool ClothSmell();				//quest3
	bool ClothSleep(float _dt);		//finalQuest;

	/// Stage4
	//bool miniGame();				//quest1
	bool ManWakeup();				//quest2
	bool SayGoodBye();				//quest3

public:
	//���� �� ������������
	int stageNumber;

	//������ ����
	bool isBark;
	bool isSmell;
	bool isBiting;
	bool isHoldBiting;
	bool isSleeping;
	bool isRopeBite;
	bool isGhost;
	float dogHeight;
	

	// ��� ����
	int stateMent;

	//�� ����Ʈ���� ���� ������ �������� Ȯ���ϴ� ����
	bool isQuest1Start;
	bool isQuest2Start;
	bool isQuest3Start;
	bool isQuest4Start;
	bool isQuest5Start;
	bool isFinalQuestStart;

	//�� ����Ʈ�� Ŭ���� ����� Ȯ���ϴ� ����
	bool isQuest1Clear;
	bool isQuest2Clear;
	bool isQuest3Clear;
	bool isQuest4Clear;
	bool isQuest5Clear;
	bool isFianlQuestClear;

	//����Ʈ �� Ŭ���� �÷���
	//0 ->  ����Ʈ Ȱ��ȭ
	//1 ->  ����Ʈ Ŭ����
	//-1 -> ����Ʈ ��Ȱ��ȭ
	int quest1Flag;
	int quest2Flag;
	int quest3Flag;
	int quest4Flag;
	int quest5Flag;
	int finalQuestFlag;

	//��� ����Ʈ �Ϸ�
	bool isStageClear;

	//stage1 Qeust4�� ���� ����
	bool isChewbonePutting;

	//stage2 Quest1�� ���� ����
	bool isBowlPutting;
	//stage2 Quest2�� ���� ����
	bool isLeashPutting;
	//stage2 Quest5�� ���� ����
	bool isCalenderPutting;
	//stage2 FinalQuest�� ���� ����
	int isSojiHiding;

	//stage3 Quest2�� ���� ����
	bool isDollHiding;
	bool isBallHiding;
	bool isChewboneHiding;

	//stage4 Quest1�� ���� ����
	bool startMiniGame;

	//stage4 Quest3�� ���� ����
	bool isManArrive;

//����Ʈ�� �ʿ��� ������ ����
private:
	float timer1;
	float timer2;
	float timer3;
	float timer4;
	float timer5;
	float timerFinal;

};

