#pragma once
#include "Component.h"

// matrix...
#include "SimpleMath.h"

class ManagerSet;
class ICamera;

/// <summary>
/// ī�޶� ������Ʈ 
/// </summary>
class CameraComponent : public Component
{
public:
	CameraComponent(Entity* _entity);
	virtual ~CameraComponent();

	// �̰� �ϱ� ���� Manager�� �޾ƿ;� �ϴµ�
	virtual void Update(float _deltaTime) override;
	virtual void Render() override;
	
private:
	float moveSpeed;
	ICamera* camera;
	ManagerSet* managerSet;
	DirectX::SimpleMath::Matrix previousMatrix;
	DirectX::SimpleMath::Matrix currnetMatrix;
};

