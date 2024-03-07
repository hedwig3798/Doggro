#pragma once

enum class OBJECT_TYPE
{
	BACKGROUND, //배경
	TILE, //타일
	UI,	  //UI
	FRONT_UI
};

enum class OBJECT_STATE
{
	ALIVE,
	TO_BE_DESTROYED,
	DESTROY,
};

enum class RENDER_TYPE
{
	TESTBOX,
	TESTGUN,
	TESTDOG,
	TESTBALL,
	TESTBACKGROUND,
	TESTUI,
};

//enum class FilterGroup
//{
//	DEFAULT = (1 << 0),
//	STATIC = (1 << 1),
//	BOX = (1 << 2),
//	SPHERE = (1 << 3),
//};

