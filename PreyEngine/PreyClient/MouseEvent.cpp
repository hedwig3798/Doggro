#include "MouseEvent.h"
#include "ManagerSet.h"
#include "Transform.h"
#include "Entity.h"
#include "InputManager.h"

MouseEvent::MouseEvent(Entity* _entity)
	: Component(_entity, "MouseEvent")
	, isMouseOn(false)
	, isMouseLBTNUp(false)
{
	managerSet = entity->GetManagerset();
}

MouseEvent::~MouseEvent()
{

}

void MouseEvent::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();
	Transform* transform = entity->GetComponent<Transform>();

	POINT mousePos = inputManager->GetCurrentMousePos();
	Vector3 scale = transform->GetScale();
	Vector3 position = transform->GetPosition();

	Vector3 Min = position - scale * 0.5f;
	Vector3 Max = position + scale * 0.5f;

	if (Min.x <= mousePos.x && Min.y <= mousePos.y
		&& Max.x >= mousePos.x && Max.y >= mousePos.y
		&& inputManager->IsKeyState(KEY::LMOUSE,KEY_STATE::TAP))
	{
		isMouseOn = true;
		isMouseLBTNUp = true;
	}
	else
	{
		isMouseOn = false;
		isMouseLBTNUp = false;
	}

}

void MouseEvent::Render()
{

}
