#pragma once
#include <string>

#include "Define.h"
#include "Component.h"

class QuestManager;

class HumanScript : public Component
{
public:
	HumanScript(Entity* _entity);
	virtual ~HumanScript();

public:
	virtual void OnCollisionEnter(const Collision& _collision) override;
	virtual void OnCollisionExit(const Collision& _collision) override;

	virtual void OnTriggerEnter(Collider* collider) override;
	virtual void OnTriggerExit(Collider* collider) override;

	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }

private:
	QuestManager* questManager;
};

