#pragma once
#include "Component.h"
#include <functional>
#include "DrawType.h"

class Entity;
class ManagerSet;

enum class ButtonState
{
	Normal,		// �⺻
	Pressed,	// ����
	Hover,		// ���콺�� ���� ����
	Disabled	// ��ȣ �ۿ� x
};

class Button : public Component
{
public:
	Button(Entity* _entity);
	virtual ~Button();

	virtual void Update(float _deltaTime) override;
	virtual void Render() override;

	void OnClick();
	void OnPressed();
	void OnHover();

	// ��ư�� ��뿩�θ� ������!
	void SetDisabled() { m_buttonState = ButtonState::Disabled; }
	void SetEnable() { m_buttonState = ButtonState::Normal; }

	//void SetDisabled() { m_buttonState = ButtonState::Disabled; }
	//void SetEnable() { m_buttonState = ButtonState::Normal; }

	void SetOnClick(std::function<void(void)> onClick);
	void SetOnPressed(std::function<void(void)> onPress);
	void SetOnHover(std::function<void(void)> onHover);

	void SetButtonPos(RECT _pos);
	RECT pos;

	std::vector<DrawType*> sprites;
	void SetImage(int _index, DrawType* _object);

	bool isClick;
	bool haveImage;

private:
	std::function<void(void)> m_onClick = []() {};	// ���ٸ� �̿��ؼ� �⺻���� �־�����
	std::function<void(void)> m_onPress = []() {};
	std::function<void(void)> m_onHover = []() {};
	
	ButtonState m_buttonState;


	ManagerSet* managerSet;
};

