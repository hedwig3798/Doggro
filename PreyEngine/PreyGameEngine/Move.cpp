#include "Move.h"
#include "InputManager.h"
#include "ManagerSet.h"
#include "RenderType.h"
#include "Entity.h"
#include "Transform.h"
#include "SimpleMath.h"
#include "Collider.h"
#include "SphereCollider.h"

Move::Move(Entity* _entity)
	: Component(_entity, "Move"), managerSet{}
{
	managerSet = _entity->GetManagerset();
}

Move::~Move()
{

}

void Move::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();
	Transform* transform = GetEntity()->GetComponent<Transform>();
	Collider* collider = GetEntity()->GetComponent<Collider>();

	// left
	if (inputManager->IsKeyState(KEY::A, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(10.0f * _deltaTime, 0.0f, 0.0f));
		collider->AddForce(Vector3(100.f, 0.0f, 0.0f), ForceMode::Force);
	}

	// right
	if (inputManager->IsKeyState(KEY::D, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(-10.0f * _deltaTime, 0.0f, 0.0f));
	}

	// front
	if (inputManager->IsKeyState(KEY::W, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(0.0f, 0.0f, -10.0f * _deltaTime));
	}

	// back
	if (inputManager->IsKeyState(KEY::S, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(0.f, 0.0f, 10.0f * _deltaTime));
	}

	// Space ??
	if (inputManager->IsKeyState(KEY::SPACE, KEY_STATE::HOLD))
	{
		transform->AddPosition(Vector3(0.0f, 150.0f * _deltaTime, 0.0f));
	}
	
	// x 회전
	if (inputManager->IsKeyState(KEY::J, KEY_STATE::HOLD))
	{
		transform->AddXAxisRotation(1.0f * _deltaTime);
	}

	// y 회전
	if (inputManager->IsKeyState(KEY::K, KEY_STATE::HOLD))
	{
		transform->AddYAxisRotation(1.0f * _deltaTime);
	}

	// z 회전
	if (inputManager->IsKeyState(KEY::L, KEY_STATE::HOLD))
	{
		transform->AddZAxisRotation(1.0f * _deltaTime);
	}

	// Reset
	if (inputManager->IsKeyState(KEY::G, KEY_STATE::TAP))
	{
		transform->SetPosition(Vector3(0.0f, 10.0f, 0.0f));
		transform->SetRotation(Quaternion(0.f, 0.f, 0.0f, 1.0f));
		transform->SetScale(Vector3(1.0f, 1.0f, 1.0f));
	}

}
