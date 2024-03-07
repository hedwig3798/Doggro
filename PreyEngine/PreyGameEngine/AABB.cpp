#include "AABB.h"
#include "Collider.h"

AABB::AABB()
	:minPoint(Vector3::Zero)
	,maxPoint(Vector3::Zero)
{

}

AABB::AABB(const Vector3& _min, const Vector3& _max)
	:minPoint(_min)
	,maxPoint(_max)
{

}

AABB AABB::Union(const AABB& _other) const
{
	AABB tmp = AABB();

	tmp.minPoint.x = min(minPoint.x, _other.minPoint.x);
	tmp.minPoint.y = min(minPoint.y, _other.minPoint.y);
	tmp.minPoint.z = min(minPoint.z, _other.minPoint.z);
	tmp.maxPoint.x = max(maxPoint.x, _other.maxPoint.x);
	tmp.maxPoint.y = max(maxPoint.y, _other.maxPoint.y);
	tmp.maxPoint.z = max(maxPoint.z, _other.maxPoint.z);

	return tmp;
}

float AABB::GetVolume() const
{
	Vector3 length = (maxPoint - minPoint);
	return length.x * length.y * length.z;
}

bool AABB::Contains(Collider* _collider) const
{
	Vector3 colliderMax;
	Vector3 colliderMin;

	_collider->GetMinMaxPoint(colliderMin, colliderMax);

	if (minPoint.x <= colliderMin.x && minPoint.y <= colliderMin.y && minPoint.z <= colliderMin.z
		&& maxPoint.x >= colliderMax.x && maxPoint.y >= colliderMax.y && maxPoint.z >= colliderMax.z)
	{
		return true;
	}

	return false;
}

bool AABB::IsCollision(const AABB& _other) const
{
	if (minPoint.x <= _other.maxPoint.x && maxPoint.x >= _other.minPoint.x
		&& minPoint.y <= _other.maxPoint.y && maxPoint.y >= _other.minPoint.y
		&& minPoint.z <= _other.maxPoint.z && maxPoint.z >= _other.minPoint.z)
		return true;
	return false;
}
