#pragma once
#include <string>
#include <unordered_map>
#include <memory>

// 일단 옮기긴 했는데 어떻게 이 엔진에 사용하지..?

// 템플릿으로 만들기.
template <typename T>
class ResourceManager
{
public:
	ResourceManager() {};
	~ResourceManager() {};

	void LoadResource(std::string _path);

	// 링크로 찾는다. return 값이 shared_ptr이다.
	std::shared_ptr<T> GetResource(const std::string& _path);

	// Resource Map 전부 삭제
	void UnLoadResource();


private:
	
	// 템플릿으로 만들기
	// 앞에 string은 파일 링크, 뒤에는 저장되어 있는 Resource
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

