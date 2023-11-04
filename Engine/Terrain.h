#pragma once
#include "Component.h"

class Terrain : public Component
{
public:
	Terrain();
	virtual ~Terrain();

	void Init(int32 sizeX, int32 sizeZ, float scale, float heightScale);

	float GetHeight(float x, float z);

	virtual void FinalUpdate() override;

private:
	int32 _sizeX = 64;
	int32 _sizeZ = 64;
	float _maxTesselation = 4.f;

	float _scale = 1.f;
	float _heightScale = 1.f;

	shared_ptr<class Material> _material;

	std::vector<float> _pixels;
};


