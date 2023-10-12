#pragma once
#include "MonoBehaviour.h"

class PlayerMove : public MonoBehaviour {
public:
	PlayerMove();
	virtual ~PlayerMove();

	virtual void Update() override;

private:
	float _speed = 5.f;
};