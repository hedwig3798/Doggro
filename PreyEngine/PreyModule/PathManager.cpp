#include "PathManager.h"
#include <filesystem>
#include <cassert>

PathManager::PathManager()
	: resourceMap{}, resourceCategory{}
{

}

PathManager::~PathManager()
{

}

void PathManager::Load()
{
	if (!(std::filesystem::exists("Resource")))
	{
		assert(false && "파일이 존재하지 않습니다.");
	}

	// Resource 파일을 순회해서 Category에 넣자.
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path() / "Resource"))
	{
		std::filesystem::path path(entry);
		resourceCategory.push_back(path.filename().string());
	}

	// 2중 for문으로 만들었으며, Resource/category 안에 있는 파일들을 resource Map에 넣는다.
	for (const auto& vector : resourceCategory)
	{
		for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path() / ("Resource\\" + vector)))
		{
			std::filesystem::path path(entry);

			// 실제 사용하려면 category/"파일 경로.파일형식"
			// ex) Sound/"Stage1.wav"
			std::string pathCategoryName = vector + "/";
			std::string linkName = path.filename().string();
			std::string pathName = pathCategoryName + linkName;

			resourceMap.insert(std::make_pair(pathName, entry.path().string()));
		}
	}
}

std::string PathManager::GetPath(std::string _name)
{
	// map을 돌면서 찾는다가
	auto iter = resourceMap.find(_name);

	// 마지막에 도달하면 "", 찾았으면 가져온다.
	if (iter != resourceMap.end())
	{
		return iter->second;
	}
	else return	"";
}

std::wstring PathManager::StringToWstring(std::string _path)
{
	std::wstring wPath;
	wPath.assign(_path.begin(), _path.end());

	return wPath;
}

