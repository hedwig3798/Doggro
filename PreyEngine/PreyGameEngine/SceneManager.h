#pragma once
#include <string>
#include <unordered_map>

class Scene;
class ManagerSet;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Initalize(ManagerSet* _managerSet);
	void Update(float deltaTime);
	void Render();
	void Finalize();

	// 초반에 Scene을 세팅하기 위해 필요하다.
	void SetCurrentScene(Scene* _val) { currentScene = _val; }

	// 이름으로 씬을 교체한다.
	void ChangeScene(std::string _name);

	// 이름으로 씬을 초기화한다.
	void ResetScene(std::string _name);

	/// === Map과 관련되어 있다. ===
	// 씬을 생성합니다.
	void CreateScene(Scene* _scene);

	// 씬을 가져옵니다.
	Scene* GetScene(std::string _name);

	// map 안에 들어가 있는 씬들을 전부 삭제합니다.
	void UnloadScene();
	/// ==========================

	Scene* GetCurrentScene() const { return currentScene; }

private:
	// 현재 보여지고 있는 scene
	Scene* currentScene;
	
	// 초기에 scene 들을 담은 map, ResetScene에서 사용할 것이다.
	std::unordered_map<std::string, Scene*> sceneMap;
	
	// map이 바뀌고 다시 돌아 갔을 때 바뀐 Scene 들을 저장한다.
	std::unordered_map<std::string, Scene*> changeSceneMap;

	ManagerSet* managerSet;

	bool changeScene = false;
};

