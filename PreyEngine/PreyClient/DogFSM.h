#pragma once
#include "Component.h"
#include "SimpleMath.h"

class Animation;
class QuestManager;

/// <summary>
/// Entity를 조작할 수 있는 Component
/// </summary>
class DogFSM : public Component
{
public:
	DogFSM(Entity* _entity);
	virtual ~DogFSM();

	virtual void Update(float _deltaTime) override;

	std::vector<float> GetDirectSpeed() const { return directSpeed; }
	float GetSpeed() const { return speed; }
	
	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }
	void GetDogSight(Entity* _dogSight) { dogSight = _dogSight; }
	void GetHuman(Entity* _human) { humanEntity = _human; }

private:
	// Toggle로 이동할지 안 할지 true false로 정하고
	// Move쪽에서 이동할지 안 할지 정하는 거지

	void DogToggle();
	void DogMove(float _deltaTime);

	void DogRotation(DirectX::SimpleMath::Vector3 _vector3);
	void HumanRotation(DirectX::SimpleMath::Vector3 _vector3);

	void HumanStateMent();

	ManagerSet* managerSet;
	QuestManager* questManager;

	float speed = 100.f;

	float humanSpeed = 50.f;
	int humanState = 0;

	bool isforward = false;				// 전진 on/off toggle
	bool isbackward = false;			// 후진 on/off toggle
	bool isleft = false;				// 좌측 on/off toggle
	bool isright = false;				// 우측 on/off toggle
	bool checkForwardBackward = false;	// 전진 후진중 한개가 눌렀나? 확인하는 toggle
	bool checkLeftRight = false;		// 좌측 우측중 한개가 눌렀나? 확인하는 toggle

	bool isSleeping = false;			// 눕기 on/off를 위한 Toggle
	bool isJumping = false;				// 점프 on/off를 위한 Toggle
	bool isSitting = false;				// 앉기 on/off를 위한 Toggle	
	bool isSmell = false;				// 맡기 on/off를 위한 Toggle
	bool isMoving = false;				// 이동 on/off를 위한 Toggle
	bool isBiting = false;				// 물기 on/off를 위한 Toggle

	bool isHoldBiting = false;			// 물고있는 중
	bool lieStandUp = false;			// 눕기 -> 일어서기
	bool SitStandUp = false;			// 앉기 -> 일어서기
	bool sitToLie = false;				// 앉기 -> 눕기
	bool lieToSit = false;				// 눕기 -> 앉기

	bool sitLoop = false;
	bool lieLoop = false;
	bool playAnimation = false;			// Animation 진행 중
	
	std::vector<float> directSpeed;		// 이동 값을 담는다.
	
	float dt = 0.0f;					// 애니메이션과 동기화를 위해서
	float dogHeight;					//퀘스트에 쓰기 위해 필요한 값.
	
	Entity* dogSight;					//강아지 시선처리를 위한 Entity
	Entity* humanEntity;				//사람임.
	float dogX;
	float dogZ;
};

// 추상화 
// 상태별로 클래스 만들기
// 인터페이스 하나로 모든 것을 관리 가능.
// State Design Pattern 이란 것이 있다.

// 달력뜯기 밧줄뜯기
/// 뒤로 가는거 없이 제작
/// 1 스테이지 마지막 뒤로가는 애니메이션 출력

/// 밧줄이랑 상호작용 시 뒤로가는 애니메이션 출력 위치는 제자리

