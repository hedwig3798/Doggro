#pragma once
#include "Component.h"

class AObject;
class QuestManager;

enum class SelectAnimation
{
	Child,
	Adult,
	Ghost,
	Human,
	END,
};

enum class HumanAnimationState
{
	HumanIdle,			//0
	HumanStand,			//1
	HumanWalk,			//2
	HumanCry,			//3
	HumanLook,			//4
	HumanSit,			//5
	HumanSitLoop,		//6
	HumanOpen,			//7
	HumanTrippleAccle,	//8

	END,
};

enum class DogAnimationState
{
	DogIdle,			// 강아지 서 있는 동작
	DogBiteIdle,		// Object를 물고 서 있는 동작

	DogWalk,			// 걷는 동작
	DogBiteWalk,		// Object를 물고 걷는 동작

	DogBackWalk,		// Object를 물고 걷는 동작
	DogBiteBackWalk,	// Object를 물고 걷는 동작

	DogJump,			// 점프하는 동작
	DogBiteJump,		// Object를 물고 점프하는 동작

	DogStandToLie,		// 서 있는 상태에서 눕는 동작
	DogSitToLie,		// 앉은 상태에서 웅크려 눕는 동작

	DogLieToStand,		// 누운 상태에서 일어서는 동작
	DogLieToSit,		// 누운 상태에서 앉는 동작

	DogSitToStand,		// 앉은 상태에서 일어서는 동작
	DogStandToSit,		// 서 있는 상태에서 앉는 동작

	DogSitLoop,			// 앉은 상태에서 유지 동작 
	DogPush,			// 충돌 시 머리를 숙여 살짝 밀치는 동작

	DogUseBiteStand,	// 서서 깨무는 동작
	DogUsePutDown,		// 물고 있던 것을 내려놓는 동작
	DogUseBiteWalk,		// 걸으며 깨무는 동작

	DogBarkStand,		// 서서 짖는 동작
	DogBarkWalk,		// 걸으며 짖는 동작
	DogBarkSit,			// 앉아서 짖는 동작
	DogBarkJump,		// 점프해서 짖는 동작
	
	DogSmell,			// 고개를 뻗어서 냄새를 맡는 동작
	DogPhshUp,			// 이스터 에그 1
	DogBingBing,		// 이스터 에그 2
	
	END,
};

/// <summary>
/// Component로 만드는 게 맞을듯 하다. 그래야 관리하기 쉬울 거 같다!
/// </summary>
class Animation : public Component
{
public:
	Animation(Entity* _entity);
	virtual ~Animation();

	virtual void Update(float _deltaTime) override;
	virtual void Render() override;
	
	void SelectAnimationType(SelectAnimation _animationType);
	AObject* GetAObject() { return aObjectRender; }

	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }
	void UpdateDogState(bool _isRopeBite) { isRopeBite = _isRopeBite; }
	void SetHumanState(int _humanState) {}

	bool isRopeBite;			//퀘스트를 위한조건값.
	SelectAnimation GetAnimationType() const { return animationType; }
private:
	bool isDogAnimation = false;

	bool isMoving = false;		// 움직였나?
	bool isSitting = false;		// 앉았나?
	bool isSleeping = false;	// 누웠나?
	bool isJumping = false;		// 뛰었나?
	bool isStanding = false;	// 가만히있나?

	bool isCrying = false;		// 짖고있나?
	bool isSmell = false;		// 맡고있나?
	bool isBiting = false;		// 물었나?

	bool sitToStand = false;	// 앉았다 일어나기
	bool lieToStand = false;	// 누웠다 일어나기

	bool sitToLie = false;		// 앉고 있다가 눕기
	bool lieToSit = false;		// 앉고 있다가 눕기

	bool sitLoop = false;		// SitLoop
	bool lieLoop = false;		// LieLoop

	bool isHoldBiting = false;	// 물고 있는 키
	bool isBiteMoving = false;	// 이동하면서 물기
	bool awayBite = false;		// Bite 제거 시 바로 떨어지는 키

	bool sitCrying = false;		// 앉으며 짖기
	bool walkCrying = false;	// 걸으며 짖기
	bool jumpCrying = false;	// 점프 중 짖기

	bool walkSmell = false;		// 걸으며 맡기
	bool sitSmell = false;		// 앉아서 맡기
	bool isGhost = false;

	bool playAnimation = false;	// 애니메이션 Play
	bool firstIn = false;
	bool oneClear = false;

	float dt = 0.0f;			// 애니메이션 시간
	


	int humanAnimation = 0;
	int humanState;				// 사람 상태를 숫자로 넘길게요. 맞게 업데이트 부탁.

	std::vector<std::string> animationVector;
	AObject* aObjectRender;
	ManagerSet* managerSet;
	QuestManager* questManager;
	SelectAnimation animationType;
	
	void DogAnimationLoad();
	void HumanAnimationLoad();

	void DogAnimationToggle();
	void DogPlayAnimation();

	void HumanAnimationToggle();
	void HumanPlayAnimation();
	
	void MoveAnimation();


};
