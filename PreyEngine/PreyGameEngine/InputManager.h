#pragma once
#include "headers.h"

/// <summary>
/// InputManager - Ű����� ���콺�� �Է��� ������ش�.
/// 
/// 2024.01.09 chlaudrl
/// </summary>

enum class KEY_STATE
{
	NONE, //Ű�� ������ ���� ����
	TAP, //Ű�� �� ���� ����
	HOLD, //Ű�� ������ �ִ� ����
	AWAY, //Ű�� �� �� ����
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L, Z,
	X, C, V, B, N, M,

	ALT, CTRL, LSHIFT, SPACE, ENTER, ESC, TAB,

	F1, F2, F3, F4, F5, F6, F7, F8, F9,
	LMOUSE, RMOUSE, UPBUTTON, DOWNBUTTON,

	LAST,
};

struct KeyInfo
{
	KEY_STATE state;
	bool prevPush;
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void Initalize(HWND _hwnd);
	void Update();
	void Finalize();

	KEY_STATE GetKeyState(KEY _key) const { return keyinfo[static_cast<int>(_key)].state; }
	bool IsKeyState(const KEY& _key, const KEY_STATE& _state) const;
	POINT GetCurrentMousePos() const { return currentMousePos; }

private:
	HWND hwnd;

	const int matchVK[static_cast<int>(KEY::LAST)];
	std::vector<KeyInfo> keyinfo;

	POINT currentMousePos; //���� ���콺 ��ġ
};

