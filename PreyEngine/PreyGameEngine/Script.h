#pragma once
#include <string>
#include "Component.h"

struct Collision;
class Collider;

class Script : public Component
{
public:
	Script(Entity* _entity, std::string name);
	virtual ~Script();

	virtual void Update(double dt) abstract;
	virtual void Render(double dt) abstract {};
	virtual void Finalize() {};

	virtual void OnCollisionEnter(const Collision& collision) {};
	virtual void OnCollisionStay(const Collision& collision) {};
	virtual void OnCollisionExit(const Collision& collision) {};
	virtual void OnTriggerEnter(Collider* collider) {};
	virtual void OnTriggerStay(Collider* collider) {};
	virtual void OnTriggerExit(Collider* collider) {};

};

