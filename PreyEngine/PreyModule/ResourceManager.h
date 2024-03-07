#pragma once
#include <string>
#include <unordered_map>
#include <memory>

// �ϴ� �ű�� �ߴµ� ��� �� ������ �������..?

// ���ø����� �����.
template <typename T>
class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	void LoadResource(std::string _path);

	// ��ũ�� ã�´�. return ���� shared_ptr�̴�.
	std::shared_ptr<T> GetResource(const std::string& _path);

	// Resource Map ���� ����
	void UnLoadResource();


private:
	
	// ���ø����� �����
	// �տ� string�� ���� ��ũ, �ڿ��� ����Ǿ� �ִ� Resource
	std::unordered_map<std::string, std::shared_ptr<T>> resourceMap;

};

template<typename T>
void ResourceManager<T>::UnLoadResource()
{
	resourceMap.clear();
}

template<typename T>
std::shared_ptr<T> ResourceManager<T>::GetResource(const std::string& _path)
{
	auto iter = resourceMap.find(_path);

	if (iter != resourceMap.end())
	{
		return iter->second;
	}
	else return nullptr;
}

template<typename T>
void ResourceManager<T>::LoadResource(std::string _path)
{
	T* _newResource = new T();

	resourceMap.insert(std::make_pair(_path, _newResource));
}

