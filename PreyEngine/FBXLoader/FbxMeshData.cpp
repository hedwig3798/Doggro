#include "FbxMeshData.h"

FbxMeshData::FbxMeshData()
	: fbxData(nullptr)
	, indexData{}
	, parent(nullptr)
	, children(std::vector<FbxMeshData*>())
	, vertexBufferData(nullptr)
	, indexBufferData{}
	, pipeline(nullptr)
	, localTM{}
	, globalTM{}
	, name("")
	, matrialList{}
{
}

FbxMeshData::~FbxMeshData()
{
}
