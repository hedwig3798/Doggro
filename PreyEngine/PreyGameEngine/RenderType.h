#pragma once
#include "Component.h"
#include "headers.h"
#include "Define.h"
#include "SimpleMath.h"


class IGraphicsEngine;
class AObject;
class UObject;

/// <summary>
/// Entity들이 어떤 texure를 가질지 모르니 외부에서 적어서 적용하는 클래스
/// 
/// </summary>
class RenderType : public Component
{
public:
	RenderType(Entity* _entity);
	virtual ~RenderType();

	void CreateRenderType(RENDER_TYPE _renderType, IGraphicsEngine* _renderer);
	virtual void Update(float _deltatime) override;
	virtual void Render() override;
	void DebugRender();

	AObject* GetaObjectRender() const { return aObjectRender; }

private:
	DirectX::SimpleMath::Vector3 ToEulerAngles(DirectX::SimpleMath::Quaternion q);

	// Render Type에 따라 바뀐다.
	std::wstring path[2] = {};
	std::wstring texturePath = {};
	AObject* aObjectRender = {};
	UObject* uObjectRender = {};
};

