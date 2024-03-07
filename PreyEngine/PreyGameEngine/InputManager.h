#pragma once
#include "headers.h"

/// <summary>
/// InputManager - 키보드와 마우스의 입력을 담당해준다.
/// 
/// 2024.01.09 chlaudrl
/// </summary>

enum class KEY_STATE
{
	NONE, //키가 눌리지 않은 상태
	TAP, //키를 막 누른 상태
	HOLD, //키를 누르고 있는 상태
	AWAY, //키를 막 뗸 상태
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

	POINT currentMousePos; //현재 마우스 위치
};

