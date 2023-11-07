#pragma once

#include "MonoBehaviour.h"
#include "Material.h"

class TerrainWater : public MonoBehaviour {
public:
	TerrainWater();
	virtual ~TerrainWater();

	void SetMaterial(const shared_ptr<Material>& material);
	virtual void Update() override;

private:
	shared_ptr<Material> _material;
	Matrix _animationMatrix;
};

