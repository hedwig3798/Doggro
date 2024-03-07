#pragma once
#include <unordered_map>
#include <vector>
#include <string>

class PathManager
{
public:
	PathManager();
	~PathManager();

	// 입력할 필요 없이 filesystem을 이용해서 순회하면서 알아서 넣어준다.
	void Load();

	// 파일 이름을 입력하면 해당 Resource 파일의 경로를 return 해주는 함수
	std::string GetPath(std::string _name);

	// String에서 Wstring으로 변환
	std::wstring StringToWstring(std::string _path);

private:
	// 1. 파일 이름 2. 경로
	std::unordered_map<std::string, std::string> resourceMap;

	// Resource Category
	std::vector<std::string> resourceCategory;
};

