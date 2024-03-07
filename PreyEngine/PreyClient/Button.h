#pragma once
#include "Component.h"
#include <functional>
#include "DrawType.h"

class Entity;
class ManagerSet;

enum class ButtonState
{
	Normal,		// 기본
	Pressed,	// 눌림
	Hover,		// 마우스가 위에 있음
	Disabled	// 상호 작용 x
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

	// 버튼의 사용여부를 정해줘!
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
	std::function<void(void)> m_onClick = []() {};	// 람다를 이용해서 기본값을 넣어주자
	std::function<void(void)> m_onPress = []() {};
	std::function<void(void)> m_onHover = []() {};
	
	ButtonState m_buttonState;


	ManagerSet* managerSet;
};

