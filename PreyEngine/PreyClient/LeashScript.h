#pragma once
#include <string>

#include "Define.h"
#include "Component.h"

class QuestManager;

class LeashScript : public Component
{
public:
	LeashScript(Entity* _entity);
	virtual ~LeashScript();

public:
	virtual void OnCollisionEnter(const Collision& _collision) override;
	virtual void OnCollisionExit(const Collision& _collision) override;

	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }

private:
	QuestManager* questManager;
};

