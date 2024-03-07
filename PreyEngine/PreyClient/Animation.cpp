#include "Animation.h"
#include "AObject.h"
#include "Entity.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "InputManager.h"
#include "QuestManager.h"
#include "SimpleMath.h"
#include "Transform.h"
#include "DogScript.h"
#include "AudioManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Stage4.h"

Animation::Animation(Entity* _entity)
	: Component(_entity, "Animation")
{
	managerSet = entity->GetManagerset();
}

Animation::~Animation()
{

}

void Animation::Update(float _deltaTime)
{
	if (isDogAnimation)
	{
		//Dog Animation
		DogAnimationToggle();
		//퀘스트 시스템을 위한 강아지 상태 업데이트 함수
		questManager->StateUpdate(isCrying, isSmell, isBiting, isHoldBiting, isSleeping, isRopeBite);
		DogPlayAnimation();
		questManager->GetDogAnimation(this);
	}
	else
	{
		// Human Animation
		HumanAnimationToggle();
		HumanPlayAnimation();
	}
	MoveAnimation();
	dt += _deltaTime;

}

void Animation::Render()
{
	aObjectRender->Render();
}

void Animation::SelectAnimationType(SelectAnimation _animationType)
{
	animationType = _animationType;
	switch (_animationType)
	{
	case SelectAnimation::Child:
	{
		animationVector.resize(static_cast<int>(DogAnimationState::END));
		aObjectRender = new AObject("adult_dog_final3.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
		DogAnimationLoad();
		isDogAnimation = true;
	}
		break;
	case SelectAnimation::Adult:
	{
		animationVector.resize(static_cast<int>(DogAnimationState::END));
		aObjectRender = new AObject("adult_dog_final3.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
		DogAnimationLoad();
		isDogAnimation = true;
	}
		break;
	case SelectAnimation::Ghost:
	{
		animationVector.resize(static_cast<int>(DogAnimationState::END));
		aObjectRender = new AObject("adult_dog_final3.fbx", entity->GetManagerset()->GetGraphics(), true, true, false);
		DogAnimationLoad();
		isDogAnimation = true;
	}
		break;
	case SelectAnimation::Human:
	{
		animationVector.resize(static_cast<int>(HumanAnimationState::END));
		aObjectRender = new AObject("human_rig_final2.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
		HumanAnimationLoad();
		isDogAnimation = false;
	}
		break;
	default:
		break;
	}
}

void Animation::DogAnimationLoad()
{
	// 애니메이션 개수가 N개가 늘어날 것이다.

	animationVector[static_cast<int>(DogAnimationState::DogIdle)] = "dog_idle";
	animationVector[static_cast<int>(DogAnimationState::DogBiteIdle)] = "dog_bite_idle";
	animationVector[static_cast<int>(DogAnimationState::DogWalk)] = "dog_walk";
	animationVector[static_cast<int>(DogAnimationState::DogBiteWalk)] = "dog_bite_walk";
	animationVector[static_cast<int>(DogAnimationState::DogBiteBackWalk)] = "dog_bite_back_walk";
	animationVector[static_cast<int>(DogAnimationState::DogJump)] = "dog_jump";
	animationVector[static_cast<int>(DogAnimationState::DogBiteJump)] = "dog_bite_jump";
	animationVector[static_cast<int>(DogAnimationState::DogStandToLie)] = "dog_stand_to_lie";
	animationVector[static_cast<int>(DogAnimationState::DogSitToLie)] = "dog_sit_to_lie";
	animationVector[static_cast<int>(DogAnimationState::DogLieToStand)] = "dog_lie_to_stand";
	animationVector[static_cast<int>(DogAnimationState::DogLieToSit)] = "dog_lie_to_sit";
	animationVector[static_cast<int>(DogAnimationState::DogSitToStand)] = "dog_sit_to_stand";
	animationVector[static_cast<int>(DogAnimationState::DogStandToSit)] = "dog_stand_to_sit";
	animationVector[static_cast<int>(DogAnimationState::DogSitLoop)] = "dog_sit_loop";
	animationVector[static_cast<int>(DogAnimationState::DogPush)] = "dog_push";
	animationVector[static_cast<int>(DogAnimationState::DogUseBiteStand)] = "dog_use_bite_stand";
	animationVector[static_cast<int>(DogAnimationState::DogUsePutDown)] = "dog_use_put_down";
	animationVector[static_cast<int>(DogAnimationState::DogUseBiteWalk)] = "dog_use_bite_walk";
	animationVector[static_cast<int>(DogAnimationState::DogBarkStand)] = "dog_bark_stand";
	animationVector[static_cast<int>(DogAnimationState::DogBarkWalk)] = "dog_bark_walk";
	animationVector[static_cast<int>(DogAnimationState::DogBarkSit)] = "dog_bark_sit";
	animationVector[static_cast<int>(DogAnimationState::DogBarkJump)] = "dog_bark_jump";
	animationVector[static_cast<int>(DogAnimationState::DogSmell)] = "dog_smell";
}

void Animation::HumanAnimationLoad()
{
	animationVector[static_cast<int>(HumanAnimationState::HumanCry)] = "human_cry";
	animationVector[static_cast<int>(HumanAnimationState::HumanLook)] = "human_look";
	animationVector[static_cast<int>(HumanAnimationState::HumanStand)] = "human_stand";
	animationVector[static_cast<int>(HumanAnimationState::HumanWalk)] = "human_walk";
	animationVector[static_cast<int>(HumanAnimationState::HumanSit)] = "human_sit";
	animationVector[static_cast<int>(HumanAnimationState::HumanSitLoop)] = "human_sit_loop";
	animationVector[static_cast<int>(HumanAnimationState::HumanOpen)] = "human_open";
	animationVector[static_cast<int>(HumanAnimationState::HumanIdle)] = "human_idle";
	animationVector[static_cast<int>(HumanAnimationState::HumanTrippleAccle)] = "human_tripple_accle";
}

void Animation::DogAnimationToggle()
{
	InputManager* inputManager = managerSet->GetInputManager();

	// 이동 애니메이션 wsad 키를 처음 눌렀을 때 애니메이션 뗐을 때 dt = 0, move 상태
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::AWAY) ||
		inputManager->IsKeyState(KEY::A, KEY_STATE::AWAY) ||
		inputManager->IsKeyState(KEY::S, KEY_STATE::AWAY) ||
		inputManager->IsKeyState(KEY::D, KEY_STATE::AWAY))
	{
		// 점프 중이라면 이동 애니메이션이 입력 받지 못하게 한다.
		if (isJumping)
		{
			return;
		}

		isMoving = false;
		isStanding = true;
		return;
	}

	// 돌아가고 있는 시간 동안 마우스를 뗀다면 playAnimation이 계속 true이기 때문에 Animation에 Lock이 걸린다.
	
	// 물고 있는 것을 놨을 때
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::AWAY))
	{
		if (isSitting || isJumping || isSleeping || isCrying)
			return;

		awayBite = true;
		isHoldBiting = false;
		return;
	}

	// 여기서 애니메이션이 Play 중이라면 이리로 들어오지 못하도록 한다.
	if (playAnimation) return;

	/// 키 입력

	/// 일반 행동
	// 이동 애니메이션 wsad 키를 처음 눌렀을 때 애니메이션 시작 dt = 0, move 상태
	if ((inputManager->IsKeyState(KEY::W, KEY_STATE::TAP) ||
		 inputManager->IsKeyState(KEY::A, KEY_STATE::TAP) ||
		 inputManager->IsKeyState(KEY::S, KEY_STATE::TAP) ||
		inputManager->IsKeyState(KEY::D, KEY_STATE::TAP)) && !isMoving)
	{
		// 점프 중이라면 이동 애니메이션이 입력 받지 못하게 한다.
		if (isJumping || isRopeBite)
		{
			return;
		}

		AudioManager::GetInstance()->StopEffect(EFFECT::Dog_Walk);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Walk);

		if (isSitting)
		{
			dt = 0;
			// 앉고 있는 데 이동 키 누르면 앉기가 풀린다.
			sitToStand = true;
			isMoving = false;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			// 눕고 있는데 이동 키 누르면 눕기가 풀린다.
			lieToStand = true;
			isMoving = false;
			return;
		}

		// 아무것도 없다면? 이동 고
		dt = 0; 
		isMoving = true;
		isStanding = false;
		return;
	}


	// 이동 키를 누르고 있으면 이동 누르고 있는 동안 유지
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD) ||
		inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD) ||
		inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD) ||
		inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD))
	{
		if (isJumping || isRopeBite)
		{
			return;
		}

		

		isMoving = true;
		isStanding = false;
	}

	// 점프 애니메이션 (Jump : false, Sit : false, Sleep : false, )
	if (inputManager->IsKeyState(KEY::SPACE, KEY_STATE::HOLD))
	{
		if (inputManager->IsKeyState(KEY::RMOUSE, KEY_STATE::TAP))
		{
		 	dt = 0;
			jumpCrying = true;
			return;
		}

		if (isJumping || isBiting || isBiteMoving || isRopeBite)
			return;

		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Jump);

		if (isSitting)
		{
			dt = 0;
			// 앉았다면 일어서야 한다.
			sitToStand = true;
			isJumping = false;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			// 누웠다면 일어서야 한다.
			lieToStand = true;
			isJumping = false;
			return;
		}

		// 점프 애니메이션 실행
		dt = 0;
		isJumping = true;
		isMoving = false;
		isStanding = false;
		return;
	}

	// 앉기 애니메이션 
	if (inputManager->IsKeyState(KEY::CTRL, KEY_STATE::TAP))
	{
		if (isJumping || isBiting || isBiteMoving || isHoldBiting)
			return;

		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Sit);

		// 누워 있다면 눕기 -> 앉기로
		if (isSleeping)
		{
			dt = 0;
			lieToSit = true;
			return;
		}

		// 앉기 -> 일어나기


		if (isSitting)
		{
			dt = 0;
			sitToStand = true;
			isSitting = false;
			return;
		}
		
		// 앉기 실행
		dt = 0;
		isSitting = true;
		return;
	}

	// 눕기 애니메이션, 누운 상태에서 앉기 가능
	if (inputManager->IsKeyState(KEY::LSHIFT, KEY_STATE::TAP))
	{
		if (isJumping || isBiting || isBiteMoving || isHoldBiting || isSmell)
			return;

		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Lie);

		// 앉기 -> 눕기
		if (isSitting)
		{
			dt = 0;
			sitToLie = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			// 누웠다 일어나기
			lieToStand = true;	
			return;
		}

		dt = 0;
		isSleeping = true;
		return;
	}

	/// 특수 행동 	
	// 물기 애니메이션
	/// 물리 테스트
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
	{
		// 앉거나 점프 중이거나 눕고 있으면 물기 안한다.
		if (isSitting || isJumping || isSleeping)
 			return;

		if (isMoving)
		{
			dt = 0;
			isBiteMoving = true;
			return;
		}

		// 그냥 물기
		dt = 0;
		isBiting = true;

		return;
	}

	/// 물리 테스트 
	// 물고 있을 때
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD))
	{
		if (isSitting || isJumping || isSleeping)
			return;
		
		isHoldBiting = true;	
	}

	// 물고 있는 것을 놨을 때
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::AWAY) || awayBite)
	{
		if (isSitting || isJumping || isSleeping || isCrying)
			return;

		bool isAttach = entity->GetComponent<DogScript>()->GetIsAttach();

		if (isAttach)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Put_Down);
		}

		isBiting = false;
		isHoldBiting = false;
		awayBite = false;
		return;
	}

	// 짖기 애니메이션
	if (inputManager->IsKeyState(KEY::RMOUSE, KEY_STATE::TAP))
	{
		
		if (isBiting || isBiteMoving || isSleeping || isHoldBiting)
			return;

		if (animationType == SelectAnimation::Child)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Baby_Bark);
		}
		else
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Normal_Bark);
		}

		// 앉으며 짖기
		if (isSitting)
		{
			dt = 0;
			sitCrying = true;
			return;
		}

		// 움직이며 짖기
		if (isMoving)
		{
			dt = 0;
			walkCrying = true;
			return;
		}

		// 가만히 짖기
		dt = 0;
		isCrying = true;
		return;
	}


	// 맡기 애니메이션, 점프 중일 때 사용 불가
	/// 물리 넣고 영차
	if (inputManager->IsKeyState(KEY::E, KEY_STATE::TAP))
	{
		if (isJumping || isHoldBiting || isSleeping)
			return;


		if (isMoving)
		{
			dt = 0;
			walkSmell = true;
			isSmell = true;
			return;
		}

		if (isSitting)
		{
			dt = 0;
			sitSmell = true;
			isSmell = true;
			return;
		}

		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Smell);
		dt = 0;
		isSmell = true;
		return;
	}
}

void Animation::DogPlayAnimation()
{
	InputManager* inputManager = managerSet->GetInputManager();
	bool isAttach = entity->GetComponent<DogScript>()->GetIsAttach();
	
	if (questManager->isQuest1Clear && questManager->isGhost)
	{
		SelectAnimation dogAni = entity->GetComponent<Animation>()->GetAnimationType();

		if (dogAni == SelectAnimation::Adult)
		{
			entity->GetComponent<Animation>()->SelectAnimationType(SelectAnimation::Ghost);
			questManager->isGhost = false;
		}
	}

	// 애니메이션 시전 중에는 다른 애니메이션이 실행이 되면 안된다.

	// 밧줄 성공 시 출력동안 다른 거 불가능
	if (isRopeBite)
	{
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBiteBackWalk)], dt);
		playAnimation = true;

		if (dt > 4.0)
		{
			dt = 0;
			isRopeBite = false;
			playAnimation = false;
		}
		return;
	}

	//무는 애니메이션
	if (isBiting || isBiteMoving)
	{
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogUseBiteStand)], dt);
		playAnimation = true;

		if (dt > 0.7)
		{
			playAnimation = false;
			isBiteMoving = false;
			isBiting = false;
			isStanding = true;
		}
		return;
	}

	// 정지 애니메이션
	if (isStanding)
	{
		if (isHoldBiting && isAttach)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBiteIdle)], dt);
			return;
		}
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogIdle)], dt);
	}

	// 걷는 애니메이션
	if (isMoving)
	{		
		if (isHoldBiting && isAttach)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBiteWalk)], dt);
			return;
		}
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogWalk)], dt);
	}
	// 짖는 애니메이션, 나머지 false인 상태
	if (isCrying || sitCrying || walkCrying || jumpCrying)
	{
	
		if (sitCrying)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBarkSit)], dt);
			playAnimation = true;
			if (dt > 0.7)
			{
				dt = 0;
				sitCrying = false;
				sitLoop = true;
				playAnimation = false;
			}
			return;
		}

		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBarkStand)], dt);
		playAnimation = true;
		if (dt > 0.7)
		{
			dt = 0;
			isCrying = false;
			jumpCrying = false;
			walkCrying = false;
			playAnimation = false;
		
		}
		return;
	}

	// 냄새 애니메이션
	if (isSmell || walkSmell || sitSmell)
	{
		if (walkSmell)
		{
			if (dt > 0.1f)
			{
				AudioManager::GetInstance()->StopAllEffect();
				AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Smell);
			}

			// idle -> 맡기 -> idle
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogIdle)], dt);
			playAnimation = true;

			if (dt > 0.3)
			{
				dt = 0;
				walkSmell = false;
				isMoving = false;
				return;
			}
			return;
		}

		if (sitSmell)
		{
			if (dt > 0.1f)
			{
				AudioManager::GetInstance()->StopAllEffect();
				AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Smell);
			}

			// sitToStand -> 맡기 -> idle
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSitToStand)], dt);
			playAnimation = true;

			if (dt > 0.7)
			{
				dt = 0;
				sitSmell = false;
				isSitting = false;
				sitLoop = false;
				return;
			}
			return;
		}

		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSmell)], dt);
		playAnimation = true;

		if (dt > 0.7)
		{
			dt = 0;
			playAnimation = false;
			isSmell = false;
			isStanding = true;
		}
		return;
	}

	// 앉는 애니메이션
	if (isSitting || sitToStand || sitToLie)
	{
	
		// 앉는 상태에서 일어났다면?
		if (sitToStand)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSitToStand)], dt);
			playAnimation = true;
			if (dt > 0.7)
			{
				dt = 0;
				isSitting = false;
				sitToStand = false;
				playAnimation = false;
				sitLoop = false;
				isStanding = true;
			}
			return;
		}
		
		// 앉기 -> 눕기
		if (sitToLie)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSitToLie)], dt);
			playAnimation = true;

			if (dt > 0.4)
			{
				dt = 0;
				isSitting = false;
				playAnimation = false;
				sitToLie = false;
				sitLoop = false;
				isSleeping = true;
			}
			return;
		}
		
		// 앉는거 유지
		if (sitLoop)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSitLoop)], dt);
			return;
		}
	
		// 서 있다가 앉기
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogStandToSit)], dt);
		playAnimation = true;
		if (dt > 0.86)
		{
			dt = 0;
			playAnimation = false;
			sitLoop = true;
		}
		return;
	}
 
	// 점프 애니메이션
	if (isJumping)
	{

		if (isHoldBiting && isAttach)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBiteJump)], dt);
			if (dt > 0.96)
			{
				dt = 0;
				isJumping = false;
				isStanding = true;
			}
			return;
		}

		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogJump)], dt);
		if (dt > 0.96)
		{
			dt = 0;
			isJumping = false;
			isStanding = true;
		}
		return;
	}

	// 눕는 애니메이션 
	if (isSleeping || lieToStand || lieToSit)
	{
		// 눕다가 일어나기
		if (lieToStand)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogLieToStand)], dt);
			playAnimation = true;
			if (dt > 0.7)
			{
				dt = 0;
				isSleeping = false;
				lieToStand = false;
				playAnimation = false;
				lieLoop = false;
				isStanding = true;
			}
			return;
		}

		// 눕다가 앉기
		if (lieToSit)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSitToLie)], dt);
			playAnimation = true;

			if (dt > 0.7)
			{
				isSleeping = false;
				lieLoop = false;
				playAnimation = false;
				lieToSit = false;
				isSitting = true;
			}
			return;
		}

		// 눕는거 유지
		if (lieLoop)
		{
			// 마지막 프레임 유지라는데?
			dt = 0.82;
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogStandToLie)], dt);
			return;
		}

		// 서 있다가 눕기
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogStandToLie)], dt);
		playAnimation = true;

		if (dt > 0.86)
		{
			dt = 0;
			playAnimation = false;
			lieLoop = true;
		}
		return;
	}
}

void Animation::HumanAnimationToggle()
{
	// 여기서 Human 전용 애니메이션을 Toggle을 받고
	
}

void Animation::HumanPlayAnimation()
{
	// Animation이 실행된다. 
	// 시작할 때 일어서 있다가 앉고 앉기 Loop -> 허탈감 
	// 서약서 작성시 Cry Animation 실행 -> 슬픔 고조
	// 강아지 짖으면 놀라고, 일어서고, 움직이고, 정지하고, 문 열고 -> 극복

	Scene* _scene = managerSet->GetSceneManager()->GetCurrentScene();

	bool cutScene = dynamic_cast<Stage4*>(_scene)->isStartSceneEnd;

	if (humanState == 0 && cutScene)
	{
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanIdle)], dt);
		
		if (dt > 1.0f)
		{
			dt = 0;
			humanState = 1;
		}
	}

	if (questManager->isQuest1Clear && !oneClear)
	{
		AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Cry);
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanCry)], dt);
		questManager->isGhost = true;
		oneClear = true;
	}

	if (humanState == 1)
	{
		if (0.01 >= dt)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Stand_Sit);
		}
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanSit)], dt);
		if (dt > 0.7f)
		{
			dt = 0;
			humanState = 2;
		}
	}

	if (humanState == 2)
	{
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanSitLoop)], dt);
	}

	if (questManager->isQuest3Clear && !firstIn)
	{
		dt = 0;
		firstIn = true;
	}

	if (questManager->isQuest2Clear)
	{
		if (questManager->stateMent == 0)
		{
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Cry);
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanCry)], dt);
		}
		else if (questManager->stateMent == 1)
		{
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Surprise);
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanLook)], dt);
		}
		else if (questManager->stateMent == 2)
		{
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Stand_Sit);
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanStand)], dt);
		}
		else if (questManager->stateMent == 3)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanIdle)], dt);
		}
		else if (questManager->stateMent == 4)
		{	
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanWalk)], dt);
		}
	}

	if (questManager->stateMent == 3)
	{
		if (dt > 2.5)
		{
			dt = 0;
		}
	}

	if (questManager->stateMent == 4)
	{
		if (0.01 >= dt)
		{
			AudioManager::GetInstance()->StopAllEffect();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Human_Walk);
		}

		if (dt > 2.5)
		{
			dt = 0;
		}
	}

	if (questManager->isQuest3Clear)
	{
		if (0.35f > dt)
		{
			AudioManager::GetInstance()->StopAllSound();
			AudioManager::GetInstance()->PlayEffect(EFFECT::Door_Open);
			AudioManager::GetInstance()->PlayBGM(BGM::STAGE4END);

			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanOpen)], dt);
			questManager->SayGoodBye();
		}
		else
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(HumanAnimationState::HumanIdle)], dt);
		}
	}
}

void Animation::MoveAnimation()
{
	DirectX::SimpleMath::Matrix currentFinalMatrix = entity->GetComponent<Transform>()->GetFinalMatrix();

	Vector3 position = {};
	Quaternion quaternionToRotation = {};
	Vector3 rotation = {};
	Vector3 scale = {};

	currentFinalMatrix.Decompose(scale, quaternionToRotation, position);

	rotation = entity->GetComponent<Transform>()->QuaternionToVector3(quaternionToRotation);

	aObjectRender->SetPosition(position.x, position.y, position.z);
	aObjectRender->SetRotation(rotation.x, rotation.y, rotation.z);
	aObjectRender->SetScale(scale.x, scale.y, scale.z);
}
