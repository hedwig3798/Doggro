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
		assert(false && "������ �������� �ʽ��ϴ�.");
	}

	// Resource ������ ��ȸ�ؼ� Category�� ����.
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path() / "Resource"))
	{
		std::filesystem::path path(entry);
		resourceCategory.push_back(path.filename().string());
	}

	// 2�� for������ ���������, Resource/category �ȿ� �ִ� ���ϵ��� resource Map�� �ִ´�.
	for (const auto& vector : resourceCategory)
	{
		for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path() / ("Resource\\" + vector)))
		{
			std::filesystem::path path(entry);

			// ���� ����Ϸ��� category/"���� ���.��������"
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
	// map�� ���鼭 ã�´ٰ�
	auto iter = resourceMap.find(_name);

	// �������� �����ϸ� "", ã������ �����´�.
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

