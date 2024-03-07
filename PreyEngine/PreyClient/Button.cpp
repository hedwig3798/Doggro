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

	// �⺻ �̾��ٸ�
	if (m_buttonState != ButtonState::Disabled)
	{
		// ���ǿ� ���� ��ư ���¸� �����Ѵ�.
		/// ��ư���� �ִ°�

		//	���콺�� x��ġ�� ��ư�� left ���� ũ�� right ���� �۴�
		//	���콺�� y��ġ�� ��ư�� top ���� ũ�� bottom ���� �۴�
		if (inputManager->GetCurrentMousePos().x > pos.left && inputManager->GetCurrentMousePos().x < pos.right &&
			inputManager->GetCurrentMousePos().y > pos.top && inputManager->GetCurrentMousePos().y < pos.bottom)
		{
			// ��Ŭ��
			if (inputManager->IsKeyState(KEY::LMOUSE,KEY_STATE::TAP))
			{
				// ��ư ���� �ۿ��� �����鼭 ������ �� pressed �Լ��� �۵��ϴ� ���� ����
				if (m_buttonState == ButtonState::Pressed)
				{
					m_buttonState = ButtonState::Pressed;
					OnPressed();
				}
			}

			// ���콺�� ��ư ���� �����鼭 �⺻������ ��� 
			if (m_buttonState == ButtonState::Normal)
			{
				// ���¸� ȣ�������� �ٲ��ش�.
				m_buttonState = ButtonState::Hover;
				OnHover();
			}

			if (m_buttonState == ButtonState::Hover)
			{
				OnHover();
			}

			// ���콺�� Ŭ�� �ϸ� -> onPress�� ���� �����Ѵ�.
			if (inputManager->IsKeyState(KEY::LMOUSE, KEY_STATE::HOLD))
			{
				m_buttonState = ButtonState::Pressed;
				OnPressed();
			}
			// ���� ���°� getkey down �Ǵ� getkey �϶�
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
