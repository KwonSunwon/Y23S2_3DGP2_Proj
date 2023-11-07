#pragma once
#include "Component.h"

enum class BillboardType : unsigned short {
	TYPE0 = 0,
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4,
};

struct BillboardData {
	Vec3 position;
	Vec2 size;
	BillboardType type;
};

class Billboard : public Component {
public:
	Billboard();
	virtual ~Billboard();

	virtual void FinalUpdate() override;

private:
	vector<BillboardData> _billboardData;
};

