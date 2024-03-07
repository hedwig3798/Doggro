#include "AABBNode.h"
#include "AABB.h"
#include "Collider.h"

AABBNode::AABBNode()
	:parent(nullptr)
	,children{nullptr, nullptr}
	,crossedChildren(false)
	,aabb{}
	,collider(nullptr)
{

}

AABBNode::~AABBNode()
{

}

void AABBNode::AddChild(AABBNode* _a, AABBNode* _b)
{
	this->children[0] = _a;
	this->children[1] = _b;

	_a->parent = this;
	_b->parent = this;
}

void AABBNode::SetLeaf(Collider* _collider)
{
	this->collider = _collider;
	children[0] = nullptr;
	children[1] = nullptr;
}

void AABBNode::Update(float _margine)
{
	if (IsLeaf())
	{
		Vector3 marginVec3(_margine, _margine, _margine);

		collider->GetMinMaxPoint(aabb.minPoint, aabb.maxPoint);

		aabb.minPoint -= marginVec3;
		aabb.maxPoint += marginVec3;
	}
	else
		aabb = children[0]->aabb.Union(children[1]->aabb);
}

AABBNode* AABBNode::GetSibling()
{
	assert(parent);
	return this == parent->children[0] ? parent->children[1] : parent->children[0];
}
