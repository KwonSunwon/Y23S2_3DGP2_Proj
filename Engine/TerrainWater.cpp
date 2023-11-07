#include "pch.h"
#include "TerrainWater.h"
#include "Timer.h"

TerrainWater::TerrainWater()
{
	_animationMatrix = XMMatrixIdentity();
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

	_animationMatrix._31 += time * 0.0125f;
	_animationMatrix._32 += time * 0.00125f;

	_material->SetMatrix(1, _animationMatrix);
	_material->SetFloat(0, time);
}
