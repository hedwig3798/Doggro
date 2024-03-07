#include "InputManager.h"

InputManager::InputManager()
	:matchVK{
	VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L','Z',
	'X','C','V','B','N','M',

	VK_MENU, // ALT,
	VK_CONTROL, // CTRL,
	VK_LSHIFT, // LSHIFT,
	VK_SPACE, // SPACE,
	VK_RETURN, // ENTER,
	VK_ESCAPE, // ESC,
	VK_TAB, //TAB

	VK_F1, // F1
	VK_F2, // F2
	VK_F3, // F3
	VK_F4, // F4
	VK_F5, // F5
	VK_F6, // F6
	VK_F7, // F7
	VK_F8, // F8
	VK_F9, // F9

	VK_LBUTTON, // LBTN
	VK_RBUTTON, // RBTN
	VK_XBUTTON2,  // 위 버튼
	VK_XBUTTON1, // 아래 버튼

	},
	keyinfo{},
	hwnd(nullptr),
	currentMousePos{}
{

}

InputManager::~InputManager()
{

}

void InputManager::Initalize(HWND _hwnd)
{
	hwnd = _hwnd;
	for (int i = 0; i < static_cast<int>(KEY::LAST); i++)
	{
		keyinfo.push_back(KeyInfo{ KEY_STATE::NONE,false });
	}
}

void InputManager::Update()
{
	HWND isFocusHwnd = GetFocus();


	//현재 포커스 중일 때
	if (nullptr != isFocusHwnd)
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); i++)
		{
			if (GetAsyncKeyState(matchVK[i]) & 0x8000)
			{
				if (keyinfo[i].prevPush)
					keyinfo[i].state = KEY_STATE::HOLD;
				else
					keyinfo[i].state = KEY_STATE::TAP;
				keyinfo[i].prevPush = true;
			}
			else
			{
				if (keyinfo[i].prevPush)
					keyinfo[i].state = KEY_STATE::AWAY;
				else
					keyinfo[i].state = KEY_STATE::NONE;
				keyinfo[i].prevPush = false;
			}
		}
		//마우스 위치 계산
		GetCursorPos(&currentMousePos);
		ScreenToClient(hwnd, &currentMousePos);
	}
	else
	{
		for (int i = 0; i < static_cast<int>(KEY::LAST); i++)
		{
			keyinfo[i].prevPush = false;
			if (KEY_STATE::TAP == keyinfo[i].state || KEY_STATE::HOLD == keyinfo[i].state)
				keyinfo[i].state = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == keyinfo[i].state)
				keyinfo[i].state = KEY_STATE::NONE;
		}
	}
}

void InputManager::Finalize()
{
	keyinfo.clear();
}

bool InputManager::IsKeyState(const KEY& _key, const KEY_STATE& _state) const
{
	if (_state == GetKeyState(_key))
		return true;
	return false;
}

