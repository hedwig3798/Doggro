#pragma once
#include <string>

#include "Define.h"
#include "Component.h"

class QuestManager;

class CalenderScript : public Component
{
public:
	CalenderScript(Entity* _entity);
	virtual ~CalenderScript();

public:
	virtual void OnCollisionEnter(const Collision& _collision) override;
	virtual void OnCollisionExit(const Collision& _collision) override;

	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }

private:
	QuestManager* questManager;
};

