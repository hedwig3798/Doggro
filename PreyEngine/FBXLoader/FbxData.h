#pragma once
#include <string>
#include <vector>
#include <map>

class GraphicsEngine;
class FbxLoader;
class FbxMaterialData;
struct PipeLine;
class FbxBone;
class FbxMeshData;
class FbxAnimationData;

class FbxData
{
public:
	std::string name;

	FbxMeshData* mesh;
	
	std::vector<FbxBone*> boneVector;

	std::map<std::string, FbxMaterialData*> materialMap;

	FbxData();
};

