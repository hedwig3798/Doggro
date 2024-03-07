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

//���ο� �ݶ��̴��� Ʈ���� �Է�
void AABBTree::AddCollider(Collider* _collider)
{
	//�����
	AABBNode* node = new AABBNode();

	//node�� collider ����
	_collider->SetNode(node);
	node->collider = _collider;

	//��Ʈ�� �ִ� ���
	if (root)
	{
		node->SetLeaf(_collider);
		node->Update(margin);
		InsertNode(node, &root);
	}
	//��Ʈ�� ���� ���
	else
	{
		root = node;
		root->SetLeaf(_collider);
		root->Update(margin);
	}
}

//�ش� �ݶ��̴��� ��� ����
void AABBTree::RemoveCollider(Collider* _collider)
{
	//�ݶ��̴��� ��� ��������
	AABBNode* node = _collider->GetNode();

	//�ش� ����� �ݶ��̴� �����
	node->collider = nullptr;
	//�ݶ��̴��� �ִ� ��� ���� �����
	_collider->SetNode(nullptr);

	RemoveNode(node);
}

//������Ʈ aabb tree�� ��带 ��� ������Ʈ
void AABBTree::Update()
{
	//��Ʈ���� ����
	if (root)
	{
		//��Ʈ�� ���� ���̶��
		if (root->IsLeaf())
		{
			//��Ʈ�� ���������� ���
			if (root->collider->GetEntity()->GetState() == OBJECT_STATE::DESTROY)
			{
				RemoveCollider(root->collider);
			}
			//��Ʈ�� ������ �ƴ� ��� ��Ʈ ������Ʈ
			else
				root->Update(margin);
		}
		//��Ʈ�� �ǹ��� �ƴ� ���
		else
		{
			//�ϴ� �ʱ�ȭ
			invalidNodes.clear();
			removeNodes.clear();
			//�ʱ�ȭ �� �ٽ� ��ȿ, ���� ���
			UpdateAllNode(root);

			//���������� ������Ʈ�� Ʈ�� ����
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
