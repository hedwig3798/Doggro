#pragma once

/// <summary>
/// �߻�ȭ�� ������Ʈ���� �������̽�
/// 
/// 2023-12-28 KGIT 2C1P LYS
/// </summary>
class IComponent abstract
{
public:
	virtual ~IComponent() {}

	virtual void Update() abstract;

};

