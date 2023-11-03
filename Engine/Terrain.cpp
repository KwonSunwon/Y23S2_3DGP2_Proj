#include "pch.h"
#include "Terrain.h"
#include "Resources.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Texture.h"


Terrain::Terrain() : Component(COMPONENT_TYPE::TERRAIN)
{

}

Terrain::~Terrain()
{
}

void Terrain::Init(int32 sizeX, int32 sizeZ)
{
	_sizeX = 2048;
	_sizeZ = 2048;

	_material = GET_SINGLE(Resources)->Get<Material>(L"Terrain");

	_material->SetInt(1, _sizeX);
	_material->SetInt(2, _sizeZ);
	_material->SetFloat(0, _maxTesselation);

	shared_ptr<Texture> heightMap = GET_SINGLE(Resources)->Load<Texture>(L"HeightMap", L"..\\Resources\\Texture\\Terrain\\height.png");
	Vec2 v = Vec2(heightMap->GetWidth(), heightMap->GetHeight());
	_material->SetVec2(0, Vec2(heightMap->GetWidth(), heightMap->GetHeight()));
	_material->SetVec2(1, Vec2(1000.f, 5000.f));
	_material->SetTexture(2, heightMap);

	shared_ptr<MeshRenderer> meshRenderer = GetGameObject()->GetMeshRenderer();
	{
		shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadTerrainMesh(_sizeX, _sizeZ);
		meshRenderer->SetMesh(mesh);
	}
	{
		shared_ptr<Material> material = GET_SINGLE(Resources)->Get<Material>(L"Terrain");
		meshRenderer->SetMaterial(material);
	}

	// for player collision terrain hieht
	uint8_t* pixels;
	size_t size = heightMap->GetImage().GetPixelsSize();
	//memcpy(pixels, heightMap->GetImage().GetPixels(), size);
	pixels = heightMap->GetImage().GetPixels();
	_heightMap.reserve(size);
	for (int i = 0; i < size; i++) {
		_heightMap.push_back((pixels[i] / 255.f) * 250.f);
	}
	//std::reverse(_heightMap.begin(), _heightMap.end());
	//for (int i = 0; i < sizeX; i++) {
	//	std::reverse(_heightMap.begin() + (i * sizeZ), _heightMap.begin() + ((i + 1) * sizeZ));
	//}
	//for (int i = 0; i < sizeZ; i++) {
	//	std::reverse(_heightMap.begin() + (i * sizeX), _heightMap.begin() + ((i + 1) * sizeX));
	//}
}

float Terrain::GetHeight(float x, float z)
{
	//return _heightMap[x + (z * _sizeZ)];

	bool reverseQuad = ((static_cast<int>(z) % 2) != 0);
	x = x / 1.f;
	z = z / 1.f;
	if ((x < 0.0f) || (z < 0.0f) || (x >= _sizeX) || (z >= _sizeZ)) return(-100.0f);

	int ix = (int)x;
	int iz = (int)z;
	float xPercent = x - ix;
	float zPercent = z - iz;

	//float bottomLeft = (float)_heightMap[ix + (iz * _sizeX)];
	//float bottomRight = (float)_heightMap[(ix + 1) + (iz * _sizeX)];
	//float topLeft = (float)_heightMap[ix + ((iz + 1) * _sizeX)];
	//float topRight = (float)_heightMap[(ix + 1) + ((iz + 1) * _sizeX)];

	float bottomLeft = (float)_heightMap[x + (_sizeZ - 1 - z) * _sizeX];
	float bottomRight = (float)_heightMap[x + 1 + (_sizeZ - 1 - z) * _sizeX];
	float topLeft = (float)_heightMap[x + (_sizeZ - 2 - z) * _sizeX];
	float topRight = (float)_heightMap[x + 1 + (_sizeZ - 2 - z) * _sizeX];

	//if (reverseQuad)
	//{
	//	if (zPercent >= xPercent)
	//		bottomRight = bottomLeft + (topRight - topLeft);
	//	else
	//		topLeft = topRight + (bottomLeft - bottomRight);
	//}
	//else
	//{ 
	//	if (zPercent < (1.0f - xPercent))
	//		topRight = topLeft + (bottomRight - bottomLeft);
	//	else
	//		bottomLeft = topLeft + (bottomRight - topRight);
	//}

	float topHeight = topLeft * (1 - xPercent) + topRight * xPercent;
	float bottomHeight = bottomLeft * (1 - xPercent) + bottomRight * xPercent;
	float height = bottomHeight * (1 - zPercent) + topHeight * zPercent;

	//float height = _heightMap[ix + (iz * _sizeX)];

	return(height);
}

void Terrain::FinalUpdate()
{
	shared_ptr<Camera> mainCamera = GET_SINGLE(SceneManager)->GetActiveScene()->GetMainCamera();
	if (mainCamera == nullptr)
		return;

	Vec3 pos = mainCamera->GetTransform()->GetLocalPosition();
	_material->SetVec4(0, Vec4(pos.x, pos.y, pos.z, 0));
}