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
	//강아지의 시야값도 움직여준다.
	dogSight->GetComponent<Transform>()->SetPosition(Vector3(dogX, dogHeight, dogZ));
	
	questManager->HumanStateUpdate(humanState);
}

void DogFSM::DogToggle()
{
	// 애니메이션 시 이동 금지

	// 이동
	InputManager* inputManager = managerSet->GetInputManager();

	// 전진 키를 뗐을 때
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::AWAY) && checkForwardBackward)
	{
		dt = 0;
		isMoving = false;
		isforward = false;
		checkForwardBackward = false;
	}

	// 전진 키를 뗐을 때
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::AWAY) && checkForwardBackward)
	{
		dt = 0;
		isMoving = false;
		isbackward = false;
		checkForwardBackward = false;
	}

	// 전진 키를 뗐을 때
	if (inputManager->IsKeyState(KEY::D, KEY_STATE::AWAY) && checkLeftRight)
	{
		dt = 0;
		isMoving = false;
		isright = false;
		checkLeftRight = false;
	}

	// 좌측 키를 뗐을 때
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::AWAY) && checkLeftRight)
	{
		dt = 0;
		isleft = false;
		isMoving = false;
		checkLeftRight = false;
	}

	if (playAnimation)
		return;


	// W 전진
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

	// S 후진
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

	// A 좌측
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

	// D 우측
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

	/// 특수 행동
	// 물기
	/// 물리 충돌 Test 범위에 들어 왔다면 최초 실행
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

	// 맡기
	/// 물리 충돌 Test 범위에 들어 왔다면 실행
	if (inputManager->IsKeyState(KEY::E, KEY_STATE::TAP))
	{
		if (isJumping || isBiting || isHoldBiting)
			return;

		dt = 0;
		playAnimation = true;
		isSmell = true;
		return;
	}

	// 눕기
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

	// 앉기
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

	// 점프
	if (inputManager->IsKeyState(KEY::SPACE, KEY_STATE::TAP))
	{
		// 점프 중이면 return
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
	// 카메라 모듈에서 카메라를 가져온다.
	CameraModule* cameraModule = entity->GetComponent<CameraModule>();

	// main 카메라인가?
	bool mainCamera = cameraModule->GetMainCamera();

	if (!mainCamera) return;

	// Transform과 Input Manager를 가져온다.
	InputManager* inputManager = managerSet->GetInputManager();
	Transform* transform = entity->GetComponent<Transform>();

	// 윤서가 원하는 key 입력 받으면 위치 초기화

	if (inputManager->IsKeyState(KEY::F5, KEY_STATE::TAP))
	{
		transform->SetPosition(Vector3(0.f, 10.f, 0.0f));
	}

	// 카메라를 가져온다.
	ICamera* camera = entity->GetComponent<CameraModule>()->GetCamera();

	// 현재 카메라의 View Matrix를 가져온다.
	std::vector<std::vector<float>> cameraMatrix = camera->GetViewMatrix();

	// 카메라모듈에 있는 기본 속도를 가져와서 적용한다.
	// 카메라 속도 = 캐릭터 이동속도 동기화 시킨다.

	// 방향 벡터를 생성
	Vector3 direct = { 0.f, 0.f, 0.f };

	//강아지의 높이를 가져온다
	Vector3 nowPosition = transform->GetPosition();
	dogX = nowPosition.x;
	dogHeight = nowPosition.y;
	dogZ = nowPosition.z;

	bool isRopeBite = entity->GetComponent<Animation>()->isRopeBite;

	// W 전진
	if (isforward)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop) {}
		else
		{
			Vector3 forward = { cameraMatrix[0][0], 0.f, cameraMatrix[0][2] };
			direct += forward;
		}
	}

	// S 후진
	if (isbackward)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop ) {}
		else
		{
			Vector3 forward = { -cameraMatrix[0][0], 0.f, -cameraMatrix[0][2] };
			direct += forward;
		}	
	}

	// A 왼쪽
	if (isleft)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop) {}
		else
		{
			Vector3 forward = { cameraMatrix[2][0], 0.f, cameraMatrix[2][2] };
			direct += forward;
		}	
	}

	// D 오른쪽
	if (isright)
	{
		if (isSitting || isSleeping || isSmell || isRopeBite || sitLoop) {}
		else
		{
			Vector3 forward = { -cameraMatrix[2][0], 0.f, -cameraMatrix[2][2] };
			direct += forward;
		}		
	}

	// 계산하고 Normalize를 한다.
	direct.Normalize(direct);

	// 여기서 Speed 저장하고 camera로
	directSpeed[0] = direct.x * _deltaTime * speed;
	directSpeed[1] = direct.y * _deltaTime * speed;
	directSpeed[2] = direct.z * _deltaTime * speed;

	Vector3 zero = { 0.f, 0.f, 0.f };

	// 만약 direct가 0,0,0 이 아니라면 AddPosition을 시간과 이동속도와 direct를 곱한다.
	if (direct != zero)
	{
		if (0.01 > dt)
		{
			AudioManager::GetInstance()->StopEffect(EFFECT::Dog_Walk);
			AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Walk);
		}

		transform->AddPosition(direct * _deltaTime * speed);
		// 그리고 해당 direct에 맞게 회전을 한다.
		DogRotation(direct);
	}

	/// 여기는 사람 StateMent 여깄는게 마음에 안 들지만 시간이 없다.
	// 나중 - 시작 거리를 구한다. 강아지 위치랑 같아질 때까지 이동한다.
	if (humanEntity != nullptr && questManager->isQuest3Start == true && !questManager->isQuest3Clear)
	{
		// 사람 Position을 구한다.
		Transform* humanTransform = humanEntity->GetComponent<Transform>();
		Vector3 humanPosition = humanTransform->GetPosition();

		// 강아지 현재위치 - 사람 현재 위치
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
					// 그리고 해당 direct에 맞게 회전을 한다.
					HumanRotation(humanDirect);
				}
			}
		}
	}

	// 점프
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

	// 물기시 최초 애니메이션 시간 동안은 이동 금지
	if (isBiting || isHoldBiting)
	{		
		if (isHoldBiting && isBiting)
		{
			// 애니메이션 하는 중
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

	// 앉기시 이동 금지
	if (isSitting || SitStandUp || lieToSit || sitLoop)
	{
		if (SitStandUp || lieToSit)
		{
			// 일어날 때 걸리는 애니메이션 시간
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

	// 눕기시 이동 금지
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

	// 맡기시 이동 금지
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
	// 초기 들어왔을 때 
	switch (humanState)
	{
	case 0:		// 우는 상태
	{
		dt = 0;
		humanState = 1;
		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Cry);
	}
		break;
	case 1:		// Look 상태
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
	case 2:		// Stand 상태
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
