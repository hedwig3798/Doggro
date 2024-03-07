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
	DogIdle,			// ������ �� �ִ� ����
	DogBiteIdle,		// Object�� ���� �� �ִ� ����

	DogWalk,			// �ȴ� ����
	DogBiteWalk,		// Object�� ���� �ȴ� ����

	DogBackWalk,		// Object�� ���� �ȴ� ����
	DogBiteBackWalk,	// Object�� ���� �ȴ� ����

	DogJump,			// �����ϴ� ����
	DogBiteJump,		// Object�� ���� �����ϴ� ����

	DogStandToLie,		// �� �ִ� ���¿��� ���� ����
	DogSitToLie,		// ���� ���¿��� ��ũ�� ���� ����

	DogLieToStand,		// ���� ���¿��� �Ͼ�� ����
	DogLieToSit,		// ���� ���¿��� �ɴ� ����

	DogSitToStand,		// ���� ���¿��� �Ͼ�� ����
	DogStandToSit,		// �� �ִ� ���¿��� �ɴ� ����

	DogSitLoop,			// ���� ���¿��� ���� ���� 
	DogPush,			// �浹 �� �Ӹ��� ���� ��¦ ��ġ�� ����

	DogUseBiteStand,	// ���� ������ ����
	DogUsePutDown,		// ���� �ִ� ���� �������� ����
	DogUseBiteWalk,		// ������ ������ ����

	DogBarkStand,		// ���� ¢�� ����
	DogBarkWalk,		// ������ ¢�� ����
	DogBarkSit,			// �ɾƼ� ¢�� ����
	DogBarkJump,		// �����ؼ� ¢�� ����
	
	DogSmell,			// ���� ��� ������ �ô� ����
	DogPhshUp,			// �̽��� ���� 1
	DogBingBing,		// �̽��� ���� 2
	
	END,
};

/// <summary>
/// Component�� ����� �� ������ �ϴ�. �׷��� �����ϱ� ���� �� ����!
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

	bool isRopeBite;			//����Ʈ�� �������ǰ�.
	SelectAnimation GetAnimationType() const { return animationType; }
private:
	bool isDogAnimation = false;

	bool isMoving = false;		// ��������?
	bool isSitting = false;		// �ɾҳ�?
	bool isSleeping = false;	// ������?
	bool isJumping = false;		// �پ���?
	bool isStanding = false;	// �������ֳ�?

	bool isCrying = false;		// ¢���ֳ�?
	bool isSmell = false;		// �ð��ֳ�?
	bool isBiting = false;		// ������?

	bool sitToStand = false;	// �ɾҴ� �Ͼ��
	bool lieToStand = false;	// ������ �Ͼ��

	bool sitToLie = false;		// �ɰ� �ִٰ� ����
	bool lieToSit = false;		// �ɰ� �ִٰ� ����

	bool sitLoop = false;		// SitLoop
	bool lieLoop = false;		// LieLoop

	bool isHoldBiting = false;	// ���� �ִ� Ű
	bool isBiteMoving = false;	// �̵��ϸ鼭 ����
	bool awayBite = false;		// Bite ���� �� �ٷ� �������� Ű

	bool sitCrying = false;		// ������ ¢��
	bool walkCrying = false;	// ������ ¢��
	bool jumpCrying = false;	// ���� �� ¢��

	bool walkSmell = false;		// ������ �ñ�
	bool sitSmell = false;		// �ɾƼ� �ñ�
	bool isGhost = false;

	bool playAnimation = false;	// �ִϸ��̼� Play
	bool firstIn = false;
	bool oneClear = false;

	float dt = 0.0f;			// �ִϸ��̼� �ð�
	


	int humanAnimation = 0;
	int humanState;				// ��� ���¸� ���ڷ� �ѱ�Կ�. �°� ������Ʈ ��Ź.

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
