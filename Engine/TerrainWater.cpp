#include "pch.h"
#include "TerrainWater.h"
#include "Timer.h"

TerrainWater::TerrainWater()
{
}

TerrainWater::~TerrainWater()
{
}

void TerrainWater::SetMaterial(const shared_ptr<Material>& material)
{
	_material = material;
}

void TerrainWater::Update()
{
	float time = GET_SINGLE(Timer)->GetElapsedTime();
	_material->SetFloat(0, time);
}
