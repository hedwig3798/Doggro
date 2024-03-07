#pragma once
#include "Component.h"
#include "SimpleMath.h"

// SimpleMath를 원활하게 사용하기 위해서 using을 사용하는 것이 좋겠다.
using namespace DirectX::SimpleMath;

class Entity;

/// <summary>
/// Transform 제작중.. LYS
/// </summary>
class Transform : public Component
{
public:
	//Transform();
	Transform(Entity* _entity);
	virtual ~Transform();

	void Update(float _deltaTime) override;

	/// ====================== Matrix Update ====================== ///
	/// =========================================================== ///

	// local Matrix를 Update 한다.
	void UpdateLocalMatrix();

	// final Matrix를 Update 한다.
	void UpdateFinalMatrix();

	/// ===================== Add Position Rotation Scale ===================== ///
	/// ======================================================================= ///

	// Add Position
	void AddPosition(const Vector3& _addposition) { position += _addposition; /*UpdateLocalMatrix(); UpdateFinalMatrix();*/ };

	// Add Rotation 
	void AddXAxisRotation(float _radian);
	void AddPitchRotation(float _radian);

	void AddYAxisRotation(float _radian);
	void AddYawRotation(float _radian);

	void AddZAxisRotation(float _radian);
	void AddRollRotation(float _radian);

	// Add Scale
	void AddScale(const Vector3& _addScale) { scale += _addScale; };

	// 일단 만들어봐 필요하겠지
	/// =========================== Hierarchy =========================== ///
	/// ================================================================= ///

	// 부모 Transform을 얻어온다.
	Transform* GetParent() const { return parent; }

	// 자식들을 얻어온다.
	std::vector<Transform*> GetChildren() const { return children; }

	// 부모를 설정한다.
	void SetParent(Transform* _parent);

	// 자식을 추가 제거한다.
	void AddChild(Transform* _child);
	void RemoveChild(Transform* _child);

	// 최상위 부모가 없는지 확인한다.
	bool IsRoot() const { return parent == nullptr; }

	// 자식이 비어 있는지 확인한다.
	bool IsLeaf() const { return GetChildren().empty(); }

	// 자신의 자식들이 있는지 확인한다.
	bool IsChildren(Transform* _transform);

	/// ========================= Getter Setter ========================== ///
	/// ================================================================== ///

	// Positon Getter Setter
	Vector3 GetPosition() const { return position; }
	void SetPosition(Vector3 _val) { position = _val; /*UpdateLocalMatrix();*/ }

	// Rotation Getter Setter
	Quaternion GetRotation() const { return rotation; }
	void SetRotation(Quaternion _val) { rotation = _val; }

	// Scale Getter Setter
	Vector3 GetScale() const { return scale; }
	void SetScale(Vector3 _val) { scale = _val; }

	// local Matrix Getter
	Matrix GetLocalMatrix() const { return localMatrix; }
	void SetLocalMatrix(DirectX::SimpleMath::Matrix val) { localMatrix = val; }

	// final Matrix Getter
	Matrix GetFinalMatrix() const { return finalMatrix; }
	void SetFinalMatrix(DirectX::SimpleMath::Matrix val) { finalMatrix = val; }

	Vector3 QuaternionToVector3(Quaternion _q);
	Quaternion Vector3ToQuaternion(Vector3 _vector3);

private:
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	Quaternion rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	Vector3 scale = { 1.0f, 1.0f, 1.0f };

	Matrix localMatrix;
	Matrix finalMatrix;

	// 일단 부모 자식 적어보자. 필요 이유는 아직은 잘 모르겠다.
	Transform* parent;
	std::vector<Transform*> children;
};

