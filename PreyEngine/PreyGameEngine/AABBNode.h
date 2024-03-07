#pragma once
#include "headers.h"
#include "SimpleMath.h"
#include "AABB.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// AABB Tree의 노드 클래스 
/// 계층구조 정립
/// 2024.01.24 chlaudrl
/// </summary>

class Collider;

class AABBNode
{
public:
	AABBNode();
	~AABBNode();

	bool IsLeaf() { return children[0] == nullptr; }
	void AddChild(AABBNode* _a, AABBNode* _b);
	void SetLeaf(Collider* _collider);
	void Update(float _margine);
	AABBNode* GetSibling();

public:
	AABBNode* parent;
	AABBNode* children[2];
	bool crossedChildren;
	AABB aabb;
	Collider* collider;
};

