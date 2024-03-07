#pragma once

#include "foundation/PxErrorCallback.h"
#include "PxPhysXConfig.h"

namespace physx
{
	class ShoebillPxErrorCallback : public PxErrorCallback
	{
	public:
		ShoebillPxErrorCallback();
		virtual ~ShoebillPxErrorCallback();

		virtual void reportError(PxErrorCode::Enum code, const char* message, const char* file, int line) PX_OVERRIDE;
	};
}

