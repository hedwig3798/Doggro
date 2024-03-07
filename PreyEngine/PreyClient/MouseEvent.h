#pragma once
#include <Component.h>

class Entity;
class ManagerSet;

class MouseEvent : public Component
{
public:
	MouseEvent(Entity* _entity);
	virtual ~MouseEvent();

	virtual void Update(float _deltaTime) override;
	virtual void Render() override;

	bool GetIsMouseOn() const { return isMouseOn; }
	void SetIsMouseOn(bool val) { isMouseOn = val; }

	bool GetIsMouseLBTNUp() const { return isMouseLBTNUp; }
	void SetIsMouseLBTNUp(bool val) { isMouseLBTNUp = val; }
private:
	ManagerSet* managerSet;

	bool isMouseOn;
	bool isMouseLBTNUp;

};

