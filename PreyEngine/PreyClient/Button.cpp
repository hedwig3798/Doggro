#include "Button.h"
#include "InputManager.h"
#include "ManagerSet.h"
#include "Entity.h"
#include "DrawType.h"
#include "PreyGameEngine.h"
#include "DrawType.h"

Button::Button(Entity* _entity)
	: Component(_entity, "Button")
	, sprites(std::vector<DrawType*>(4))
	, m_buttonState(ButtonState::Disabled)
	, isClick(false)
	, haveImage(true)
{
	managerSet = entity->GetManagerset();
}

Button::~Button()
{

}

void Button::Update(float _deltaTime)
{
	InputManager* inputManager = managerSet->GetInputManager();

	// 기본 이었다면
	if (m_buttonState != ButtonState::Disabled)
	{
		// 조건에 따라 버튼 상태를 점검한다.
		/// 버튼위에 있는가

		//	마우스의 x위치가 버튼의 left 보다 크고 right 보다 작다
		//	마우스의 y위치가 버튼의 top 보다 크고 bottom 보다 작다
		if (inputManager->GetCurrentMousePos().x > pos.left && inputManager->GetCurrentMousePos().x < pos.right &&
			inputManager->GetCurrentMousePos().y > pos.top && inputManager->GetCurrentMousePos().y < pos.bottom)
		{
			// 좌클릭
			if (inputManager->IsKeyState(KEY::LMOUSE,KEY_STATE::TAP))
			{
				// 버튼 영역 밖에서 누르면서 들어왔을 때 pressed 함수가 작동하는 것을 막음
				if (m_buttonState == ButtonState::Pressed)
				{
					m_buttonState = ButtonState::Pressed;
					OnPressed();
				}
			}

			// 마우스가 버튼 위에 있으면서 기본상태일 경우 
			if (m_buttonState == ButtonState::Normal)
			{
				// 상태를 호버링으로 바꿔준다.
				m_buttonState = ButtonState::Hover;
				OnHover();
			}

			if (m_buttonState == ButtonState::Hover)
			{
				OnHover();
			}

			// 마우스를 클릭 하면 -> onPress에 먼저 접근한다.
			if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD))
			{
				m_buttonState = ButtonState::Pressed;
				OnPressed();
			}
			// 이전 상태가 getkey down 또는 getkey 일때
			if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::AWAY))
			{
				m_buttonState = ButtonState::Normal;
				OnClick();
			}
		}
		else
		{
			m_buttonState = ButtonState::Normal;
		}
	}
}

void Button::Render()
{
	if (m_buttonState == ButtonState::Disabled || haveImage == false)
		return;
	this->sprites[static_cast<int>(this->m_buttonState)]->Render();
}

void Button::OnClick()
{
	if (m_buttonState == ButtonState::Disabled)
		return;
	isClick = !isClick;
	m_onClick();
}

void Button::OnPressed()
{
	if (m_buttonState == ButtonState::Disabled)
		return;
	m_onPress();
}

void Button::OnHover()
{
	if (m_buttonState == ButtonState::Disabled)
		return;
	m_onHover();
}

void Button::SetOnClick(std::function<void(void)> onClick)
{
	m_onClick = onClick;
}

void Button::SetOnPressed(std::function<void(void)> onPress)
{
	m_onPress = onPress;
}

void Button::SetOnHover(std::function<void(void)> onHover)
{
	m_onHover = onHover;
}

void Button::SetButtonPos(RECT _pos)
{
	pos = _pos;
	pos.top = managerSet->GetPreyGame()->GetScreenHeight() - pos.top;
	pos.bottom = managerSet->GetPreyGame()->GetScreenHeight() - pos.bottom;
}

void Button::SetImage(int _index, DrawType* _object)
{
	if (_index < 0 || _index >= sprites.size())
	{
		return;
	}

	sprites[_index] = _object;
}
