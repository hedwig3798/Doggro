#pragma once
#include "headers.h"

/// <summary>
/// component의 기본적인 부모 클래스
/// 2024.01.16 chlaudrl
/// </summary>

class Entity;
class ManagerSet;
struct Collision;
class Collider;

class Component
{
public:
	Component(Entity* _entity, std::string _name);
	virtual ~Component();

	virtual void Start() {};
	virtual void Update(float _deltaTime) {};
	virtual void Render() {};
	virtual void Finalize() {};

	//충돌 관련 함수
	virtual void OnCollisionEnter(const Collision& _collision) {};
	virtual void OnCollisionExit(const Collision& _collision) {};

	virtual void OnTriggerExit(Collider* collider) {};
	virtual void OnTriggerEnter(Collider* collider) {};

	Entity* GetEntity() const { return entity; }
	void SetEntity(Entity* val) { entity = val; }

protected:
	Entity* entity;
	std::string name;
};
