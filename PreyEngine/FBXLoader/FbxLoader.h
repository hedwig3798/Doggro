#pragma once
#include "pch.h"
#include "FbxData.h"

class FbxMeshData;
class FbxBone;

class FbxLoader
{
public:
	FbxLoader();

	FbxManager* fbxManager;
	FbxImporter* fbxImpoter;
	FbxScene* fbxScene;
	FbxGeometryConverter* geometryConverter;

	void Initalize();
	void Release();

	FbxData* Load(std::string _path);

private:
	void LoadMesh(FbxNode* _node, FbxMeshData* _meshData, FbxData* _data);
	void LoadSkeleton(FbxNode* _node, FbxData* _data, int _index, int _pIndex);
	void LoadAnimationTime(FbxData* _data);
	void LoadAnimaiton(FbxNode* _node, FbxData* _data, std::string _name, float _framRate, float _sTime, float _eTime);
	void LoadMaterial(FbxData* _data);

	DirectX::XMMATRIX FbxAMatrixToXMMatrix(const FbxAMatrix& _pSrc);

	DirectX::XMFLOAT3 ReadNormal(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter);
	DirectX::XMFLOAT3 ReadBinormal(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter);
	DirectX::XMFLOAT3 ReadTangent(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter, bool* isValue);
	DirectX::XMFLOAT2 ReadUV(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter);

	template<typename T, typename F>
	F ReadThing(const T* _thigs, int _controlPointIndex, int _vertexCounter);

	FbxBone* FindBoneByName(FbxData* _data, std::string _name, int _now = 0);
};

/// <summary>
/// �Ž� ������ �б� ���ø�
/// �ƿ� �̰ŷθ� ���� �� �ִ� ����� �ִ��� �����
/// </summary>
/// <typeparam name="T">� ����������</typeparam>
/// <typeparam name="F">���ϰ��� � ��������</typeparam>
/// <param name="_thigs">���� ������</param>
/// <param name="_controlPointIndex">�ε����� �д´�</param>
/// <param name="_vertexCounter">���� ������ �д´�</param>
/// <returns></returns>
template<typename T, typename F>
F FbxLoader::ReadThing(const T* _thigs, int _controlPointIndex, int _vertexCounter)
{
	F result = {};

	int counter;
	switch (_thigs->GetMappingMode())
	{
	case FbxGeometryElement::eByControlPoint:
	{
		counter = _controlPointIndex;
		break;
	}
	case FbxGeometryElement::eByPolygonVertex:
	{
		counter = _vertexCounter;
		break;
	}
	default:
		assert(false && "cannot access FbxGeometryElementNormal");
		break;
	}

	switch (_thigs->GetReferenceMode())
	{
	case FbxGeometryElement::eDirect:
	{
		result.x = static_cast<float>(_thigs->GetDirectArray().GetAt(counter).mData[0]);
		result.y = static_cast<float>(_thigs->GetDirectArray().GetAt(counter).mData[1]);
		if constexpr (std::is_same_v<F, DirectX::XMFLOAT3>)
		{
			result.z = static_cast<float>(_thigs->GetDirectArray().GetAt(counter).mData[2]);
		}
		if constexpr (std::is_same_v<F, DirectX::XMFLOAT4>)
		{
			result.z = static_cast<float>(_thigs->GetDirectArray().GetAt(counter).mData[2]);
			result.w = static_cast<float>(_thigs->GetDirectArray().GetAt(counter).mData[3]);
		}
		break;
	}
	case FbxGeometryElement::eIndexToDirect:
	{
		int index = _thigs->GetIndexArray().GetAt(counter); // �ε����� ���´�.
		result.x = static_cast<float>(_thigs->GetDirectArray().GetAt(index).mData[0]);
		result.y = static_cast<float>(_thigs->GetDirectArray().GetAt(index).mData[1]);
		if constexpr (std::is_same_v<F, DirectX::XMFLOAT3>)
		{
			result.z = static_cast<float>(_thigs->GetDirectArray().GetAt(index).mData[2]);
		}
		if constexpr (std::is_same_v<F, DirectX::XMFLOAT4>)
		{
			result.z = static_cast<float>(_thigs->GetDirectArray().GetAt(index).mData[2]);
			result.w = static_cast<float>(_thigs->GetDirectArray().GetAt(index).mData[3]);
		}
		break;
	}
	default:
		break;
	}

	return result;
}