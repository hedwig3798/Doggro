#pragma once
#include <string>

#include "Define.h"
#include "SimpleMath.h"
#include "Component.h"

class AObject;

class QuestManager;
class LoadMapData;

class DogScript : public Component
{
public:
	DogScript(Entity* _entity);
	virtual ~DogScript();


	virtual void Update(float _deltaTime) override;
	virtual void Render() override;

	
	bool GetIsCollision() const { return isCollision; }
public:
	virtual void OnCollisionEnter(const Collision& collision) override;
	virtual void OnCollisionExit(const Collision& collision) override;

	void GetQuestManager(QuestManager* _questManager) { questManager = _questManager; }
	void GetObjectManager(LoadMapData* _objectManager) { objectManager = _objectManager; }
	void GetAObject(AObject* _aObject) { myMesh = _aObject; }
	bool GetIsAttach() const { return isAttach; }
	void SetIsAttach(bool val) { isAttach = val; }
	bool GetIsDetach() const { return isDetach; }
	void SetIsDetach(bool val) { isDetach = val; }
	std::vector<float> GetDogPosition() const { return dogPosition; }
	std::string GetAttachName() const { return attachName; }
	void GetDogSight(Entity* _dogSight) { dogSight = _dogSight; }

private:
	QuestManager* questManager;
	LoadMapData* objectManager;

	AObject* myMesh;
	AObject* attachMesh;
	Entity* dogSight;

private:
	bool isHolding;

	bool isCollision;

	bool isAttach;	// Attach
	bool isDetach;	// Detach
	std::vector<float> dogPosition;
	std::string attachName;
};

