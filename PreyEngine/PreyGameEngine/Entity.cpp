#include "Entity.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "Component.h"
#include "Script.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

//Entity::Entity()
//{
//	//트랜스폼은 항상 들고 있어야함
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
	// 여기서 Fobject를 render 한다?
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
	// 이름이 있다며 Physx, asdf, efd, asdf
	

	// for (auto aobject : !@vector)
	//{
	//	안에 벡터를 가져와서 new Entity 만든다.
	//  그 안에 있는 Transform, Collider Type을 확인, RenderType 정보를 넘긴다.
	//  그러면 기본 세팅 끝.
	//}

	// Transform 은 Matrix 형태
	// Collider Type은 std::string
	// Render Type은 저쪽에서 해 주기로

}
