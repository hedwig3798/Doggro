#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class PathManager
{
public:
	PathManager();
	~PathManager();

	// �Է��� �ʿ� ���� filesystem�� �̿��ؼ� ��ȸ�ϸ鼭 �˾Ƽ� �־��ش�.
	void Load();

	// ���� �̸��� �Է��ϸ� �ش� Resource ������ ��θ� return ���ִ� �Լ�
	std::string GetPath(std::string _name);

	// String���� Wstring���� ��ȯ
	std::wstring StringToWstring(std::string _path);

private:
	// 1. ���� �̸� 2. ���
	std::unordered_map<std::string, std::string> resourceMap;

	// Resource Category
	std::vector<std::string> resourceCategory;
};

