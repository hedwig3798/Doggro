#pragma once
#include "headers.h"

// 이것을 interface로 뽑아서 사용해야 할까?

class Entity;
class PathManager;
class ManagerSet;

/// <summary>
/// Scene 추상 클래스
/// Enter Scene 시작 전에 작성한다.
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

	// Scene 에서 정지, 재개기능
	void Resume() { isStop = true; }
	void Pause() { isStop = false; }

	// Scene에 Object 추가 및 가져오기
	void AddGameObject(Entity* _entity);
	Entity* GetGameObject(std::string _name);

	// 이 부분은 각 Scene 마다 다를 것이다.
	// Unity에 있는 부분을 참고했다.
	virtual void Start() abstract;
	virtual void Update(float _deltaTime) abstract;

	// Scene 이름을 얻는다.
	std::string GetSceneName() const { return sceneName; }

	ManagerSet* GetManagerSet() const { return managerSet; }

protected:
	// 모든 manager를 가지고 있다.
	ManagerSet* managerSet;

private:
	// 일시 정지 기능S
	bool isStop;

	// Scene 이름
	std::string sceneName;

	// Entity들을 담아둘 것이 필요할지도?
	std::vector<Entity*> entityVector;
};

