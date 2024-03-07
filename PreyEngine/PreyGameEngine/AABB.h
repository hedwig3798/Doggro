#pragma once
#include "headers.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// AABB Tree�� ����� ���ؼ� AABB������ ����
/// 2024.01.24 chlaudrl
/// </summary>

class Collider;

class AABB
{
public:
	AABB();
	AABB(const Vector3& _min, const Vector3& _max);

	//aabb ��ġ�� 
	AABB Union(const AABB& _other) const;

	//���� ��ȯ
	float GetVolume() const;

	//�ݶ��̴��� Ȯ���� �ڽ� ���ο� �ִ��� Ȯ��
	bool Contains(Collider* _collider) const;

	//�浹ó�� Ȯ��
	bool IsCollision(const AABB& _other) const;

public:
	Vector3 minPoint;
	Vector3 maxPoint;
};

