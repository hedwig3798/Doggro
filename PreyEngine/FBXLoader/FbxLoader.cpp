#include "FbxLoader.h"
#include "FbxMaterialData.h"
#include "FbxMeshData.h"
#include "../DXTK/Inc/SimpleMath.h"
#include "FbxBone.h"
#include "FbxAnimationData.h"

FbxLoader::FbxLoader()
	: fbxManager(nullptr)
	, fbxImpoter(nullptr)
	, fbxScene(nullptr)
	, geometryConverter(nullptr)
{

}

/// <summary>
/// �δ��� �ʱ�ȭ
/// </summary>
void FbxLoader::Initalize()
{
	// Fbx �ε带 ���� Ŭ���� ����
	this->fbxManager = FbxManager::Create();
	assert(this->fbxManager && "cannot create fbx manager\n");

	this->fbxImpoter = FbxImporter::Create(fbxManager, "");
	assert(this->fbxManager && "cannot create fbx manager\n");

	this->fbxScene = FbxScene::Create(fbxManager, "");
	assert(this->fbxScene && "cannot create fbx manager\n");

	// �Ž��� �ﰢ������ �߶��� Ŭ���� ����
	this->geometryConverter = new FbxGeometryConverter(this->fbxManager);
}

/// <summary>
/// �δ��� ����
/// </summary>
void FbxLoader::Release()
{
	// �̸� ������ Ŭ���� ����
	this->fbxManager->Destroy();
	this->fbxImpoter->Destroy();
	this->fbxScene->Destroy();
	delete this->geometryConverter;
}

/// <summary>
/// �ε� �Լ�
/// </summary>
/// <param name="_path"></param>
/// <returns></returns>
FbxData* FbxLoader::Load(std::string _path)
{
	// ��θ� ���� ������ Ŭ���� �ʱ�ȭ
	bool ret = this->fbxImpoter->Initialize(_path.c_str());
	assert(ret && "cannot initalize fbx importer when load\n");

	// �����͸� ���� �� ����Ʈ
	ret = this->fbxImpoter->Import(this->fbxScene);
	assert(ret && "cannot import fbx scene when load\n");

	// ������ ��Ʈ ��� ������
	FbxNode* node = this->fbxScene->GetRootNode();
	assert(node && "cannot load Node from scene\n");

	// �ش� ���� ��带 �ﰢ������ �ɰ���
	this->geometryConverter->Triangulate(this->fbxScene, true);

	// ������ ������ Ŭ����
	FbxData* data = new FbxData();

	LoadMaterial(data);

	FbxBone* bone = new FbxBone();
	LoadSkeleton(node, data, 0, -1);
	FbxMeshData* meshData = new FbxMeshData();

	// ������ Ŭ������ ������ �ε�
	LoadMesh(node, meshData, data);
	data->mesh = meshData;
	LoadAnimationTime(data);

	return data;
}

/// <summary>
/// �Ž� �ε�
/// </summary>
/// <param name="_node">Fbx ���</param>
/// <param name="_data">�Ž� ������</param>
void FbxLoader::LoadMesh(FbxNode* _node, FbxMeshData* _meshData, FbxData* _data)
{
	// ����� �Ӽ�
	FbxNodeAttribute* nodeAttribute = _node->GetNodeAttribute();
	// ����� ���� ��ȯ ���
	FbxAMatrix& globalTransform = _node->EvaluateGlobalTransform();
	_meshData->globalTM = FbxAMatrixToXMMatrix(globalTransform);

	// ����� ���� ��ȯ ���
	FbxAMatrix& localTransform = _node->EvaluateLocalTransform();
	_meshData->localTM = FbxAMatrixToXMMatrix(localTransform);

	// ���� ��ġ ������ ���� ����
	std::vector<DirectX::XMFLOAT3> position;
	// ����ȭ�� ���� ��
	std::unordered_map<VertexF::Data, UINT, VertexF::Data> indexMapping;

	int matCount = _node->GetSrcObjectCount<FbxSurfaceMaterial>();

	for (int i = 0; i < matCount; i++)
	{
		FbxSurfaceMaterial* mat = _node->GetSrcObject<FbxSurfaceMaterial>(i);
		if (mat)
		{
			auto matName = mat->GetName();
			_meshData->matrialList.push_back(matName);
		}
	}

	_meshData->name = _node->GetName();

	// ��� �Ӽ��� �ִٸ�
	if (nodeAttribute != nullptr)
	{
		// �� ����� �Ӽ��� �޽�.
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			// FbxMesh�� ĳ���õ� ��� �Ӽ��� �����͸� �����´�.
			FbxMesh* mesh = _node->GetMesh();
			int layerCount = mesh->GetLayerCount();
			bool isSame = true;
			std::vector<int> matrialIds;

			// ��ġ ������ �ִ� ���� ������ ������ �´�.
			int vertexCount = mesh->GetControlPointsCount();
			position.resize(vertexCount);

			// �������� ��ġ ������ �Է�
			for (int i = 0; i < vertexCount; i++)
			{
				position[i].x = (static_cast<float>(mesh->GetControlPointAt(i).mData[0]));
				position[i].y = (static_cast<float>(mesh->GetControlPointAt(i).mData[1]));
				position[i].z = (static_cast<float>(mesh->GetControlPointAt(i).mData[2]));
			}

			bool val = true;
			bool* isValue = &val;
			*isValue = true;
			// �ش� �Ž��� ��� �ﰢ���� ������ �ִ���
			int triangleCount = mesh->GetPolygonCount();
			// _data->indexData.resize(static_cast<size_t>(indexCount * 3));
			int vCount = 0;
			// �ﰢ���� ���� ��ŭ vertex ����
			for (int i = 0; i < triangleCount; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					int controlPointIndex = mesh->GetPolygonVertex(i, j);

					int matCount = mesh->GetElementMaterialCount();


					DirectX::XMFLOAT3& pos = position[controlPointIndex];
					DirectX::XMFLOAT3 normal = ReadNormal(mesh, controlPointIndex, vCount);
					DirectX::XMFLOAT3 tangent = ReadTangent(mesh, controlPointIndex, vCount, isValue);
					DirectX::XMFLOAT3 bitangent = ReadBinormal(mesh, controlPointIndex, vCount);
					DirectX::XMFLOAT2 UV = ReadUV(mesh, controlPointIndex, vCount);

					FbxLayerElementMaterial* layerMaterial = mesh->GetLayer(0)->GetMaterials();
					int matrialId = layerMaterial->GetIndexArray().GetAt(i);

					VertexF::Data inputData = VertexF::Data(pos, normal, UV, bitangent, tangent, matrialId);

					UINT temp = static_cast<UINT>(_meshData->vertexData.size());
					if (_meshData->indexData.size() < matrialId + 1)
					{
						_meshData->indexData.resize(matrialId + 1);
					}

					_meshData->indexData[matrialId].push_back(vCount);
					_meshData->vertexData.push_back(inputData);

					vCount++;
				}
			}

			if (!(*isValue))
			{
				using DirectX::SimpleMath::Vector3;
				using DirectX::SimpleMath::Vector2;

				Vector3* Tangent = new Vector3[vCount * 2];
				Vector3* Bitangent = Tangent + vCount;

				for (int i = 0; i < vCount; ++i)
				{
					Tangent[i] = DirectX::SimpleMath::Vector3::Zero;
					Bitangent[i] = DirectX::SimpleMath::Vector3::Zero;
				}

				for (int i = 0; i < triangleCount; i++)
				{
					const Vector3& p0 = _meshData->vertexData[i * 3].position;
					const Vector3& p1 = _meshData->vertexData[i * 3 + 1].position;
					const Vector3& p2 = _meshData->vertexData[i * 3 + 2].position;

					const Vector2& w0 = _meshData->vertexData[i * 3].UV;
					const Vector2& w1 = _meshData->vertexData[i * 3 + 1].UV;
					const Vector2& w2 = _meshData->vertexData[i * 3 + 2].UV;

					Vector3 e1 = p1 - p0;
					Vector3 e2 = p2 - p0;
					float x1 = w1.x - w0.x;
					float x2 = w2.x - w0.x;
					float y1 = w1.y - w0.y;
					float y2 = w2.y - w0.y;

					float r = 1.0f / (x1 * y2 - x2 * y1);
					Vector3 t = (e1 * y2 - e2 * y1) * r;
					Vector3 b = (e2 * x1 - e1 * x2) * r;

					Tangent[i * 3] += t;
					Tangent[i * 3 + 1] += t;
					Tangent[i * 3 + 2] += t;

					Bitangent[i * 3] += b;
					Bitangent[i * 3 + 1] += b;
					Bitangent[i * 3 + 2] += b;
				}

				// ������ Tangent�� Orthonormalize �ϰ�, Handedness �ϰ� ��갡���ϵ��� w �� ��ȣ �߰�
				for (int i = 0; i < vCount; ++i)
				{
					const Vector3& t = Tangent[i];
					const Vector3& b = Bitangent[i];
					const Vector3& n = _meshData->vertexData[i].normal;


					// DirectX::XMStoreFloat3(&_data->vertexData[i].tangent, DirectX::XMVector3Normalize(t - DirectX::XMVector3Dot(t, n).m128_f32[0] * n)); // Normalize(t - Dot(t, n)*n)
					DirectX::XMStoreFloat3(&_meshData->vertexData[i].tangent, DirectX::XMVector3Normalize(t));
					DirectX::XMStoreFloat3(&_meshData->vertexData[i].binormal, DirectX::XMVector3Normalize(b));
					// OutTangentArray[i].w = (Dot(Cross(t, b), n) > 0.0f) ? 1.0f : -1.0f;
				}
				delete[] Tangent;
			}
		}
	}



	// ����� �ڽĵ� ���� �ε�
	for (int i = 0; i < _node->GetChildCount(); ++i)
	{
		FbxMeshData* child = new FbxMeshData();
		_meshData->children.push_back(child);
		child->parent = _meshData;
		LoadMesh(_node->GetChild(i), child, _data);
	}
}

void FbxLoader::LoadSkeleton(FbxNode* _node, FbxData* _data, int _index, int _pIndex)
{
	FbxBone* child = nullptr;
	if (_node->GetNodeAttribute() &&
		_node->GetNodeAttribute()->GetAttributeType() &&
		_node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		child = new FbxBone();
		child->index = _index;
		if (_index == 0)
		{
			child->parentIndex = -1;
		}
		else
		{
			child->parentIndex = _pIndex;
			_data->boneVector[_pIndex]->childIndex.push_back(_index);
		}
		child->name = _node->GetName();
		FbxSkeleton* skel = _node->GetSkeleton();
		// 		child->initailLocalTM = child->localTM = FbxAMatrixToXMMatrix(_node->EvaluateLocalTransform());
		// 		child->initailGlobalTM = child->globalTM = FbxAMatrixToXMMatrix(_node->EvaluateGlobalTransform());

		_data->boneVector.push_back(child);
	}
	for (int i = 0; i < _node->GetChildCount(); ++i)
	{
		LoadSkeleton(_node->GetChild(i), _data, static_cast<int>(_data->boneVector.size()), _index);
	}
}

void FbxLoader::LoadAnimationTime(FbxData* _data)
{
	FbxNode* rootNode = this->fbxScene->GetRootNode();
	float framerate = static_cast<float>(FbxTime::GetFrameRate(this->fbxScene->GetGlobalSettings().GetTimeMode()));


	FbxArray<FbxString*> animationArray;
	FbxDocument* document = dynamic_cast<FbxDocument*>(this->fbxScene);

	if (document != nullptr)
	{
		document->FillAnimStackNameArray(animationArray);
	}

	for (int i = 0; i < this->fbxImpoter->GetAnimStackCount(); i++)
	{
		FbxTakeInfo* animationInfo = this->fbxImpoter->GetTakeInfo(i);
		std::string animationName = animationInfo->mName.Buffer();

		FbxTimeSpan span = animationInfo->mLocalTimeSpan;

		double sTime = span.GetStart().GetSecondDouble();
		double eTime = span.GetStop().GetSecondDouble();

		if (sTime < eTime)
		{
			int keyFrame = static_cast<int>((eTime - sTime) * static_cast<double>(framerate));

			LoadAnimaiton(rootNode, _data, animationName, framerate, static_cast<float>(sTime), static_cast<float>(eTime));
		}
	}
}

void FbxLoader::LoadAnimaiton(FbxNode* _node, FbxData* _data, std::string _name, float _framRate, float _sTime, float _eTime)
{
	FbxNodeAttribute* nodeAttribute = _node->GetNodeAttribute();
	if (nodeAttribute != nullptr)
	{
		if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			if (!_data->boneVector.empty())
			{
				std::string boneName = _node->GetName();
				FbxBone* bone = FindBoneByName(_data, boneName);
				FbxAnimationData* aniData = new FbxAnimationData();

				if (bone != nullptr)
				{
					double time = 0;
					while (time <= static_cast<double>(_eTime))
					{
						FbxTime aniTime;
						aniTime.SetSecondDouble(time);

						auto localTM = _node->EvaluateLocalTransform(aniTime);
						auto globalTM = _node->EvaluateGlobalTransform(aniTime);

						aniData->keyFrameCount = static_cast<int>((_eTime - _sTime) * static_cast<double>(_framRate));
						aniData->framerate = _framRate;
						aniData->defaultFramerate = _framRate;

						aniData->animationData.push_back({ time, FbxAMatrixToXMMatrix(localTM) });

						time += 1.0f / _framRate;
					}
					bone->frameList[_name] = aniData;
				}
			}
		}
	}

	for (int i = 0; i < _node->GetChildCount(); i++)
	{
		LoadAnimaiton(_node->GetChild(i), _data, _name, _framRate, _sTime, _eTime);
	}

	return;
}

/// <summary>
/// ���׸��� �ε�
/// </summary>
/// <param name="_data">����� ������</param>
void FbxLoader::LoadMaterial(FbxData* _data)
{
	for (int i = 0; i < this->fbxScene->GetMaterialCount(); i++)
	{
		FbxSurfaceMaterial* rawMat = this->fbxScene->GetMaterial(i);
		FbxSurfacePhong* phongMat = this->fbxScene->GetSrcObject<FbxSurfacePhong>(i);
		FbxMaterialData* matData = new FbxMaterialData(i, rawMat, phongMat);
		auto name = rawMat->GetName();
		_data->materialMap[name] = matData;
	}
}

/// <summary>
/// FBX ��Ʈ������ D3D ��Ʈ������ ����
/// </summary>
/// <param name="_fbxMatrix"></param>
/// <returns></returns>
DirectX::XMMATRIX FbxLoader::FbxAMatrixToXMMatrix(const FbxAMatrix& _fbxMatrix)
{
	// fbx�� ��� �����͸� Diretx�� �µ��� ����
	return DirectX::XMMatrixSet(
		static_cast<FLOAT>(_fbxMatrix.Get(0, 0)), static_cast<FLOAT>(_fbxMatrix.Get(0, 1)), static_cast<FLOAT>(_fbxMatrix.Get(0, 2)), static_cast<FLOAT>(_fbxMatrix.Get(0, 3)),
		static_cast<FLOAT>(_fbxMatrix.Get(1, 0)), static_cast<FLOAT>(_fbxMatrix.Get(1, 1)), static_cast<FLOAT>(_fbxMatrix.Get(1, 2)), static_cast<FLOAT>(_fbxMatrix.Get(1, 3)),
		static_cast<FLOAT>(_fbxMatrix.Get(2, 0)), static_cast<FLOAT>(_fbxMatrix.Get(2, 1)), static_cast<FLOAT>(_fbxMatrix.Get(2, 2)), static_cast<FLOAT>(_fbxMatrix.Get(2, 3)),
		static_cast<FLOAT>(_fbxMatrix.Get(3, 0)), static_cast<FLOAT>(_fbxMatrix.Get(3, 1)), static_cast<FLOAT>(_fbxMatrix.Get(3, 2)), static_cast<FLOAT>(_fbxMatrix.Get(3, 3)));
}

/// <summary>
/// �Ž��� �븻�� �б�
/// </summary>
/// <param name="_mesh">�Ž� ������</param>
/// <param name="_controlPointIndex">�ε��� ������ �Ž� ã��</param>
/// <param name="_vertexCounter">���� ī���ͷ� �Ž� ã��</param>
/// <returns>�븻 ��</returns>
DirectX::XMFLOAT3 FbxLoader::ReadNormal(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter)
{
	DirectX::XMFLOAT3 result = {};

	if (!(_mesh->GetElementNormalCount() < 1))
	{
		const FbxGeometryElementNormal* vBinormal = _mesh->GetElementNormal(0);
		result = ReadThing<FbxGeometryElementNormal, DirectX::XMFLOAT3>(vBinormal, _controlPointIndex, _vertexCounter);
	}
	else
	{
		result = { 0.0f, 0.0f, 0.0f };
	}
	return result;
}

/// <summary>
/// ���̳븻 �б�
/// </summary>
DirectX::XMFLOAT3 FbxLoader::ReadBinormal(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter)
{
	DirectX::XMFLOAT3 result = {};

	if (!(_mesh->GetElementBinormalCount() < 1))
	{
		const FbxGeometryElementBinormal* vBinormal = _mesh->GetElementBinormal(0);
		result = ReadThing<FbxGeometryElementBinormal, DirectX::XMFLOAT3>(vBinormal, _controlPointIndex, _vertexCounter);
	}
	else
	{
		result = { 0.0f, 0.0f, 0.0f };
	}
	return result;
}

/// <summary>
/// ź��Ʈ �б�
/// </summary>
DirectX::XMFLOAT3 FbxLoader::ReadTangent(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter, bool* isValue)
{
	DirectX::XMFLOAT3 result = {};

	if (!(_mesh->GetElementTangentCount() < 1))
	{
		const FbxGeometryElementTangent* vBinormal = _mesh->GetElementTangent(0);
		result = ReadThing<FbxGeometryElementTangent, DirectX::XMFLOAT3>(vBinormal, _controlPointIndex, _vertexCounter);
	}
	else
	{
		*isValue = false;
		result = { 0.0f, 0.0f, 0.0f };
	}
	return result;
}

/// <summary>
/// UV ������ �б�
/// </summary>
DirectX::XMFLOAT2 FbxLoader::ReadUV(const FbxMesh* _mesh, int _controlPointIndex, int _vertexCounter)
{
	DirectX::XMFLOAT2 result = {};

	const FbxGeometryElementUV* vBinormal = _mesh->GetElementUV(0);
	result = ReadThing<FbxGeometryElementUV, DirectX::XMFLOAT2>(vBinormal, _controlPointIndex, _vertexCounter);

	result.y = 1.0f - result.y;
	return result;
}

FbxBone* FbxLoader::FindBoneByName(FbxData* _data, std::string _name, int _now)
{
	if (_data->boneVector[_now]->name == _name)
	{
		return _data->boneVector[_now];
	}

	for (auto index : _data->boneVector[_now]->childIndex)
	{
		auto* result = FindBoneByName(_data, _name, index);
		if (result != nullptr)
		{
			return result;
		}
	}

	return nullptr;
}
