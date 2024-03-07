#pragma once
#include <string>

#include "Define.h"
#include "Component.h"

class AObject;

class QuestManager;

class DogSightScript : public Component
{
public:
	DogSightScript(Entity* _entity);
	virtual ~DogSightScript();

public:
	virtual void OnCollisionEnter(const Collision& collision) override;
	virtual void OnCollisionExit(const Collision& collision) override;

	virtual void OnTriggerEnter(Collider* collider) override;
	virtual void OnTriggerExit(Collider* collider) override;

public:
	std::string checkName;
	std::string setName() { return checkName; };
};

