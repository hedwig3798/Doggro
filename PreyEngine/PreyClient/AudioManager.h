#pragma once
#include "Singleton.h"
#include <map>
#include "fmod.hpp"

// �������!
enum class BGM
{
	BGMSOUND_START,
	TITLE,
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE4CUT,
	STAGE4END,
	MINIGAME,
	NEXT,

	BGMSOUND_END
};

// ȿ����!
enum class EFFECT
{
	EFFECT_START,
	Dog_SevenTeenFive_Walk,
	Dog_Baby_Bark,
	Dog_Jump,
	Dog_Lie,
	Dog_Normal_Bark,
	Dog_Pick_Up,
	Dog_Put_Down,
	Dog_Sit,
	Dog_Smell,
	Dog_Walk,
	Calender,
	Click,
	Clock,
	Cut_Paper,
	Cut_Rope,
	Door_Open,
	Hide,
	Knock,
	Obj_drop,
	Pick_Up,
	Rope,
	Set_Bowl,
	Shutter,
	Success,
	Human_Cry,
	Human_Stand_Sit,
	Human_Surprise,
	Human_Walk,

	EFFECT_END
};

class PathManager;

class AudioManager : public Singleton<AudioManager>
{
public:
	AudioManager();
	virtual ~AudioManager();

	void Initialize(PathManager* _pathManager);
	void Update();

	// Sound �ٿ�ε�
	void CreateBGM(const char* _filePath, BGM _bgm, bool _isLoop);
	void CreateEffect(const char* _filePath, EFFECT _effect, bool _isLoop);

	// Sound ���� ����
	void SetBGMVolume(BGM _bgm, float _vol);
	void SetEffectVolume(EFFECT _effect, float _vol);

	// Sound Play
	void PlayBGM(BGM _bgm);
	void PlayEffect(EFFECT _effect);

	// Sound Stop
	void StopBGM(BGM _bgm);
	void StopEffect(EFFECT _effect);

	// ��� Sound�� �����Ѵ�.
	void StopAllSound();

	// ��� Effect�� ������Ų��.
	void StopAllEffect();

	// ��� Sound ���� ����
	void SetAllBGMVolume(float _vol);
	void SetAllEffectVolume(float _vol);

	// ��� BGM Volume ���� ����
	void AddAllBGMVolume(float _vol);
	void SubAllBGMVolume(float _vol);

	// ��� Effect Volume ���� ����
	void AddAllEffectVolume(float _vol);
	void SubAllEffectVolume(float _vol);

private:
	bool isLoop;
	bool isPlaying;

	float currentBGMVolume = 0.5f;
	float currentEffectVolume = 0.5f;

	// FMOD System
	FMOD::System* system;

	// FMOD�� ���������� �۵� �ϴ��� �� �ϴ��� �˷� �� �� �ִ� Error Message��.
	FMOD_RESULT result;

	// BGM sound �� channel
	FMOD::Sound* bgmSound[static_cast<int>(BGM::BGMSOUND_END)];
	FMOD::Channel* bgmChannel[static_cast<int>(BGM::BGMSOUND_END)];

	// Effect sound �� channel
	FMOD::Sound* effectSound[static_cast<int>(EFFECT::EFFECT_END)];
	FMOD::Channel* effectChannel[static_cast<int>(EFFECT::EFFECT_END)];

	// BGM������ ģ��

};

