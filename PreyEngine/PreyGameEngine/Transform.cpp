#include "Transform.h"
#include <queue>

using namespace DirectX::SimpleMath;

Transform::Transform(Entity* _entity)
	: Component(_entity, "Transform")
	,localMatrix{}
	,finalMatrix{}
	,parent(nullptr)
	,children{}
{

}


Transform::~Transform()
{

}

void Transform::Update(float _deltaTime)
{
	UpdateLocalMatrix();
	UpdateFinalMatrix();
}

void Transform::UpdateLocalMatrix()
{
	// �������� �����
	Matrix _rotation = Matrix::CreateFromQuaternion(rotation);
	Matrix _scale = Matrix::CreateScale(scale);
	Matrix _translation = Matrix::CreateTranslation(position);

	// SRT
	localMatrix = _scale * _rotation * _translation;
}

void Transform::UpdateFinalMatrix()
{
	if (IsRoot())
	{
		finalMatrix = localMatrix;
	}
	else
	{
		Matrix _parentMatirx = parent->GetFinalMatrix();
		finalMatrix = localMatrix * _parentMatirx;
	}
}

void Transform::AddXAxisRotation(float _radian)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f) , _radian);
	rotation *= q;
	UpdateLocalMatrix();
}

void Transform::AddPitchRotation(float _radian)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), _radian);
	rotation *= q;
	UpdateLocalMatrix();
}

void Transform::AddYAxisRotation(float _radian)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), _radian);
	rotation *= q;
	UpdateLocalMatrix();
}

void Transform::AddYawRotation(float _radian)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), _radian);
	rotation *= q;
	UpdateLocalMatrix();
}


void Transform::AddZAxisRotation(float _radian)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), _radian);
	rotation *= q;
	UpdateLocalMatrix();
}

void Transform::AddRollRotation(float _radian)
{
	Quaternion q = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), _radian);
	rotation *= q;
	UpdateLocalMatrix();
}

void Transform::SetParent(Transform* _parent)
{

	if (_parent == parent || _parent == this)
	{
		return;
	}

	parent = _parent;

	// �ڱ� �ڽ��� Transform�� �ִ´ٴ� �ǵ�?
	if (parent != nullptr)
	{
		parent->AddChild(this);
	}
}

void Transform::AddChild(Transform* _child)
{
	// �Ű� ���� child�� �ڱ� this��� �Լ��� ������.
	if (_child == this)
	{
		return;
	}

	// children vector�� ��ȸ�ؼ� �Ű����� _child�� ���ٸ� for���� ������.
	for (auto child : children)
	{
		if (_child == child)
		{
			return;
		}
	}
	
	// �Ű����� child�� �θ� �����ͼ� preParent�� �ִ´�.
	Transform* preParent = _child->GetParent();

	// �θ� �ִٸ� �Ű� ���� child�� �θ� �ִ� �ڽ��� �����Ѵ�. 
	if (preParent != nullptr)
	{
		preParent->RemoveChild(_child);
	}

	// children vector�� �Ű������� �߰��Ѵ�.
	children.push_back(_child);

	// �ٵ� ��� ���⼭�� ����ϰ� �����°� �ƴѰ�? �ƴ��� �������ݾ�!
	_child->SetParent(this);
}

void Transform::RemoveChild(Transform* _child)
{
	// �Ű��������� ���� �ڽ��� children vector ���� ã�Ƽ� ���ش�.
	children.erase(std::remove(children.begin(), children.end(), _child));

	// �ڽ��� �θ� ������ �����Ѵ�.
	_child->SetParent(nullptr);
}

bool Transform::IsChildren(Transform* _transform)
{
	std::queue<Transform*> q;

	// �ڽ��� Transform�� queue�� �ִ´�.
	q.push(this);

	// ť�� ��� ���� ������ �ݺ��Ѵ�.
	while (!q.empty())
	{
		Transform* temp = q.front();
		q.pop();

		if (temp == _transform)
		{
			return true;
		}

		// q.front�� �� �ִٸ�
		if (!temp->IsLeaf())
		{
			// ��ȸ�ؼ� ť���ٰ� �ڽĵ��� �ִ´�.
			for (auto child : temp->GetChildren())
			{
				q.push(child);
			}
		}
	}

	return false;
}

Vector3 Transform::QuaternionToVector3(Quaternion _q)
{
	Vector3 _rotation;

	_rotation = _q.ToEuler();

	return _rotation;
}

Quaternion Transform::Vector3ToQuaternion(Vector3 _vector3)
{
	Quaternion q;

	q = q.CreateFromYawPitchRoll(_vector3);

	Vector3 _rotation;
	_rotation = q.ToEuler();

	return q;
}

