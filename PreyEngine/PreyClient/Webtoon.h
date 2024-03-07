#pragma once
#include "Component.h"

class IGraphicsEngine;
class Entity;
class UObject;

class Webtoon : public Component
{
public:
	Webtoon(Entity* _entity);
	virtual ~Webtoon();

	virtual void Update(float _deltatime) override;
	void CutSceneLoad(int _currentIndex, IGraphicsEngine* _renderer);
	virtual void Render() override;

private:
	unsigned int currentIndex;

	bool isClear;
	float dt;
	UObject* uObjectReneder = {};
	ManagerSet* managerSet;

	std::wstring upath[2]
	{
		L"../Shader/compiled/UIVertexShader.cso",
		L"../Shader/compiled/UIPixelShader.cso",
	};
};

