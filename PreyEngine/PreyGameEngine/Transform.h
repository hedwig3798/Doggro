#pragma once
#include "Component.h"
#include "SimpleMath.h"

// SimpleMath�� ��Ȱ�ϰ� ����ϱ� ���ؼ� using�� ����ϴ� ���� ���ڴ�.
using namespace DirectX::SimpleMath;

class Entity;

/// <summary>
/// Transform ������.. LYS
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

	// local Matrix�� Update �Ѵ�.
	void UpdateLocalMatrix();

	// final Matrix�� Update �Ѵ�.
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

	// �ϴ� ������ �ʿ��ϰ���
	/// =========================== Hierarchy =========================== ///
	/// ================================================================= ///

	// �θ� Transform�� ���´�.
	Transform* GetParent() const { return parent; }

	// �ڽĵ��� ���´�.
	std::vector<Transform*> GetChildren() const { return children; }

	// �θ� �����Ѵ�.
	void SetParent(Transform* _parent);

	// �ڽ��� �߰� �����Ѵ�.
	void AddChild(Transform* _child);
	void RemoveChild(Transform* _child);

	// �ֻ��� �θ� ������ Ȯ���Ѵ�.
	bool IsRoot() const { return parent == nullptr; }

	// �ڽ��� ��� �ִ��� Ȯ���Ѵ�.
	bool IsLeaf() const { return GetChildren().empty(); }

	// �ڽ��� �ڽĵ��� �ִ��� Ȯ���Ѵ�.
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

	// �ϴ� �θ� �ڽ� �����. �ʿ� ������ ������ �� �𸣰ڴ�.
	Transform* parent;
	std::vector<Transform*> children;
};

