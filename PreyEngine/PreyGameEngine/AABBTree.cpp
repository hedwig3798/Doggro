#include "AABBTree.h"
#include "Collider.h"
#include "Entity.h"
#include "CollsionManager.h"

AABBTree::AABBTree(float _margin, CollisionManager* _collisonManager)
	:root(nullptr)
	,pairs{}
	,margin(_margin)
	,collisionManager(_collisonManager)
	,invalidNodes{}
	,removeNodes{}
{

}

AABBTree::~AABBTree()
{
	Clear();
}

//새로운 콜라이더를 트리에 입력
void AABBTree::AddCollider(Collider* _collider)
{
	//새노드
	AABBNode* node = new AABBNode();

	//node와 collider 연결
	_collider->SetNode(node);
	node->collider = _collider;

	//루트가 있는 경우
	if (root)
	{
		node->SetLeaf(_collider);
		node->Update(margin);
		InsertNode(node, &root);
	}
	//루트가 없는 경우
	else
	{
		root = node;
		root->SetLeaf(_collider);
		root->Update(margin);
	}
}

//해당 콜라이더의 노드 제거
void AABBTree::RemoveCollider(Collider* _collider)
{
	//콜라이더의 노드 가져오기
	AABBNode* node = _collider->GetNode();

	//해당 노드의 콜라이더 지우기
	node->collider = nullptr;
	//콜라이더에 있는 노드 정보 지우기
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

//업데이트 aabb tree의 노드를 모드 업데이트
void AABBTree::Update()
{
	//루트부터 시작
	if (root)
	{
		//루트가 제일 밑이라면
		if (root->IsLeaf())
		{
			//루트가 삭제예정일 경우
			if (root->collider->GetEntity()->GetState() == OBJECT_STATE::DESTROY)
			{
				RemoveCollider(root->collider);
			}
			//루트가 삭제가 아닌 경우 루트 업데이트
			else
				root->Update(margin);
		}
		//루트가 맨밑이 아닌 경우
		else
		{
			//일단 초기화
			invalidNodes.clear();
			removeNodes.clear();
			//초기화 후 다시 유효, 삭제 노드
			UpdateAllNode(root);

			//삭제예정인 오브젝트를 트리 제거
			for (AABBNode* node : removeNodes)
				RemoveCollider(node->collider);
			for (AABBNode* node : invalidNodes)
			{
				AABBNode* parent = node->parent;
				AABBNode* sibling = node->GetSibling();
				AABBNode** parentLink = parent->parent
					? (parent == parent->parent->children[0])
					? &parent->parent->children[0]
					: &parent->parent->children[1]
					: &root;

				sibling->parent = parent->parent ? parent->parent : nullptr;
				*parentLink = sibling;
				delete parent;

				node->Update(margin);
				InsertNode(node, &root);
			}
			invalidNodes.clear();
			removeNodes.clear();
		}
	}
}

void AABBTree::Remove(Collider* _collider)
{
	AABBNode* node = _collider->GetNode();
	node->collider = nullptr;
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

std::list<std::pair<Collider*, Collider*>>& AABBTree::GetCollisionPairs()
{
	pairs.clear();

	if (!root || root->IsLeaf())
		return pairs;
	ClearChildrenCrossFlag(root);
	ComputeCollisionPairs(root->children[0], root->children[1]);

	return pairs;
}

void AABBTree::Clear()
{

}

void AABBTree::UpdateAllNode(AABBNode* _node)
{

}

void AABBTree::InsertNode(AABBNode* _node, AABBNode** _parent)
{

}

void AABBTree::RemoveNode(AABBNode* _node)
{

}

void AABBTree::ComputeCollisionPairs(AABBNode* _node1, AABBNode* _node2)
{

}

void AABBTree::ClearChildrenCrossFlag(AABBNode* _node)
{

}

void AABBTree::CrossChildren(AABB* _node)
{

}
