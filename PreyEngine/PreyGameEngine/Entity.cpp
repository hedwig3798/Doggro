#include "Entity.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "Component.h"
#include "Script.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

//Entity::Entity()
//{
//	//Ʈ�������� �׻� ��� �־����
//	CreateComponent<Transform>();
//	GetComponent<Transform>();
//}

Entity::Entity(std::string _name, ManagerSet* _managerSet, OBJECT_TYPE _type)
	: name(_name)
	, managerset(_managerSet)
	, type(_type)
{
	CreateComponent<Transform>(this);
	//GetComponent<Transform>();
}

Entity::~Entity()
{
	DestroyAllComponent();
}

void Entity::Start()
{

}

void Entity::Update(float _deltaTime)
{
	for (auto component : componentList)
	{
		if (component == nullptr)
		{
			return;
		}
		else component->Update(_deltaTime);
	}
}

void Entity::Render()
{
	// ���⼭ Fobject�� render �Ѵ�?
// 	if (!isActive)
// 		return;
	
	for (auto component : componentList)
	{
		if (component == nullptr)
		{
			return;
		}
		else component->Render();
	}
}

void Entity::Finalize()
{
	for (auto component : componentList)
	{
		if (component == nullptr)
		{
			return;
		}
		else component->Finalize();
	}
}

void Entity::DestroyComponent()
{
	Finalize();
}

void Entity::DestroyAllComponent()
{
	for (auto component : componentList)
		delete component;
}

//void Entity::SetLayerCollision(const FilterGroup n)
//{
//	filter = n;
//
//	BoxCollider* boxCollider = GetComponent<BoxCollider>();
//	SphereCollider* sphereCollider = GetComponent<SphereCollider>();
//
//	if (boxCollider) boxCollider->SetLayerCollision(n);
//	if (sphereCollider) sphereCollider->SetLayerCollision(n);
//}

void Entity::OnCollisionEnter(const Collision& _collision)
{
	for (auto& component : componentList)
	{
		component->OnCollisionEnter(_collision);

		std::string name = _collision.otherCollider->GetEntity()->GetName();
	}
}

//void Entity::OnCollisionStay(const Collision& _collision)
//{
//	if (!isActive)
//		return;
//	for (auto& component : componentList)
//		component->OnCollisionStay(_collision);
//}

void Entity::OnCollisionExit(const Collision& _collision)
{
	if (_collision.otherCollider == nullptr || _collision.thisCollider == nullptr)
		return;

	for (auto& component : componentList)
	{
		if (component != nullptr)
		{
			component->OnCollisionExit(_collision);
		}
	}
		
}

void Entity::OnTriggerEnter(Collider* _otherCollider)
{
	
	for (auto& component : componentList)
		component->OnTriggerEnter(_otherCollider);
}

//void Entity::OnTriggerStay(const Collision& _collision)
//{
//	if (!isActive)
//		return;
//	for (auto& component : componentList)
//		component->OnTriggerStay(_collision);
//}

void Entity::OnTriggerExit(Collider* _otherCollider)
{
	
	for (auto& component : componentList)
		component->OnTriggerExit(_otherCollider);
}

void Entity::LoadMapLoader()
{
	// �̸��� �ִٸ� Physx, asdf, efd, asdf
	

	// for (auto aobject : !@vector)
	//{
	//	�ȿ� ���͸� �����ͼ� new Entity �����.
	//  �� �ȿ� �ִ� Transform, Collider Type�� Ȯ��, RenderType ������ �ѱ��.
	//  �׷��� �⺻ ���� ��.
	//}

	// Transform �� Matrix ����
	// Collider Type�� std::string
	// Render Type�� ���ʿ��� �� �ֱ��

}
