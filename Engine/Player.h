#pragma once
#include "MonoBehaviour.h"

class PlayerMove : public MonoBehaviour {
public:
	PlayerMove();
	virtual ~PlayerMove();

	virtual void Update() override;

private:
	// movemet
	float _movementSpeed = 500.f;

	// mouse
	float _mouseSensitivity = 0.01f;
	POINT _oldMousePos = {};
};