#pragma once
#include "pch.h"
#include "fbxVertex.h"
#include <wrl\client.h>
using Microsoft::WRL::ComPtr;

class FbxData;
struct PipeLine;
struct ID3D11ShaderResourceView;
struct ID3D11Buffer;

class FbxMeshData
{
public:
	FbxMeshData();
	~FbxMeshData();

	FbxData* fbxData;

	FbxMeshData* parent;
	std::vector<FbxMeshData*> children;

	std::string name;

	std::vector<VertexF::Data> vertexData;
	std::vector<std::vector<UINT>> indexData;
	VertexF::Data* vertexBufferData;
	std::vector<UINT*> indexBufferData;

	std::vector<std::vector<std::pair<int, float>>> boneList;

	std::vector<ComPtr<ID3D11ShaderResourceView>> textuers;
	std::vector<ComPtr<ID3D11Buffer>> indexBuffer;

	DirectX::XMMATRIX localTM;
	DirectX::XMMATRIX globalTM;

	PipeLine* pipeline;

	std::vector<std::string> matrialList;
};

