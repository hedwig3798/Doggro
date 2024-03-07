#include "RenderType.h"
#include "IGraphicsEngine.h"
#include "Transform.h"

#include "AObject.h"
#include "UObject.h"
#include "Entity.h"
#include "SimpleMath.h"
#include "ManagerSet.h"

RenderType::RenderType(Entity* _entity)
	: Component(_entity, "RenderType"), texturePath{} 
{

}

RenderType::~RenderType()
{

}

/// <summary>
/// �׸��� ���� Type�� �׷��� ������ �Ű������� �ְ� �Ǹ� �˾Ƽ� �׷��ִ� �Լ�.
/// </summary>
/// <param name="_renderType">�׸��� ���� Object</param>
/// <param name="renderer">Graphics Engine</param>
void RenderType::CreateRenderType(RENDER_TYPE _renderType, IGraphicsEngine* _renderer)
{
	// Render Type�� ���� ����ȴ�. mk-1
	switch (_renderType)
	{
	case RENDER_TYPE::TESTBOX:
	{
		aObjectRender = new AObject("gun.fbx", entity->GetManagerset()->GetGraphics(), false, false, true);
	}
	break;
	case RENDER_TYPE::TESTGUN:
	{
		aObjectRender = new AObject("adult_dog3.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
	}
	break;
	case RENDER_TYPE::TESTDOG:
	{
		aObjectRender = new AObject("adult_dog.fbx", entity->GetManagerset()->GetGraphics(), true, true, true);
	}
	break;
	case RENDER_TYPE::TESTBACKGROUND:
	{
		//bObjectRender = _renderer->LoadFbxDatawithBackground("../Model/mapDummy.fbx");
		path[0] = L"../Shader/compiled/BackgroundVS.cso";
		path[1] = L"../Shader/compiled/BackgroundPS.cso";
		texturePath = L"..\\Model\\";
	}
	break;
	case RENDER_TYPE::TESTUI:
	{
		std::wstring texturePath = L"..\\Resource\\Texture\\UI_dummy\\d_guide.png";
		uObjectRender = new UObject();
		std::wstring upath[2]
		{
			L"../Shader/compiled/UIVertexShader.cso",
			L"../Shader/compiled/UIPixelShader.cso",
		};
		uObjectRender->Initalize(entity->GetManagerset()->GetGraphics(), "keySetting", upath, texturePath, 70.f, 300.f, 270.f, 300.f);
	}
	break;

	default:
	{
		path[0] = L" ";
		path[1] = L" ";
		texturePath = L" ";
	}
		break;
	}




}

void RenderType::Update(float _deltatime)
{
	DirectX::SimpleMath::Matrix currentfinalMatrix = GetEntity()->GetComponent<Transform>()->GetFinalMatrix();

	Vector3 position = {};
	Quaternion quaternionRotation = {};
	Vector3 rotation = {};
	Vector3 scale = {};

	// Final Transform�� position, rotation, scale�� ���� �и����ش�.
	currentfinalMatrix.Decompose(scale, quaternionRotation, position);

	// ���ʹϾ����� ���� ȸ�� ���� vector�� �����ش�.
	rotation = ToEulerAngles(quaternionRotation);

	// ��ġ�� �����Ѵ�.



	if (aObjectRender != nullptr)
	{
		aObjectRender->SetPosition(position.x, position.y, position.z);
		aObjectRender->SetRotation(rotation.y, rotation.x, rotation.z);
		//aObjectRender->SetRotation(quaternionRotation);
		aObjectRender->SetScale(scale.x, scale.y, scale.z);	
	}

}

/// <summary>
/// Scene�� ����� or ������ �� access Error 1. �迭 �ʰ��ؼ�, 2. ���� nullptr �̶� 3. �޸� �ջ�
/// </summary>
void RenderType::Render()
{

	if (aObjectRender != nullptr)
	{
		aObjectRender->Render();
	}
	if (uObjectRender != nullptr)
	{
		uObjectRender->Render();
	}
}

void RenderType::DebugRender()
{
	// ���� �������� ���� �� ������?
}

DirectX::SimpleMath::Vector3 RenderType::ToEulerAngles(DirectX::SimpleMath::Quaternion _q)
{
	Vector3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (_q.w * _q.x + _q.y * _q.z);
	double cosr_cosp = 1 - 2 * (_q.x * _q.x + _q.y * _q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = std::sqrt(1 + 2 * (_q.w * _q.y - _q.x * _q.z));
	double cosp = std::sqrt(1 - 2 * (_q.w * _q.y - _q.x * _q.z));
	angles.y = 2 * std::atan2(sinp, cosp) - 3.14159f / 2;

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (_q.w * _q.z + _q.x * _q.y);
	double cosy_cosp = 1 - 2 * (_q.y * _q.y + _q.z * _q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

