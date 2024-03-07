#pragma once
#include "headers.h"
#include "SimpleMath.h"
#include "AABB.h"
#include "AABBNode.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// AABB Tree를 만들어 충돌체를 감싸자
/// 2024.01.24 chlaudrl
/// </summary>

class Collider;
class CollisionManager;

class AABBTree
{
public:
	AABBTree(float _margin, CollisionManager* _collisonManager);
	~AABBTree();

	void AddCollider(Collider* _collider);
	void RemoveCollider(Collider* _collider);
	void Update();
	void Remove(Collider* _collider);
	std::list<std::pair<Collider*, Collider*>>& GetCollisionPairs();
	void Clear();

private:
	void UpdateAllNode(AABBNode* _node);
	void InsertNode(AABBNode* _node, AABBNode** _parent);
	void RemoveNode(AABBNode* _node);
	void ComputeCollisionPairs(AABBNode* _node1, AABBNode* _node2);
	void ClearChildrenCrossFlag(AABBNode* _node);
	void CrossChildren(AABB* _node);

private:
	AABBNode* root;
	std::list<std::pair<Collider*, Collider*>> pairs;
	const float margin;

	CollisionManager* collisionManager;
	std::vector<AABBNode*> invalidNodes;
	std::vector<AABBNode*> removeNodes;

};

