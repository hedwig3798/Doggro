#pragma once

/// <summary>
/// 추상화된 컴포넌트들의 인터페이스
/// 
/// 2023-12-28 KGIT 2C1P LYS
/// </summary>
class IComponent abstract
{
public:
	virtual ~IComponent() {}

	virtual void Update() abstract;

};

