#pragma once
#include "Component.h"
#include "SimpleMath.h"

class Animation;
class QuestManager;

/// <summary>
/// Entity�� ������ �� �ִ� Component
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
	// Toggle�� �̵����� �� ���� true false�� ���ϰ�
	// Move�ʿ��� �̵����� �� ���� ���ϴ� ����

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

	bool isforward = false;				// ���� on/off toggle
	bool isbackward = false;			// ���� on/off toggle
	bool isleft = false;				// ���� on/off toggle
	bool isright = false;				// ���� on/off toggle
	bool checkForwardBackward = false;	// ���� ������ �Ѱ��� ������? Ȯ���ϴ� toggle
	bool checkLeftRight = false;		// ���� ������ �Ѱ��� ������? Ȯ���ϴ� toggle

	bool isSleeping = false;			// ���� on/off�� ���� Toggle
	bool isJumping = false;				// ���� on/off�� ���� Toggle
	bool isSitting = false;				// �ɱ� on/off�� ���� Toggle	
	bool isSmell = false;				// �ñ� on/off�� ���� Toggle
	bool isMoving = false;				// �̵� on/off�� ���� Toggle
	bool isBiting = false;				// ���� on/off�� ���� Toggle

	bool isHoldBiting = false;			// �����ִ� ��
	bool lieStandUp = false;			// ���� -> �Ͼ��
	bool SitStandUp = false;			// �ɱ� -> �Ͼ��
	bool sitToLie = false;				// �ɱ� -> ����
	bool lieToSit = false;				// ���� -> �ɱ�

	bool sitLoop = false;
	bool lieLoop = false;
	bool playAnimation = false;			// Animation ���� ��
	
	std::vector<float> directSpeed;		// �̵� ���� ��´�.
	
	float dt = 0.0f;					// �ִϸ��̼ǰ� ����ȭ�� ���ؼ�
	float dogHeight;					//����Ʈ�� ���� ���� �ʿ��� ��.
	
	Entity* dogSight;					//������ �ü�ó���� ���� Entity
	Entity* humanEntity;				//�����.
	float dogX;
	float dogZ;
};

// �߻�ȭ 
// ���º��� Ŭ���� �����
// �������̽� �ϳ��� ��� ���� ���� ����.
// State Design Pattern �̶� ���� �ִ�.

// �޷¶�� ���ٶ��
/// �ڷ� ���°� ���� ����
/// 1 �������� ������ �ڷΰ��� �ִϸ��̼� ���

/// �����̶� ��ȣ�ۿ� �� �ڷΰ��� �ִϸ��̼� ��� ��ġ�� ���ڸ�

