#pragma once
#include "pch.h"

enum class DEFERRED_MAP
{
	DIFFUSE,
	NORMAL,
	METALIC,
	ROUGHNESS,
	END,
};

class FbxMaterialData
{
public:
	UINT index;
	std::string filePath[static_cast<UINT>(DEFERRED_MAP::END)];
	float materialValue[4] = { 0.0f, };
	int materialTypeCount = static_cast<int>(DEFERRED_MAP::END);

	const char* mapType[4] =
	{
		FbxSurfaceMaterial::sDiffuse,
		FbxSurfaceMaterial::sNormalMap,
		FbxSurfaceMaterial::sReflectionFactor,
		FbxSurfaceMaterial::sShininess
	};

public:
	FbxMaterialData();
	FbxMaterialData(UINT _index, FbxSurfaceMaterial* _matData, FbxSurfacePhong* _phongData);
	~FbxMaterialData();

private:
	FbxProperty GetFbxSurfaceMaterialProperty(FbxSurfaceMaterial* _matData, const char* _type)
	{
		return _matData->FindProperty(_type);
	}
};

