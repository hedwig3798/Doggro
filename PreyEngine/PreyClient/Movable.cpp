#include "Movable.h"
#include "Entity.h"
#include "Transform.h"

#include "ManagerSet.h"
#include "InputManager.h"
#include "SoundManager.h"

Movable::Movable(Entity* _entity)
	: Component(_entity, "Movable"), managerSet{}
{
	managerSet = _entity->GetManagerset();
}

Movable::~Movable()
{

}

void Movable::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();
	Transform* transform = GetEntity()->GetComponent<Transform>();

	// left
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(5.0f * _deltaTime, 0.1f, 0.0f));
	}

	// right
	if (inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(-5.0f * _deltaTime, 0.1f, 0.0f));
	}

	// front
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(0.0f, 0.1f, -5.0f * _deltaTime));
	}

	// back
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(0.0f, 0.1f, 5.0f * _deltaTime));
	}

	// Space ??
	if (inputManager->IsKeyState(KEY::SPACE, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(0.0f, 5.0f * _deltaTime, 0.0f));
		SoundManager::GetInstance()->StopEffect(EFFECTSOUND::TESTEFFECT);
		SoundManager::GetInstance()->PlayEffect(EFFECTSOUND::TESTEFFECT);
	}

	// x 회전
	if (inputManager->IsKeyState(KEY::J, KEY_STATE::HOLD))
	{
		transform->AddXAxisRotation(5.0f * _deltaTime);
		SoundManager::GetInstance()->AddAllEffectVolume(0.01f);
	}

	// y 회전
	if (inputManager->IsKeyState(KEY::K, KEY_STATE::HOLD))
	{
		transform->AddYAxisRotation(5.0f * _deltaTime);
		SoundManager::GetInstance()->SubAllEffectVolume(0.01f);
	}

	// z 회전
	if (inputManager->IsKeyState(KEY::L, KEY_STATE::HOLD))
	{
		transform->AddZAxisRotation(5.0f * _deltaTime);
	}

	// Reset
	if (inputManager->IsKeyState(KEY::G, KEY_STATE::TAP))
	{
		transform->SetPosition(Vector3(0.0f, 10.0f, 0.0f));
		transform->SetRotation(Quaternion(0.f, 0.f, 0.0f, 1.0f));
		transform->SetScale(Vector3(1.0f, 1.0f, 1.0f));
	}
}
