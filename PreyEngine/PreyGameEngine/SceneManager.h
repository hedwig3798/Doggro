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

	// �ʹݿ� Scene�� �����ϱ� ���� �ʿ��ϴ�.
	void SetCurrentScene(Scene* _val) { currentScene = _val; }

	// �̸����� ���� ��ü�Ѵ�.
	void ChangeScene(std::string _name);

	// �̸����� ���� �ʱ�ȭ�Ѵ�.
	void ResetScene(std::string _name);

	/// === Map�� ���õǾ� �ִ�. ===
	// ���� �����մϴ�.
	void CreateScene(Scene* _scene);

	// ���� �����ɴϴ�.
	Scene* GetScene(std::string _name);

	// map �ȿ� �� �ִ� ������ ���� �����մϴ�.
	void UnloadScene();
	/// ==========================

	Scene* GetCurrentScene() const { return currentScene; }

private:
	// ���� �������� �ִ� scene
	Scene* currentScene;
	
	// �ʱ⿡ scene ���� ���� map, ResetScene���� ����� ���̴�.
	std::unordered_map<std::string, Scene*> sceneMap;
	
	// map�� �ٲ�� �ٽ� ���� ���� �� �ٲ� Scene ���� �����Ѵ�.
	std::unordered_map<std::string, Scene*> changeSceneMap;

	ManagerSet* managerSet;

	bool changeScene = false;
};

