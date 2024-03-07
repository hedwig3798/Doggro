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
/// ������ �� ƽ ���� �� ����Ʈ�� ������ �� �� �ִ� �������� Ȯ���� 
/// ������ �� �� �ִ� �����϶� �� ����Ʈ�� ����Ǹ� Ŭ����� ������ش�.
/// </summary>
void QuestManager::Update(float _dt)
{
	///1�� ����Ʈ�� ������ ������ �ܰ��� ���
	if (isQuest1Start == true && quest1Flag == 0)
	{
		//1���������� 1�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 1)
			isQuest1Clear = ClockBark();

		//2���������� 1�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 2)
			isQuest1Clear = BowlPut();

		//3���������� 1�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 3)
			isQuest1Clear = BedSmell();

		//4���������� 1�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 4)
		{
			if (isBiting == true)
				startMiniGame = true;

		}
			
	}

	///2�� ����Ʈ�� ������ ������ �ܰ��� ���
	if (isQuest2Start == true && quest2Flag == 0)
	{
		//1���������� 2�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 1)
			isQuest2Clear = DeskUp(_dt);

		//2���������� 2�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 2)
			isQuest2Clear = LeashPut();

		//4���������� 2�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 4)
			isQuest2Clear = ManWakeup();

	}

	//3���������� 2�� ����Ʈ�� ����� �� �ִ� �����̴�.
	if (stageNumber == 3)
		isQuest2Clear = ObjectHiding();

	///3�� ����Ʈ�� ������ ������ �ܰ��� ���
	if (isQuest3Start == true && quest3Flag == 0)
	{
		//1���������� 3�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 1)
			isQuest3Clear = CupDown(_dt);


		//2���������� 3�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 2)
			isQuest3Clear = ShoseSmell();

		//3���������� 3�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 3)
			isQuest3Clear = ClothSmell();

		//4���������� 3�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 4)
			isQuest3Clear = SayGoodBye();

	}

	///4�� ����Ʈ�� ������ ������ �ܰ��� ���
	if (isQuest4Start == true && quest4Flag == 0)
	{
		//1���������� 4�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 1)
			isQuest4Clear = ChewBonePut();
		//2���������� 4�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 2)
			isQuest4Clear = DoorBark();
	}

	///5�� ����Ʈ�� ������ ������ �ܰ��� ���
	if (isQuest5Start == true && quest5Flag == 0)
	{
		//2���������� 5�� ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 2)
			isQuest5Clear = CalanderBite();
	}
	///Final ����Ʈ�� ������ ������ �ܰ��� ���
	if (isFinalQuestStart == true && finalQuestFlag == 0)
	{
		//1���������� final ����Ʈ�� ����� �� �ִ� �����̴�
		if (stageNumber == 1)
		{
			if (isBiting == true || isHoldBiting == true)
			{
				dogAni->UpdateDogState(true);
				isFianlQuestClear = RopeHolding(_dt);
			}
		}
		
		//3���������� final ����Ʈ�� ����� �� �ִ� �����̴�.
		if (stageNumber == 3)
			isFianlQuestClear = ClothSleep(_dt);

	}
	//2���������� final ����Ʈ�� ����� �� �ִ� �����̴�.
	if (finalQuestFlag == 0)
	{
		if (stageNumber == 2)
			isFianlQuestClear = SojuHiding();
	}
	

	///����Ʈ�� Ŭ���� ���� ���, �÷��׸� ������Ʈ �����ش�.
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

		
	///��� ����Ʈ�� Ŭ���� �Ǿ Final ����Ʈ�� ����.
	//stage1 : 4��
	if (stageNumber == 1 && finalQuestFlag != 1)
	{
		if (quest1Flag == 1 && quest2Flag == 1 && quest3Flag == 1 && quest4Flag == 1)
			finalQuestFlag = 0; //����Ʈ Ȱ��ȭ
	}
	//stage2 : 5��
	if (stageNumber == 2 && finalQuestFlag != 1)
	{
		if (quest1Flag == 1 && quest2Flag == 1 && quest3Flag == 1 && quest4Flag == 1 && quest5Flag == 1)
			finalQuestFlag = 0; //����Ʈ Ȱ��ȭ
	}
	//stage3 : 3��
	if (stageNumber == 3 && finalQuestFlag != 1)
	{
		if (quest1Flag == 1 && quest2Flag == 1 && quest3Flag == 1)
			finalQuestFlag = 0; //����Ʈ Ȱ��ȭ
	}

	//��� ����Ʈ�� Ŭ�����
	if (finalQuestFlag == 1)
	{
		isStageClear = true;
	}
}

/// <summary>
/// �������� ���¸� ������Ʈ ���ִ� �Լ�
/// ������ FSM���� �Ҹ� �����̴�.
/// </summary>
/// <param name="_isBark">isBark</param>
void QuestManager::StateUpdate(bool _isBark, bool _isSmell, bool _isBiting, bool _isHoldBiting, bool _isSleeping, bool _isRopeBite)
{
	//¢�� ���°� ���� ���� ����� �ϴ� ������ ��ü
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
/// �ð迡 ¢��
/// mark.1 30�ʴ� �����ϰ� �׳� ¢���� Ŭ����ǰ� ������
/// </summary>
/// <returns></returns>
bool QuestManager::ClockBark()
{
	//�������� ���¸� �޾ƿ;߰ٱ���.
	if (isBark == true)
		return true;
	
	return false;
}

/// <summary>
/// stage1 Quest 2
/// å�� �ö󰡱�
/// mark.1 �ݶ��̴��� �ָ��� ����� ħ�뿡 �ö󰡱�� ������
/// </summary>
/// <returns></returns>
bool QuestManager::DeskUp(float _dt)
{
	//�������� y��ǥ�� ���� �̻��̰�, �� ��ü�� �浹�� ���� ���
	//�ٵ� �浹�� ��ٰ� �ٷ� Ŭ���� �ϸ� �浹�� ���¿��� ������ ������.
	//�浹�� ���� 3���̻�? �ϸ� Ŭ����?
	
	//�ϴ� �� �Լ��� ������ٴ� ���� ħ��� �浹�ϰ� �ִٴ� ���̴�.
	// ���� ���� �̻��̸� Ÿ�̸Ӹ� �ʱ�ȭ ���� �ʴ´�
	// ���̰� �������� Ÿ�̸� �ʱ�ȭ.

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
/// �� ������
/// �ٴڿ� �浹 �ϰ� 2�� �ڿ� ����!
/// </summary>
/// <param name="_dt"></param>
/// <returns></returns>
bool QuestManager::CupDown(float _dt)
{			
	return true;	
}

/// <summary>
/// Stage1 Quest4
/// ���� ħ��� �ű��
/// ������ ���̰� ħ�� �̻��̰� ������ ħ��� �浹�Ҷ� ����Ʈ �Ϸ�
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
/// ���� ����
/// ���� ��ó�� ����. ����. ����(2��) ��!
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
/// ��׸� å�� �α�
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
/// ���� �Ź��忡 �α�
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
/// �Ź� ���� �ñ�
/// �׳� �Ź� ��ó���� ��ȣ�ۿ�� ����!
/// </summary>
/// <returns></returns>
bool QuestManager::ShoseSmell()
{
	//�������� ���¸� �޾ƿ;߰ٱ���.
	if (isSmell == true)
		return true;

	return false;
}

/// <summary>
/// Stage2 Quest4
/// ������ ¢��
/// �� ��ó���� ¢���� ����
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
/// Ķ���� ���
/// Ķ���� ���̸� ���� ����
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
/// ���� �����
/// ���� 3�� ����� Ŭ����
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
/// ħ�� ���� �ñ�
/// ħ�� ��ó���� ��ȣ�ۿ�� ����
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
/// ���� ħ�뿡 �����
/// ��� ������ �� �������� ����
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
/// �ʿ��� ���� �ñ�
/// �� ��ó���� ��ȣ�ۿ�� ����
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
/// �� ������ ����
/// �������� ���̰� ���� �̻��̰�, ���� ��ȣ�ۿ����� Ư�� �ð� ������ ����
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
/// �������� ¢���� ���� �Ͼ�� ����Ʈ Ŭ����
/// �������� �ε��� ���� ¢���� Ŭ����
/// </summary>
/// <returns></returns>
bool QuestManager::ManWakeup()
{
	if (isBark == true)
	{
		//��� �Ͼ�� �ִϸ��̼�
		dogAni->SetHumanState(1);
		return true;
	}
	
	return false;
}

/// <summary>
/// Stage4 Quest3
/// ����� ���� �����ϸ� Ŭ����.
/// </summary>
/// <returns></returns>
bool QuestManager::SayGoodBye()
{
	if(isManArrive == true)
		return true;
	
	return false;
}

