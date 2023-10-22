#include "pch.h"
#include "Player.h"
#include "Transform.h"
#include "GameObject.h"
#include "Input.h"
#include "Timer.h"
#include "SceneManager.h"
#include "Engine.h"

PlayerMove::PlayerMove()
{
	_oldMousePos = INPUT->GetMousePos();
}

PlayerMove::~PlayerMove()
{
}

void PlayerMove::Update()
{
	Vec3 pos = GetTransform()->GetLocalPosition();
	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _movementSpeed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _movementSpeed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _movementSpeed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _movementSpeed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::Q))
		pos += GetTransform()->GetUp() * _movementSpeed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::E))
		pos -= GetTransform()->GetUp() * _movementSpeed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::ESC))
		PostQuitMessage(0);

	POINT mousePos = INPUT->GetMousePos();
	float deltaX = static_cast<float>(mousePos.x - _oldMousePos.x);
	float deltaY = static_cast<float>(mousePos.y - _oldMousePos.y);
	Vec3 rot = GetTransform()->GetLocalRotation();
	rot.y += deltaX * _mouseSensitivity;
	rot.x += deltaY * _mouseSensitivity;

	::SetCursorPos(_oldMousePos.x, _oldMousePos.y);

	GetTransform()->SetLocalRotation(rot);
	GetTransform()->SetLocalPosition(pos);
}
