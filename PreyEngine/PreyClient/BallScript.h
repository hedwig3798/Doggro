#pragma once
#include <string>

#include "Define.h"
#include "Component.h"

class QuestManager;

class BallScript :public Component
{
public:
	BallScript(Entity* _entity);
	virtual ~BallScript();

public:
	virtual void OnCollisionEnter(const Collision& _collision) override;
	virtual void OnCollisionExit(const Collision& _collision) override;

	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }

private:
	QuestManager* questManager;
};

