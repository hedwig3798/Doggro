#pragma once
#include "headers.h"

// �̰��� interface�� �̾Ƽ� ����ؾ� �ұ�?

class Entity;
class PathManager;
class ManagerSet;

/// <summary>
/// Scene �߻� Ŭ����
/// Enter Scene ���� ���� �ۼ��Ѵ�.
/// </summary>
class Scene abstract 
{ 
public:
	Scene(std::string _name);
	virtual ~Scene() {}
	
	void Intialize(ManagerSet* _managerSet);
	void SceneUpdate(float deltaTime);
	void Render();
	void Finalize();

	// Scene ���� ����, �簳���
	void Resume() { isStop = true; }
	void Pause() { isStop = false; }

	// Scene�� Object �߰� �� ��������
	void AddGameObject(Entity* _entity);
	Entity* GetGameObject(std::string _name);

	// �� �κ��� �� Scene ���� �ٸ� ���̴�.
	// Unity�� �ִ� �κ��� �����ߴ�.
	virtual void Start() abstract;
	virtual void Update(float _deltaTime) abstract;

	// Scene �̸��� ��´�.
	std::string GetSceneName() const { return sceneName; }

	ManagerSet* GetManagerSet() const { return managerSet; }

protected:
	// ��� manager�� ������ �ִ�.
	ManagerSet* managerSet;

private:
	// �Ͻ� ���� ���S
	bool isStop;

	// Scene �̸�
	std::string sceneName;

	// Entity���� ��Ƶ� ���� �ʿ�������?
	std::vector<Entity*> entityVector;
};

