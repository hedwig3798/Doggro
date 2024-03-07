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
	// 지역변수 물어보기
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

	// 자기 자신의 Transform을 넣는다는 건데?
	if (parent != nullptr)
	{
		parent->AddChild(this);
	}
}

void Transform::AddChild(Transform* _child)
{
	// 매개 변수 child가 자기 this라면 함수를 나간다.
	if (_child == this)
	{
		return;
	}

	// children vector를 순회해서 매개변수 _child와 같다면 for문을 끝낸다.
	for (auto child : children)
	{
		if (_child == child)
		{
			return;
		}
	}
	
	// 매개변수 child의 부모를 가져와서 preParent를 넣는다.
	Transform* preParent = _child->GetParent();

	// 부모가 있다면 매개 변수 child의 부모에 있는 자식을 삭제한다. 
	if (preParent != nullptr)
	{
		preParent->RemoveChild(_child);
	}

	// children vector에 매개변수를 추가한다.
	children.push_back(_child);

	// 근데 얘는 여기서만 사용하고 버리는거 아닌가? 아니지 포인터잖아!
	_child->SetParent(this);
}

void Transform::RemoveChild(Transform* _child)
{
	// 매개변수에서 받은 자식을 children vector 에서 찾아서 없앤다.
	children.erase(std::remove(children.begin(), children.end(), _child));

	// 자식쪽 부모도 연결을 해제한다.
	_child->SetParent(nullptr);
}

bool Transform::IsChildren(Transform* _transform)
{
	std::queue<Transform*> q;

	// 자신의 Transform을 queue에 넣는다.
	q.push(this);

	// 큐가 비어 있을 때까지 반복한다.
	while (!q.empty())
	{
		Transform* temp = q.front();
		q.pop();

		if (temp == _transform)
		{
			return true;
		}

		// q.front가 차 있다면
		if (!temp->IsLeaf())
		{
			// 순회해서 큐에다가 자식들을 넣는다.
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

