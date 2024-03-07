#pragma once
#include <vector>
#include <string>

#include "Component.h"
#include "Define.h"
#include "SimpleMath.h"

class IGraphicsEngine;
class AObject;
class UObject;

enum DRAW_TYPE
{
	//background
	TESTBACKGROUND,
	TITLE,
	TITLECONTRACT,
	EXIT_BUTTON,
	EXIT_BUTTON2,
	CREDITBUTTON,
	CREDITBUTTON2,
	STAMP,
	CREDIT,

	//mesh
	TESTBOX,
	TESTGUN,
	TESTBALL,

	//Dog
	TESTDOG,
	
	//UI
	SETTING,
	SETTING2,
	KEYGUIDE,
	KEYGUIDE2,
	MISSIONPAPER,
	MISSIONPAPER2,
	MISSIONPAPER3,
	MISSIONPAPER4,
	MISSIONPAPERPIECE1,
	MISSIONPAPERPIECE2,
	MISSIONPAPERPIECE3,
	MISSIONPAPERPIECE4_1,
	MISSIONPAPERPIECE4_2,
	CHECK1,
	CHECK2,
	CHECK3,
	CHECK4,
	CHECK5,
	CHECK6,
	MENUBOARD,
	MENUGUIDE,
	MENUGUIDE2,
	MENUGUIDEBOARD,
	MENUALBUM,
	MENUALBUM2,
	MENUGAMEEXIT,
	MENUGAMEEXIT2,
	CLOSE,    
	CLOSE2,    

	//CUTSCENE
	IMAGINECUTSCENE1,
	IMAGINECUTSCENE2,
	IMAGINECUTSCENE3,


	TITLESTART,
	TITLESTART2,
};

class DrawType : public Component
{
public:
	DrawType(Entity* _entity);
	virtual ~DrawType();

	// �̰Ÿ� Template�� �ϴ� ��� ã�ƺ���.
	void CreateRenderType(DRAW_TYPE _drawType, IGraphicsEngine* _renderer);

	// ���ø����� Ÿ���� ���ϰ� �� Ÿ�Կ� ���� ���� �ٸ� load�� �ִ´�. 

	virtual void Update(float _deltatime) override;
	virtual void Render() override;

	void SetAObject(AObject* _nowObject);
	void SetUObject(UObject* _nowUObject) { uObjectRender = _nowUObject; }
	AObject* GetAObject();
	

	void SetUIVisible(bool _isUIVisible) { isUIVisible = _isUIVisible; };
	void SetAObjectVisible(bool _isAObjectVisible) { isAObjectVisible = _isAObjectVisible; }

	void GetDog(AObject* _dogAObject) { dogAObject = _dogAObject; }
private:
	DirectX::SimpleMath::Vector3 ToEulerAngles(DirectX::SimpleMath::Quaternion _q);

	float dt = 0.0f;

	// Render Type�� ���� �ٲ��.
	std::wstring path[2] = {};
	std::wstring texturePath = {};
	AObject* aObjectRender = {};

	//UI�� ���� Render
	UObject* uObjectRender = {};
	UObject* uObjectAniRender = {};

	//attach UI�� ���� ������
	AObject* dogAObject;


	float windowHeight;
	float windowWidth;

	float UIScaleX;
	float UIScaleY;

	std::wstring upath[2]
	{
		L"../Shader/compiled/UIVertexShader.cso",
		L"../Shader/compiled/UIPixelShader.cso",
	};

public:
	bool isUIVisible;
	bool isAObjectVisible;
	float contractUp;
};