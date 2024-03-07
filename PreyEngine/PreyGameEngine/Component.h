#pragma once
#include "headers.h"

/// <summary>
/// component�� �⺻���� �θ� Ŭ����
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

	//�浹 ���� �Լ�
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
