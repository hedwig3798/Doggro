#include "QuestManager.h"
#include "Animation.h"
#include "AudioManager.h"

QuestManager::QuestManager(int _stageNumber)
	: isQuest1Start(false)
	, isQuest2Start(false)
	, isQuest3Start(false)
	, isQuest4Start(false)
	, isQuest5Start(false)
	, isFinalQuestStart(false)
	, isQuest1Clear(false)
	, isQuest2Clear(false)
	, isQuest3Clear(false)
	, isQuest4Clear(false)
	, isQuest5Clear(false)
	, isFianlQuestClear(false)
	, quest1Flag(0)
	, quest2Flag(0)
	, quest3Flag(0)
	, quest4Flag(0)
	, quest5Flag(0)
	, finalQuestFlag(-1)
	, stageNumber(_stageNumber)
	, timer1(0)
	, timer2(0)
	, timer3(0)
	, timer4(0)
	, timer5(0)
	, timerFinal(0)
	, isDollHiding(false)
	, isBallHiding(false)
	, isChewboneHiding(false)
	, isSojiHiding(0)
	, isStageClear(false)
{

}

QuestManager::~QuestManager()
{

}

/// <summary>
/// 씬에서 매 틱 마다 각 퀘스트가 실행이 될 수 있는 상태인지 확인해 
/// 실행이 될 수 있는 상태일때 그 퀘스트가 실행되면 클리어로 만들어준다.
/// </summary>
void QuestManager::Update(float _dt)
{
	///1번 퀘스트가 실행이 가능한 단계일 경우
	if (isQuest1Start == true && quest1Flag == 0)
	{
		//1스테이지의 1번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 1)
			isQuest1Clear = ClockBark();

		//2스테이지의 1번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 2)
			isQuest1Clear = BowlPut();

		//3스테이지의 1번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 3)
			isQuest1Clear = BedSmell();

		//4스테이지의 1번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 4)
		{
			if (isBiting == true)
				startMiniGame = true;

		}
			
	}

	///2번 퀘스트가 실행이 가능한 단계일 경우
	if (isQuest2Start == true && quest2Flag == 0)
	{
		//1스테이지의 2번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 1)
			isQuest2Clear = DeskUp(_dt);

		//2스테이지의 2번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 2)
			isQuest2Clear = LeashPut();

		//4스테이지의 2번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 4)
			isQuest2Clear = ManWakeup();

	}

	//3스테이지의 2번 퀘스트가 실행될 수 있는 상태이다.
	if (stageNumber == 3)
		isQuest2Clear = ObjectHiding();

	///3번 퀘스트가 실행이 가능한 단계일 경우
	if (isQuest3Start == true && quest3Flag == 0)
	{
		//1스테이지의 3번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 1)
			isQuest3Clear = CupDown(_dt);


		//2스테이지의 3번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 2)
			isQuest3Clear = ShoseSmell();

		//3스테이지의 3번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 3)
			isQuest3Clear = ClothSmell();

		//4스테이지의 3번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 4)
			isQuest3Clear = SayGoodBye();

	}

	///4번 퀘스트가 실행이 가능한 단계일 경우
	if (isQuest4Start == true && quest4Flag == 0)
	{
		//1스테이지의 4번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 1)
			isQuest4Clear = ChewBonePut();
		//2스테이지의 4번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 2)
			isQuest4Clear = DoorBark();
	}

	///5번 퀘스트가 실행이 가능한 단계일 경우
	if (isQuest5Start == true && quest5Flag == 0)
	{
		//2스테이지의 5번 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 2)
			isQuest5Clear = CalanderBite();
	}
	///Final 퀘스트가 실행이 가능한 단계인 경우
	if (isFinalQuestStart == true && finalQuestFlag == 0)
	{
		//1스테이지의 final 퀘스트가 실행될 수 있는 상태이다
		if (stageNumber == 1)
		{
			if (isBiting == true || isHoldBiting == true)
			{
				dogAni->UpdateDogState(true);
				isFianlQuestClear = RopeHolding(_dt);
			}
		}
		
		//3스테이지의 final 퀘스트가 실행될 수 있는 상태이다.
		if (stageNumber == 3)
			isFianlQuestClear = ClothSleep(_dt);

	}
	//2스테이지의 final 퀘스트가 실행될 수 있는 상태이다.
	if (finalQuestFlag == 0)
	{
		if (stageNumber == 2)
			isFianlQuestClear = SojuHiding();
	}
	

	///퀘스트가 클리어 됬을 경우, 플래그를 업데이트 시켜준다.
	if (isQuest1Clear == true)
	{
		quest1Flag = 1;
		timer1 = 0.f;
	}

	if (isQuest2Clear == true)
	{
		quest2Flag = 1;
		timer2 = 0.f;
	}

	if (isQuest3Clear == true)
	{
		quest3Flag = 1;
		timer3 = 0.f;
	}

	if (isQuest4Clear == true)
	{
		quest4Flag = 1;
		timer4 = 0.f;
	}

	if (isQuest5Clear == true)
	{
		quest5Flag = 1;
		timer5 = 0.f;
	}

	if (isFianlQuestClear == true)
	{
		finalQuestFlag = 1;
		timerFinal = 0.f;
	}

		
	///모든 퀘스트가 클리어 되어서 Final 퀘스트가 등장.
	//stage1 : 4개
	if (stageNumber == 1 && finalQuestFlag != 1)
	{
		if (quest1Flag == 1 && quest2Flag == 1 && quest3Flag == 1 && quest4Flag == 1)
			finalQuestFlag = 0; //퀘스트 활성화
	}
	//stage2 : 5개
	if (stageNumber == 2 && finalQuestFlag != 1)
	{
		if (quest1Flag == 1 && quest2Flag == 1 && quest3Flag == 1 && quest4Flag == 1 && quest5Flag == 1)
			finalQuestFlag = 0; //퀘스트 활성화
	}
	//stage3 : 3개
	if (stageNumber == 3 && finalQuestFlag != 1)
	{
		if (quest1Flag == 1 && quest2Flag == 1 && quest3Flag == 1)
			finalQuestFlag = 0; //퀘스트 활성화
	}

	//모든 퀘스트가 클리어됨
	if (finalQuestFlag == 1)
	{
		isStageClear = true;
	}
}

/// <summary>
/// 강아지의 상태를 업데이트 해주는 함수
/// 강아지 FSM에서 불릴 예정이다.
/// </summary>
/// <param name="_isBark">isBark</param>
void QuestManager::StateUpdate(bool _isBark, bool _isSmell, bool _isBiting, bool _isHoldBiting, bool _isSleeping, bool _isRopeBite)
{
	//짖기 상태가 아직 없는 관계로 일단 냄새로 대체
	isBark = _isBark;
	isSmell = _isSmell;
	isBiting = _isBiting;
	isHoldBiting = _isHoldBiting;
	isSleeping = _isSleeping;
	isRopeBite = _isRopeBite;
}

void QuestManager::HeightUpdate(float _dogHeight)
{
	dogHeight = _dogHeight;
}

void QuestManager::HumanStateUpdate(int _stateMent)
{
	stateMent = _stateMent;
}

/// <summary>
/// stage1 Quest 1
/// 시계에 짖기
/// mark.1 30초는 무시하고 그냥 짖으면 클리어되게 만들어둠
/// </summary>
/// <returns></returns>
bool QuestManager::ClockBark()
{
	//강아지의 상태를 받아와야겟구만.
	if (isBark == true)
		return true;
	
	return false;
}

/// <summary>
/// stage1 Quest 2
/// 책상에 올라가기
/// mark.1 콜라이더가 애매한 관계로 침대에 올라가기로 만들어둠
/// </summary>
/// <returns></returns>
bool QuestManager::DeskUp(float _dt)
{
	//강아지의 y좌표가 일정 이상이고, 그 물체와 충돌해 있을 경우
	//근데 충돌만 됬다고 바로 클리어 하면 충돌한 상태에서 점프도 가능함.
	//충돌된 이후 3초이상? 하면 클리어?
	
	//일단 이 함수가 실행됬다는 것은 침대와 충돌하고 있다는 것이다.
	// 일정 높이 이상이면 타이머를 초기화 하지 않는다
	// 높이가 떨어지면 타이머 초기화.

	if (dogHeight > 110)
	{
		timer2 += _dt;

		if (timer2 >= 3)
			return true;
	}
	
	else
		timer2 = 0;

	return false;
}

/// <summary>
/// stage1 Quest3
/// 컵 떨구기
/// 바닥에 충돌 하고 2초 뒤에 성공!
/// </summary>
/// <param name="_dt"></param>
/// <returns></returns>
bool QuestManager::CupDown(float _dt)
{			
	return true;	
}

/// <summary>
/// Stage1 Quest4
/// 개껌 침대로 옮기기
/// 강아지 높이가 침대 이상이고 개껌이 침대랑 충돌할때 퀘스트 완료
/// </summary>
/// <returns></returns>
bool QuestManager::ChewBonePut()
{
	
	if (isChewbonePutting == true && dogHeight > 90)
	{
		return true;
	}
		
	else
		return false;
}

/// <summary>
/// Stage1 Quest final
/// 로프 끊기
/// 로프 근처로 간다. 문다. 당긴다(2초) 끝!
/// </summary>
/// <returns></returns>
bool QuestManager::RopeHolding(float _dt)
{
	AudioManager::GetInstance()->StopAllEffect();
	AudioManager::GetInstance()->PlayEffect(EFFECT::Rope);
	AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_SevenTeenFive_Walk);
	return true;
}

/// <summary>
/// Stage2 Quest1
/// 밥그릇 책상에 두기
/// </summary>
/// <returns></returns>
bool QuestManager::BowlPut()
{
	if (isBowlPutting == true && dogHeight > 120)
		return true;
	else
		return false;
}

/// <summary>
/// Stage2 Quest2
/// 목줄 신발장에 두기
/// </summary>
/// <returns></returns>
bool QuestManager::LeashPut()
{
	if (isLeashPutting == true)
		return true;
	else
		return false;
}


/// <summary>
/// Stage2 Quest3
/// 신발 냄새 맡기
/// 그냥 신발 근처가서 상호작용시 성공!
/// </summary>
/// <returns></returns>
bool QuestManager::ShoseSmell()
{
	//강아지의 상태를 받아와야겟구만.
	if (isSmell == true)
		return true;

	return false;
}

/// <summary>
/// Stage2 Quest4
/// 문에서 짖기
/// 문 근처에서 짖으면 성공
/// </summary>
/// <returns></returns>
bool QuestManager::DoorBark()
{
	if (isBark == true)
		return true;

	return false;
}

/// <summary>
/// Stage2 Quest5
/// 캘린더 뜯기
/// 캘린더 종이를 물면 성공
/// </summary>
/// <returns></returns>
bool QuestManager::CalanderBite()
{
	if (isCalenderPutting == true)
		return true;

	return false;
}

/// <summary>
/// Stage2 FinalQuest
/// 소주 숨기기
/// 소주 3개 숨기면 클리어
/// </summary>
/// <returns></returns>
bool QuestManager::SojuHiding()
{
	if (isSojiHiding >= 3)
		return true;
	
	return false;
}

/// <summary>
/// Stage3 Quest1
/// 침대 냄새 맡기
/// 침대 근처에서 상호작용시 성공
/// </summary>
/// <returns></returns>
bool QuestManager::BedSmell()
{
	if (isSmell == true)
		return true;
	
	return false;
}

/// <summary>
/// Stage3 Quest2
/// 물건 침대에 숨기기
/// 모든 물건이 다 숨겨지면 성공
/// </summary>
/// <returns></returns>
bool QuestManager::ObjectHiding()
{
	if(isDollHiding == true && isChewboneHiding == true)
		return true;

	return false;
}

/// <summary>
/// Stage3 Quest3
/// 옷에서 냄새 맡기
/// 옷 근처에서 상호작용시 성공
/// </summary>
/// <returns></returns>
bool QuestManager::ClothSmell()
{
	if (isSmell == true)
		return true;

	return false;
}

/// <summary>
/// Stage3 finalQuest
/// 옷 위에서 눕기
/// 강아지의 높이가 일정 이상이고, 눕기 상호작용으로 특정 시간 지나면 성공
/// </summary>
/// <param name="_dt"></param>
/// <returns></returns>
bool QuestManager::ClothSleep(float _dt)
{

	if (dogHeight > 50)
	{
		if (isSleeping == true)
		{
			timerFinal += _dt;

			if (timerFinal >= 10)
				return true;
		}		
	}
	else
	{
		timerFinal = 0;
		return false;
	}
}

/// <summary>
/// Stage4 Quest2
/// 강아지가 짖으면 남자 일어나고 퀘스트 클리어
/// 강아지가 부딪힌 이후 짖으면 클리어
/// </summary>
/// <returns></returns>
bool QuestManager::ManWakeup()
{
	if (isBark == true)
	{
		//사람 일어나는 애니메이션
		dogAni->SetHumanState(1);
		return true;
	}
	
	return false;
}

/// <summary>
/// Stage4 Quest3
/// 사람이 문에 도착하면 클리어.
/// </summary>
/// <returns></returns>
bool QuestManager::SayGoodBye()
{
	if(isManArrive == true)
		return true;
	
	return false;
}

