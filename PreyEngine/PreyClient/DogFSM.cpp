#include "DogFSM.h"
#include "Entity.h"
#include "Transform.h"
#include "DogScript.h"
#include "Animation.h"
#include "Human.h"

#include "ManagerSet.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "CameraModule.h"
#include "QuestManager.h"
#include "ICamera.h"

#include "SimpleMath.h"


DogFSM::DogFSM(Entity* _entity)
	: Component(_entity, "Movable"), managerSet{}
{
	managerSet = _entity->GetManagerset();
	directSpeed.resize(3);
}

DogFSM::~DogFSM()
{

}

void DogFSM::Update(float _deltaTime)
{
	DogToggle();
	DogMove(_deltaTime);
	dt += _deltaTime;

	questManager->HeightUpdate(dogHeight);
	//�������� �þ߰��� �������ش�.
	dogSight->GetComponent<Transform>()->SetPosition(Vector3(dogX, dogHeight, dogZ));
	
	questManager->HumanStateUpdate(humanState);
}

void DogFSM::DogToggle()
{
	// �ִϸ��̼� �� �̵� ����

	// �̵�
	InputManager* inputManager = managerSet->GetInputManager();

	// ���� Ű�� ���� ��
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::AWAY) && checkForwardBackward)
	{
		dt = 0;
		isMoving = false;
		isforward = false;
		checkForwardBackward = false;
	}

	// ���� Ű�� ���� ��
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::AWAY) && checkForwardBackward)
	{
		dt = 0;
		isMoving = false;
		isbackward = false;
		checkForwardBackward = false;
	}

	// ���� Ű�� ���� ��
	if (inputManager->IsKeyState(KEY::D, KEY_STATE::AWAY) && checkLeftRight)
	{
		dt = 0;
		isMoving = false;
		isright = false;
		checkLeftRight = false;
	}

	// ���� Ű�� ���� ��
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::AWAY) && checkLeftRight)
	{
		dt = 0;
		isleft = false;
		isMoving = false;
		checkLeftRight = false;
	}

	if (playAnimation)
		return;


	// W ����
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD) && !checkForwardBackward )
	{
		if (isSitting)
		{
			dt = 0;
			isSitting = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}

		if (sitLoop)
		{
			dt = 0;
			sitLoop = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			isMoving = false;
			lieStandUp = true;
			playAnimation = true;
			return;
		}

		isforward = true;
		isMoving = true;
		isbackward = false;
		checkForwardBackward = true;
	}

	// S ����
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD) && !checkForwardBackward)
	{
		if (isSitting)
		{
			dt = 0;
			isSitting = false;
			SitStandUp = true;
			isMoving = false;
			playAnimation = true;
			return;
		}

		if (sitLoop)
		{
			dt = 0;
			sitLoop = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			isMoving = false;
			lieStandUp = true;
			playAnimation = true;
			return;
		}

		isbackward = true;
		isforward = false;
		isMoving = true;
		checkForwardBackward = true;
	}

	// A ����
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD) && !checkLeftRight)
	{
		if (isSitting)
		{
			dt = 0;
			isSitting = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}
		
		if (sitLoop)
		{
			dt = 0;
			sitLoop = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			isMoving = false;
			lieStandUp = true;
			playAnimation = true;
			return;
		}

		isleft = true;
		isright = false;
		isMoving = true;
		checkLeftRight = true;
	}

	// D ����
	if (inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD) && !checkLeftRight)
	{
		if (isSitting)
		{
			dt = 0;
			isSitting = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}

		if (sitLoop)
		{
			dt = 0;
			sitLoop = false;
			isMoving = false;
			SitStandUp = true;
			playAnimation = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			isMoving = false;
			lieStandUp = true;
			playAnimation = true;
			return;
		}

		isright = true;
		isleft = false;
		isMoving = true;
		checkLeftRight = true;
	}

	bool isAttach = entity->GetComponent<DogScript>()->GetIsAttach();

	/// Ư�� �ൿ
	// ����
	/// ���� �浹 Test ������ ��� �Դٸ� ���� ����
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
	{
		dt = 0;
		playAnimation = true;
		isBiting = true;
		return;
	}

	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::AWAY) && isAttach)
	{
		dt = 0;
		isHoldBiting = false;
		isBiting = false;
		return;
	}

	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD) && isAttach)
	{
		isHoldBiting = true;
		isBiting = false;
	}

	// �ñ�
	/// ���� �浹 Test ������ ��� �Դٸ� ����
	if (inputManager->IsKeyState(KEY::E, KEY_STATE::TAP))
	{
		if (isJumping || isBiting || isHoldBiting)
			return;

		dt = 0;
		playAnimation = true;
		isSmell = true;
		return;
	}

	// ����
	if (inputManager->IsKeyState(KEY::LSHIFT, KEY_STATE::TAP))
	{
		if (isJumping || isMoving || isBiting)
		{
			if (isMoving)
			{
				dt = 0;
				isMoving = false;
				isSleeping = true;
				return;
			}

			dt = 0;
			isSleeping = true;
			lieStandUp = true;
			playAnimation = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			lieStandUp = true;
			playAnimation = true;
			return;
		}

		if (isSitting)
		{
			dt = 0;
			lieToSit = true;
			playAnimation = true;
			return;
		}

		dt = 0;
		isSleeping = true;
		return;
	}

	// �ɱ�
	if (inputManager->IsKeyState(KEY::CTRL, KEY_STATE::TAP))
	{
		if (isJumping || isMoving || isBiting)
		{
			if (isMoving)
			{
				dt = 0;
				isMoving = false;	
				isSitting = true;
				playAnimation = true;
				return;
			}

			dt = 0;
			SitStandUp = true;
			isSitting = true;
			playAnimation = true;
			return;
		}

		if (isSitting || sitLoop)
		{
			dt = 0;		
			SitStandUp = true;
			isSitting = false;
			playAnimation = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;		
			sitToLie = true;
			playAnimation = true;
			return;
		}
			
		dt = 0;		
		isSitting = true;
		return;
	}

	// ����
	if (inputManager->IsKeyState(KEY::SPACE, KEY_STATE::TAP))
	{
		// ���� ���̸� return
		if (isJumping)
			return;

		if (isSitting)
		{
			dt = 0;		
			SitStandUp = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;		
			lieStandUp = true;
			return;
		}

		dt = 0;
		isJumping = true;
		return;
	}
}

void DogFSM::DogMove(float _deltaTime)
{
	// ī�޶� ��⿡�� ī�޶� �����´�.
	CameraModule* cameraModule = entity->GetComponent<CameraModule>();

	// main ī�޶��ΰ�?
	bool mainCamera = cameraModule->GetMainCamera();

	if (!mainCamera) return;

	// Transform�� Input Manager�� �����´�.
	InputManager* inputManager = managerSet->GetInputManager();
	Transform* transform = entity->GetComponent<Transform>();

	// ������ ���ϴ� key �Է� ������ ��ġ �ʱ�ȭ

	if (inputManager->IsKeyState(KEY::F5, KEY_STATE::TAP))
	{
		transform->SetPosition(Vector3(0.f, 10.f, 0.0f));
	}

	// ī�޶� �����´�.
	ICamera* camera = entity->GetComponent<CameraModule>()->GetCamera();

	// ���� ī�޶��� View Matrix�� �����´�.
	std::vector<std::vector<float>> cameraMatrix = camera->GetViewMatrix();

	// ī�޶��⿡ �ִ� �⺻ �ӵ��� �����ͼ� �����Ѵ�.
	// ī�޶� �ӵ� = ĳ���� �̵��ӵ� ����ȭ ��Ų��.

	// ���� ���͸� ����
	Vector3 direct = { 0.f, 0.f, 0.f };

	//�������� ���̸� �����´�
	Vector3 nowPosition = transform->GetPosition();
	dogX = nowPosition.x;
	dogHeight = nowPosition.y;
	dogZ = nowPosition.z;

	bool isRopeBite = entity->GetComponent<Animation>()->isRopeBite;

	// W ����
	if (isforward)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop) {}
		else
		{
			Vector3 forward = { cameraMatrix[0][0], 0.f, cameraMatrix[0][2] };
			direct += forward;
		}
	}

	// S ����
	if (isbackward)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop ) {}
		else
		{
			Vector3 forward = { -cameraMatrix[0][0], 0.f, -cameraMatrix[0][2] };
			direct += forward;
		}	
	}

	// A ����
	if (isleft)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop) {}
		else
		{
			Vector3 forward = { cameraMatrix[2][0], 0.f, cameraMatrix[2][2] };
			direct += forward;
		}	
	}

	// D ������
	if (isright)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop) {}
		else
		{
			Vector3 forward = { -cameraMatrix[2][0], 0.f, -cameraMatrix[2][2] };
			direct += forward;
		}		
	}

	// ����ϰ� Normalize�� �Ѵ�.
	direct.Normalize(direct);

	// ���⼭ Speed �����ϰ� camera��
	directSpeed[0] = direct.x * _deltaTime * speed;
	directSpeed[1] = direct.y * _deltaTime * speed;
	directSpeed[2] = direct.z * _deltaTime * speed;

	Vector3 zero = { 0.f, 0.f, 0.f };

	// ���� direct�� 0,0,0 �� �ƴ϶�� AddPosition�� �ð��� �̵��ӵ��� direct�� ���Ѵ�.
	if (direct != zero)
	{
		if (0.01 > dt)
		{
			AudioManager::GetInstance()->StopEffect(EFFECT::Dog_Walk);
			AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Walk);
		}

		transform->AddPosition(direct * _deltaTime * speed);
		// �׸��� �ش� direct�� �°� ȸ���� �Ѵ�.
		DogRotation(direct);
	}

	/// ����� ��� StateMent �����°� ������ �� ������ �ð��� ����.
	// ���� - ���� �Ÿ��� ���Ѵ�. ������ ��ġ�� ������ ������ �̵��Ѵ�.
	if (humanEntity != nullptr && questManager->isQuest3Start == true && !questManager->isQuest3Clear)
	{
		// ��� Position�� ���Ѵ�.
		Transform* humanTransform = humanEntity->GetComponent<Transform>();
		Vector3 humanPosition = humanTransform->GetPosition();

		// ������ ������ġ - ��� ���� ��ġ
		Vector3 humanDirect = nowPosition - humanPosition;
		humanDirect.y = 0.0f;

		HumanStateMent();
		if (humanState >= 2)
		{
			if (abs(humanDirect.x) < 1.0f && abs(humanDirect.z) < 1.0f)
			{
				humanTransform->AddPosition(Vector3(0.f, 0.f, 0.f));
				humanState = 3;
			}
			else
			{
				humanDirect.Normalize(humanDirect);
				humanState = 4;

				if (humanDirect != zero)
				{
					humanTransform->AddPosition(humanDirect * _deltaTime * humanSpeed);
					// �׸��� �ش� direct�� �°� ȸ���� �Ѵ�.
					HumanRotation(humanDirect);
				}
			}
		}
	}

	// ����
	if (isJumping)
	{
		transform->AddPosition(Vector3(0.0f, 200 * _deltaTime, 0.0f));

		if (dt > 0.7)
		{
			dt = 0;
			isJumping = false;
			playAnimation = false;
		}
		return;
	}

	// ����� ���� �ִϸ��̼� �ð� ������ �̵� ����
	if (isBiting || isHoldBiting)
	{		
		if (isHoldBiting && isBiting)
		{
			// �ִϸ��̼� �ϴ� ��
			if (dt > 0.7f)
			{
				dt = 0;
				playAnimation = false;
				isBiting = false;
			}
			return;
		}

		if (isHoldBiting)
		{
			return;
		}

		if (dt > 0.7)
		{
			dt = 0;
			playAnimation = false;
			isBiting = false;
		}
		return;
	}

	// �ɱ�� �̵� ����
	if (isSitting || SitStandUp || lieToSit || sitLoop)
	{
		if (SitStandUp || lieToSit)
		{
			// �Ͼ �� �ɸ��� �ִϸ��̼� �ð�
			if (dt > 0.7)
			{
				dt = 0;
				playAnimation = false;
				isSitting = false;
				SitStandUp = false;
				sitLoop = false;
				lieToSit = false;
				isSleeping = false;
				return;
			}
		}

		if (sitLoop)
		{
			return;
		}

		if (dt > 0.7)
		{
			dt = 0;
			sitLoop = true;
			playAnimation = false;
		}
		return;
	}

	// ����� �̵� ����
	if (isSleeping || sitToLie || lieStandUp)
	{
		if (lieStandUp)
		{
			if (dt > 0.7)
			{
				dt = 0;
				playAnimation = false;
				isSleeping = false;
				sitToLie = false;
				lieStandUp = false;
				isSitting = false;
				return;
			}
		}

		if (dt > 0.7)
		{
			dt = 0;
			playAnimation = false;
		}
		return;
	}

	// �ñ�� �̵� ����
	if (isSmell)
	{
		if (dt > 0.7)
		{
			dt = 0;
			playAnimation = false;
			isSmell = false;
		}
		return;
	}
	
}

void DogFSM::DogRotation(DirectX::SimpleMath::Vector3 _vector3)
{
	Transform* transform = entity->GetComponent<Transform>();

	Vector3 up = { 0.0f, 1.0f, 0.0f };

	Quaternion quaternion = DirectX::SimpleMath::Quaternion::LookRotation(_vector3, up);
	transform->SetRotation(quaternion);
}

void DogFSM::HumanRotation(DirectX::SimpleMath::Vector3 _vector3)
{
	Transform* humanTransform = humanEntity->GetComponent<Transform>();

	Vector3 up = { 0.0f, 1.0f, 0.0f };

	Quaternion quaternion = DirectX::SimpleMath::Quaternion::LookRotation(_vector3, up);
	humanTransform->SetRotation(quaternion);
}

void DogFSM::HumanStateMent()
{
	// �ʱ� ������ �� 
	switch (humanState)
	{
	case 0:		// ��� ����
	{
		dt = 0;
		humanState = 1;
		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Cry);
	}
		break;
	case 1:		// Look ����
	{
		if (0.01 > dt)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Surprise);
		}

		if (dt > 0.7)
		{
			dt = 0;
			humanState = 2;
		}
	}
		break;
	case 2:		// Stand ����
	{
		if (0.01 > dt)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Stand_Sit);
		}
		if (dt > 1.0)
		{
			dt = 0;
		}
	}
		break;
	case 4:
	{
		if (0.01 > dt)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Walk);
		}
		if (dt > 4.0)
		{
			dt = 0;
		}
	}
		break;
	default:
		break;
	}
	
}
