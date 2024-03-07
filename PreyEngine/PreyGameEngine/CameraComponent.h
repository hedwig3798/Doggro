#pragma once
#include "Component.h"

// matrix...
#include "SimpleMath.h"

class ManagerSet;
class ICamera;

/// <summary>
/// 카메라 컴포넌트 
/// </summary>
class CameraComponent : public Component
{
public:
	CameraComponent(Entity* _entity);
	virtual ~CameraComponent();

	// 이거 하기 전에 Manager를 받아와야 하는데
	virtual void Update(float _deltaTime) override;
	virtual void Render() override;
	
private:
	float moveSpeed;
	ICamera* camera;
	ManagerSet* managerSet;
	DirectX::SimpleMath::Matrix previousMatrix;
	DirectX::SimpleMath::Matrix currnetMatrix;
};

