#include "FbxMaterialData.h"
using namespace fbxsdk;
FbxMaterialData::FbxMaterialData()
	: filePath{}
	, index(0)
{
}

FbxMaterialData::FbxMaterialData(UINT _index, FbxSurfaceMaterial* _matData, FbxSurfacePhong* _phongData)
	: index(_index)
{
	FbxProperty	prop = _phongData->FindProperty(FbxSurfacePhong::sSpecular);
	
	auto s = _phongData->Specular;
	auto t = s.Get();
	int layerMatCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
	if (layerMatCount > 0)
	{
		for (int j = 0; j < layerMatCount; j++)
		{
			FbxLayeredTexture* layered_texture = prop.GetSrcObject<FbxLayeredTexture>(j);
			int lcount = layered_texture->GetSrcObjectCount<FbxFileTexture>();
			for (int k = 0; k < lcount; k++)
			{
				FbxFileTexture* texture = FbxCast<FbxFileTexture>(layered_texture->GetSrcObject<FbxFileTexture>(k));
				std::string texture_name = texture->GetRelativeFileName();
			}
		}
	}
	else
	{
		int texCount = prop.GetSrcObjectCount<FbxFileTexture>();
		for (int j = 0; j < texCount; j++)
		{
			const FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxFileTexture>(j));
			// Then, you can get all the properties of the texture, include its name
			std::string texture_name = texture->GetRelativeFileName();
		}
	}
	for (int i = 0; i < static_cast<int>(DEFERRED_MAP::END); i++)
	{
		FbxProperty	prop = _matData->FindProperty(this->mapType[i]);
		int layerMatCount = prop.GetSrcObjectCount<FbxLayeredTexture>();
		if (layerMatCount > 0)
		{
			for (int j = 0; j < layerMatCount; j++)
			{
				FbxLayeredTexture* layered_texture = prop.GetSrcObject<FbxLayeredTexture>(j);
				int lcount = layered_texture->GetSrcObjectCount<FbxFileTexture>();
				for (int k = 0; k < lcount; k++)
				{
					FbxFileTexture* texture = FbxCast<FbxFileTexture>(layered_texture->GetSrcObject<FbxFileTexture>(k));
					std::string texture_name = texture->GetRelativeFileName();
					this->filePath[i] = texture_name;
				}
			}
		}
		else
		{
			int texCount = prop.GetSrcObjectCount<FbxFileTexture>();
			for (int j = 0; j < texCount; j++)
			{
				const FbxFileTexture* texture = FbxCast<FbxFileTexture>(prop.GetSrcObject<FbxFileTexture>(j));
				// Then, you can get all the properties of the texture, include its name
				std::string texture_name = texture->GetRelativeFileName();
				this->filePath[i] = texture_name;
			}
		}
	}
}

FbxMaterialData::~FbxMaterialData()
{

}
