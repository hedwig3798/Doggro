#pragma once
#include "headers.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// AABB Tree를 만들기 위해서 AABB끼리의 관계
/// 2024.01.24 chlaudrl
/// </summary>

class Collider;

class AABB
{
public:
	AABB();
	AABB(const Vector3& _min, const Vector3& _max);

	//aabb 합치기 
	AABB Union(const AABB& _other) const;

	//부피 반환
	float GetVolume() const;

	//콜라이더가 확장한 박스 내부에 있는지 확인
	bool Contains(Collider* _collider) const;

	//충돌처리 확인
	bool IsCollision(const AABB& _other) const;

public:
	Vector3 minPoint;
	Vector3 maxPoint;
};

