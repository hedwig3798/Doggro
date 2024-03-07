#include "LoadMapData.h"
#include "MapLoader.h"

LoadMapData::LoadMapData(IGraphicsEngine* _gp)
{
	gp = _gp;
}

LoadMapData::~LoadMapData()
{

}

void LoadMapData::LoadMapMesh(std::string _stageName)
{
	mapObjects = MapLoader::LoadMapData(_stageName, gp);
}
