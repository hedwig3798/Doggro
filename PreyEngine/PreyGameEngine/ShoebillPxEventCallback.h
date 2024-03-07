#pragma once

#include "Collider.h"
#include "PxPhysicsAPI.h"
#include "Define.h"
using namespace physx;

struct FilterGroup
{
	enum Enum
	{
		DEFAULT = (1 << 0),
		eSTATIC = (1 << 1),
		eBox = (1 << 2),
		eSPHERE = (1 << 3),
		eFILTER = (1<<4),

	};
};

physx::PxFilterFlags boxCollisionFilterShader(
	PxFilterObjectAttributes _attributes0, PxFilterData _filterData0,
	PxFilterObjectAttributes _attributes1, PxFilterData _filterData1,
	PxPairFlags& _pairFlags, const void* _constantBlock, PxU32 _constantBlockSize);

void SetUpFiltering(PxShape* _shape, PxU32 _filterGroup, PxU32 _filterMask);

class ShoebillPxEventCallback : public physx::PxSimulationEventCallback
{
public:
	virtual void onContact(const PxContactPairHeader& _pairHeader, const PxContactPair* _pairs, PxU32 _nbPairs) override;
	virtual void onTrigger(PxTriggerPair* _pairs, PxU32 _count) override;
	virtual void onWake(PxActor** _actors, PxU32 _count) {};
	virtual void onSleep(PxActor** _actors, PxU32 _count) {};
	virtual void onAdvance(const PxRigidBody* const* _bodyBuffer, const PxTransform* poseBuffer, const PxU32 _count) {};
	virtual void onConstraintBreak(PxConstraintInfo* _constraints, PxU32 _count) {};
};

//std::unordered_map<FilterGroup, PxU32> filters;



