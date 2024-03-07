#include "ShoebillPxEventCallback.h"
#include "headers.h"
#include "Collider.h"

void ShoebillPxEventCallback::onContact(const PxContactPairHeader& _pairHeader, const PxContactPair* _pairs, PxU32 _nbPairs)
{
	//1. 일단 이 함수가 어떤 걸 인자로 받는지 무슨 역할을 하는지
	//2. 충돌 정보를 가져오거나 그걸 담는게 필요할 거 같다
	//3. nbpairs는 중복처리가 가능하다 
	//4. 일단 해보자

	for (int i = 0; i < _nbPairs; i++)
	{
		const PxContactPair& cp = _pairs[i];

		ColliderInfo* colliderInfo1 = static_cast<ColliderInfo*>(_pairHeader.actors[0]->userData);
		ColliderInfo* colliderInfo2 = static_cast<ColliderInfo*>(_pairHeader.actors[1]->userData);

		Collider* collider1 = (colliderInfo1) ? colliderInfo1->collider : nullptr;
		Collider* collider2 = (colliderInfo2) ? colliderInfo2->collider : nullptr;

		if (_pairHeader.actors[0]->userData == nullptr || _pairHeader.actors[1]->userData == nullptr)
			return;

		if (cp.events & (PxPairFlag::eNOTIFY_TOUCH_FOUND))
		{
			if (collider1 && collider2)
			{
				
				CollisionInfo collision1{ colliderInfo1, colliderInfo2 };
				collider1->OnCollisionEnter(collision1);

				CollisionInfo collision2{ colliderInfo2, colliderInfo1 };
				collider2->OnCollisionEnter(collision2);
			}
		}
		if (cp.events & (PxPairFlag::eNOTIFY_TOUCH_LOST))
		{
			if (collider1 && collider2)
			{
				CollisionInfo collision1{ colliderInfo1, colliderInfo2 };
				collider1->OnCollisionExit(collision1);

				CollisionInfo collision2{ colliderInfo2, colliderInfo1 };
				collider2->OnCollisionExit(collision2);
			}
		}
	}

	// 변수 값 출력
	/*wchar_t buffer[100];
	swprintf(buffer, L"yaw: %f, pitch : %f\n", _nbPairs, _nbPairs);
	OutputDebugString(buffer);*/
}

void ShoebillPxEventCallback::onTrigger(PxTriggerPair* _pairs, PxU32 _count)
{
	while (_count--)
	{
		const PxTriggerPair& current = *_pairs++;

		const PxActor* actor1 = current.triggerActor;
		const PxActor* actor2 = current.otherActor;

		ColliderInfo* colliderInfo1 = static_cast<ColliderInfo*>(actor1->userData);
		ColliderInfo* colliderInfo2 = static_cast<ColliderInfo*>(actor2->userData);

		Collider* collider1 = nullptr;
		Collider* collider2 = nullptr;

		if (colliderInfo1) collider1 = colliderInfo1->collider;
		if (colliderInfo2) collider2 = colliderInfo2->collider;

		if (actor2->userData == nullptr || actor1->userData == nullptr)
			return;

		if (current.status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
		{
			if (collider1 && collider2)
			{
				//1에게 보낼 데이터
				collider1->OnTriggerEnter(colliderInfo2);

				//2에게 보낼 데이터
				collider2->OnTriggerEnter(colliderInfo1);
			}
		}

		if (current.status & PxPairFlag::eNOTIFY_TOUCH_LOST)
		{
			if (collider1 && collider2)
			{
				//1에게 보낼 데이터
				if (collider1 != nullptr) collider1->OnTriggerExit(colliderInfo2);

				//2에게 보낼 데이터
				if (collider2 != nullptr) collider2->OnTriggerExit(colliderInfo1);
			}
		}
	}
}


physx::PxFilterFlags boxCollisionFilterShader(PxFilterObjectAttributes _attributes0, PxFilterData _filterData0,
	PxFilterObjectAttributes _attributes1, PxFilterData _filterData1, 
	PxPairFlags& _pairFlags, const void* _constantBlock, PxU32 _constantBlockSize)
{
	//return PxFilterFlag::eSUPPRESS;

	// let triggers through
	//두 객체 중 하나가 트리거인 경우 기본 트리거 동작을 수행하고, 그렇지 않으면 객체간의 기본 충돌 감지 수행
	if (PxFilterObjectIsTrigger(_attributes0) || PxFilterObjectIsTrigger(_attributes1))
	{
		_pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		return PxFilterFlag::eDEFAULT;
	}

	// generate contacts for all that were not filtered above
	_pairFlags = PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_FOUND | PxPairFlag::eNOTIFY_TOUCH_LOST;

	// 충돌을 무시할 아이들
	if ((_filterData0.word0 & _filterData1.word1) && (_filterData1.word0 & _filterData0.word1))
	{
		return PxFilterFlag::eSUPPRESS;
	}

	/*if (!(_filterData0.word0 & _filterData1.word1) && !(_filterData1.word0 & _filterData0.word1))
		_pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;*/

	return PxFilterFlag::eDEFAULT;
}

void SetUpFiltering(PxShape* _shape, PxU32 _filterGroup, PxU32 _filterMask)
{
	PxFilterData filterData;
	filterData.word0 = _filterGroup;
	filterData.word1 = _filterMask;
	_shape->setSimulationFilterData(filterData);
}
