#include "Debug.h"
#include "Entity.h"
#include "Transform.h"
#include "ManagerSet.h"
#include "IGraphicsEngine.h"
#include "CollsionManager.h"
#include "CameraManager.h"
#include <string>

Debug::Debug(Entity* _entity)
	: Component(_entity, "Debug"), managerSet{}
{
	managerSet = _entity->GetManagerset();
}

Debug::~Debug()
{

}

void Debug::Update(float _deltaTime)
{
	// 여기서 Debug 정보를 읽어 들인다.
	// Debug 정보에는 어떤 것이 필요할까?
	
	// 1. Object Name
	// 2. Transform 위치만 가지고 오자.
	// 3. 시간과 프레임도 가져오자
	Matrix finalMatrix = entity->GetComponent<Transform>()->GetFinalMatrix();

	//

	int i = static_cast<int>(finalMatrix._41);
	int j = static_cast<int>(finalMatrix._42);

	float rgba[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	
	// 시간 
	std::wstring wTime = L"DeltaTime : ";
	wTime += std::to_wstring(_deltaTime);
	managerSet->GetGraphics()->WriteText(i, j, rgba, const_cast<TCHAR*>(wTime.c_str()));
	j++;
	
	// 프레임
	std::wstring wFPS = L"FPS : ";
	wFPS += std::to_wstring(1.0f / _deltaTime);
	managerSet->GetGraphics()->WriteText(i, j, rgba, const_cast<TCHAR*>(wTime.c_str()));
	j++;
	
	// 1. string -> wstring 으로 변환해야 한다. -> assign
	// 2. float -> wstring 으로 변환해주는 건 to_wstring

	// Object 이름
	std::string name = entity->GetName();
	std::wstring wname = L"";
	wname.assign(name.begin(), name.end());
	managerSet->GetGraphics()->WriteText(i, j, rgba, const_cast<TCHAR*>(wname.c_str()));
	j++;

	// Object 위치
	Vector3 position = entity->GetComponent<Transform>()->GetPosition();
	std::wstring wposition = L"Position : ";
	wposition += std::to_wstring(position.x);
	wposition += L" ";
	wposition += std::to_wstring(position.y);
	wposition += L" ";
	wposition += std::to_wstring(position.z);
	managerSet->GetGraphics()->WriteText(i, j, rgba, const_cast<TCHAR*>(wposition.c_str()));
	j++;

	// Object 회전인데
	Quaternion rotation = entity->GetComponent<Transform>()->GetRotation();
	std::wstring wrotation = L"Rotation : ";
	wrotation += std::to_wstring(rotation.x);
	wrotation += L" ";
	wrotation += std::to_wstring(rotation.y);
	wrotation += L" ";
	wrotation += std::to_wstring(rotation.z);
	wrotation += L" ";
	wrotation += std::to_wstring(rotation.w);
	managerSet->GetGraphics()->WriteText(i, j, rgba, const_cast<TCHAR*>(wrotation.c_str()));
	j++;

	this->managerSet->GetCollisionManager()->PickedObject(this->managerSet->GetCameraManager()->GetCamera());

}

void Debug::Render()
{
	managerSet->GetGraphics()->DrawDefaultAxes();
	managerSet->GetGraphics()->DrawDefaultLine();
}
