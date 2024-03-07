#pragma once
#include "headers.h"
#include "Component.h"
#include "Define.h"

class Component;
class Collider;
struct Collision;
class CollsionManager;


/// <summary>
/// Entity : ������Ʈ�� ��� �׸��̴�.
/// 
/// 2023-12-28 KGIT 2C1P LYS
/// </summary>

class Component;
class Transform;
class Collider;
class Script;
class ManagerSet;

class Entity
{
public:
	//Entity();
	Entity(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type);
	virtual ~Entity();

	void Start();
	virtual void Update(float _deltaTime);
	void Render();
	void Finalize();

	void DestroyComponent();
	void DestroyAllComponent();

	OBJECT_TYPE GetType() const { return type; }
	void SetType(OBJECT_TYPE val) { type = val; }

	OBJECT_STATE GetState() const { return state; }
	void SetState(OBJECT_STATE val) { state = val; }

	std::string GetName() const { return name; }
	ManagerSet* GetManagerset() const { return managerset; }

	/*FilterGroup GetLayerCollision() const { return filter; }d
	void SetLayerCollision(const FilterGroup n);*/

	/// ������Ʈ �߰� �� ��������
public:
	template<typename T>
	void CreateComponent(Entity* _entity);
	
	template<typename T>
	void CreateComponent2(Entity* _entity, CollsionManager* _collisionmanager);

	template<typename T>
	T* GetComponent();

public:
	//�浹 ���� �Լ�
	void OnCollisionEnter(const Collision& _collision);
	//void OnCollisionStay(const Collision& _collision);
	void OnCollisionExit(const Collision& _collision);


	void OnTriggerEnter(Collider* _otherCollider);
	//void OnTriggerStay(const Collision& _collision);
	void OnTriggerExit(Collider* _otherCollider);

	void LoadMapLoader();

private:
	//�ϴ� ���Ϳ� component���� ��´�.
	std::vector<Component*> componentList;

	std::string name;
	OBJECT_TYPE type;
	OBJECT_STATE state;
	ManagerSet* managerset;
	bool isActive;
	//FilterGroup filter;
};

/// <summary>
/// ������Ʈ�� ���Ϳ��ٰ� �߰��Ѵ�.
/// </summary>
template<typename T>
void Entity::CreateComponent(Entity* _entity)
{
	T* _component = new T(_entity);
	if (GetComponent<T>() != nullptr)
	{
		return;
	}

	componentList.push_back(_component);

}

template<typename T>
void Entity::CreateComponent2(Entity* _entity, CollsionManager* _collisionmanager)
{
	T* _component = new T(_entity, _collisionmanager);
	if (GetComponent<T>() != nullptr)
	{
		return;
	}

	componentList.push_back(_component);

}

/// <summary>
/// ������Ʈ���� ����ִ� ���͵��� ��ȸ�ϸ鼭 ���ϴ� type�� ������Ʈ�� ������ return �Ѵ�.
/// ������ nullptr�� return�Ѵ�.
/// </summary>
template<typename T>
T* Entity::GetComponent()
{
	for (auto& e : componentList)
	{
		T* newComponet = dynamic_cast<T*>(e);

		if (newComponet != nullptr)
		{
			return newComponet;
		}
	}
	return nullptr;
}

