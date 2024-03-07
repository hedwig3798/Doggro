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
		//����Ʈ �ý����� ���� ������ ���� ������Ʈ �Լ�
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
	// �ִϸ��̼� ������ N���� �þ ���̴�.

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

	// �̵� �ִϸ��̼� wsad Ű�� ó�� ������ �� �ִϸ��̼� ���� �� dt = 0, move ����
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::AWAY) ||
		inputManager->IsKeyState(KEY::A, KEY_STATE::AWAY) ||
		inputManager->IsKeyState(KEY::S, KEY_STATE::AWAY) ||
		inputManager->IsKeyState(KEY::D, KEY_STATE::AWAY))
	{
		// ���� ���̶�� �̵� �ִϸ��̼��� �Է� ���� ���ϰ� �Ѵ�.
		if (isJumping)
		{
			return;
		}

		isMoving = false;
		isStanding = true;
		return;
	}

	// ���ư��� �ִ� �ð� ���� ���콺�� ���ٸ� playAnimation�� ��� true�̱� ������ Animation�� Lock�� �ɸ���.
	
	// ���� �ִ� ���� ���� ��
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::AWAY))
	{
		if (isSitting || isJumping || isSleeping || isCrying)
			return;

		awayBite = true;
		isHoldBiting = false;
		return;
	}

	// ���⼭ �ִϸ��̼��� Play ���̶�� �̸��� ������ ���ϵ��� �Ѵ�.
	if (playAnimation) return;

	/// Ű �Է�

	/// �Ϲ� �ൿ
	// �̵� �ִϸ��̼� wsad Ű�� ó�� ������ �� �ִϸ��̼� ���� dt = 0, move ����
	if ((inputManager->IsKeyState(KEY::W, KEY_STATE::TAP) ||
		 inputManager->IsKeyState(KEY::A, KEY_STATE::TAP) ||
		 inputManager->IsKeyState(KEY::S, KEY_STATE::TAP) ||
		inputManager->IsKeyState(KEY::D, KEY_STATE::TAP)) && !isMoving)
	{
		// ���� ���̶�� �̵� �ִϸ��̼��� �Է� ���� ���ϰ� �Ѵ�.
		if (isJumping || isRopeBite)
		{
			return;
		}

		AudioManager::GetInstance()->StopEffect(EFFECT::Dog_Walk);
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Walk);

		if (isSitting)
		{
			dt = 0;
			// �ɰ� �ִ� �� �̵� Ű ������ �ɱⰡ Ǯ����.
			sitToStand = true;
			isMoving = false;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			// ���� �ִµ� �̵� Ű ������ ���Ⱑ Ǯ����.
			lieToStand = true;
			isMoving = false;
			return;
		}

		// �ƹ��͵� ���ٸ�? �̵� ��
		dt = 0; 
		isMoving = true;
		isStanding = false;
		return;
	}


	// �̵� Ű�� ������ ������ �̵� ������ �ִ� ���� ����
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

	// ���� �ִϸ��̼� (Jump : false, Sit : false, Sleep : false, )
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
			// �ɾҴٸ� �Ͼ�� �Ѵ�.
			sitToStand = true;
			isJumping = false;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			// �����ٸ� �Ͼ�� �Ѵ�.
			lieToStand = true;
			isJumping = false;
			return;
		}

		// ���� �ִϸ��̼� ����
		dt = 0;
		isJumping = true;
		isMoving = false;
		isStanding = false;
		return;
	}

	// �ɱ� �ִϸ��̼� 
	if (inputManager->IsKeyState(KEY::CTRL, KEY_STATE::TAP))
	{
		if (isJumping || isBiting || isBiteMoving || isHoldBiting)
			return;

		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Sit);

		// ���� �ִٸ� ���� -> �ɱ��
		if (isSleeping)
		{
			dt = 0;
			lieToSit = true;
			return;
		}

		// �ɱ� -> �Ͼ��


		if (isSitting)
		{
			dt = 0;
			sitToStand = true;
			isSitting = false;
			return;
		}
		
		// �ɱ� ����
		dt = 0;
		isSitting = true;
		return;
	}

	// ���� �ִϸ��̼�, ���� ���¿��� �ɱ� ����
	if (inputManager->IsKeyState(KEY::LSHIFT, KEY_STATE::TAP))
	{
		if (isJumping || isBiting || isBiteMoving || isHoldBiting || isSmell)
			return;

		AudioManager::GetInstance()->StopAllEffect();
		AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Lie);

		// �ɱ� -> ����
		if (isSitting)
		{
			dt = 0;
			sitToLie = true;
			return;
		}

		if (isSleeping)
		{
			dt = 0;
			// ������ �Ͼ��
			lieToStand = true;	
			return;
		}

		dt = 0;
		isSleeping = true;
		return;
	}

	/// Ư�� �ൿ 	
	// ���� �ִϸ��̼�
	/// ���� �׽�Ʈ
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::TAP))
	{
		// �ɰų� ���� ���̰ų� ���� ������ ���� ���Ѵ�.
		if (isSitting || isJumping || isSleeping)
 			return;

		if (isMoving)
		{
			dt = 0;
			isBiteMoving = true;
			return;
		}

		// �׳� ����
		dt = 0;
		isBiting = true;

		return;
	}

	/// ���� �׽�Ʈ 
	// ���� ���� ��
	if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD))
	{
		if (isSitting || isJumping || isSleeping)
			return;
		
		isHoldBiting = true;	
	}

	// ���� �ִ� ���� ���� ��
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

	// ¢�� �ִϸ��̼�
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

		// ������ ¢��
		if (isSitting)
		{
			dt = 0;
			sitCrying = true;
			return;
		}

		// �����̸� ¢��
		if (isMoving)
		{
			dt = 0;
			walkCrying = true;
			return;
		}

		// ������ ¢��
		dt = 0;
		isCrying = true;
		return;
	}


	// �ñ� �ִϸ��̼�, ���� ���� �� ��� �Ұ�
	/// ���� �ְ� ����
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

	// �ִϸ��̼� ���� �߿��� �ٸ� �ִϸ��̼��� ������ �Ǹ� �ȵȴ�.

	// ���� ���� �� ��µ��� �ٸ� �� �Ұ���
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

	//���� �ִϸ��̼�
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

	// ���� �ִϸ��̼�
	if (isStanding)
	{
		if (isHoldBiting && isAttach)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBiteIdle)], dt);
			return;
		}
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogIdle)], dt);
	}

	// �ȴ� �ִϸ��̼�
	if (isMoving)
	{		
		if (isHoldBiting && isAttach)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogBiteWalk)], dt);
			return;
		}
		aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogWalk)], dt);
	}
	// ¢�� �ִϸ��̼�, ������ false�� ����
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

	// ���� �ִϸ��̼�
	if (isSmell || walkSmell || sitSmell)
	{
		if (walkSmell)
		{
			if (dt > 0.1f)
			{
				AudioManager::GetInstance()->StopAllEffect();
				AudioManager::GetInstance()->PlayEffect(EFFECT::Dog_Smell);
			}

			// idle -> �ñ� -> idle
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

			// sitToStand -> �ñ� -> idle
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

	// �ɴ� �ִϸ��̼�
	if (isSitting || sitToStand || sitToLie)
	{
	
		// �ɴ� ���¿��� �Ͼ�ٸ�?
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
		
		// �ɱ� -> ����
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
		
		// �ɴ°� ����
		if (sitLoop)
		{
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogSitLoop)], dt);
			return;
		}
	
		// �� �ִٰ� �ɱ�
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
 
	// ���� �ִϸ��̼�
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

	// ���� �ִϸ��̼� 
	if (isSleeping || lieToStand || lieToSit)
	{
		// ���ٰ� �Ͼ��
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

		// ���ٰ� �ɱ�
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

		// ���°� ����
		if (lieLoop)
		{
			// ������ ������ ������µ�?
			dt = 0.82;
			aObjectRender->ApplyAnimation(animationVector[static_cast<int>(DogAnimationState::DogStandToLie)], dt);
			return;
		}

		// �� �ִٰ� ����
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
	// ���⼭ Human ���� �ִϸ��̼��� Toggle�� �ް�
	
}

void Animation::HumanPlayAnimation()
{
	// Animation�� ����ȴ�. 
	// ������ �� �Ͼ �ִٰ� �ɰ� �ɱ� Loop -> ��Ż�� 
	// ���༭ �ۼ��� Cry Animation ���� -> ���� ����
	// ������ ¢���� ����, �Ͼ��, �����̰�, �����ϰ�, �� ���� -> �غ�

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
