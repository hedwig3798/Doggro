#pragma once
#include "Singleton.h"
#include <map>
#include "fmod.hpp"

// 배경음악!
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

// 효과음!
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

	// Sound 다운로드
	void CreateBGM(const char* _filePath, BGM _bgm, bool _isLoop);
	void CreateEffect(const char* _filePath, EFFECT _effect, bool _isLoop);

	// Sound 음량 조절
	void SetBGMVolume(BGM _bgm, float _vol);
	void SetEffectVolume(EFFECT _effect, float _vol);

	// Sound Play
	void PlayBGM(BGM _bgm);
	void PlayEffect(EFFECT _effect);

	// Sound Stop
	void StopBGM(BGM _bgm);
	void StopEffect(EFFECT _effect);

	// 모든 Sound를 정지한다.
	void StopAllSound();

	// 모든 Effect를 정지시킨다.
	void StopAllEffect();

	// 모든 Sound 음량 세팅
	void SetAllBGMVolume(float _vol);
	void SetAllEffectVolume(float _vol);

	// 모든 BGM Volume 증가 감소
	void AddAllBGMVolume(float _vol);
	void SubAllBGMVolume(float _vol);

	// 모든 Effect Volume 증가 감소
	void AddAllEffectVolume(float _vol);
	void SubAllEffectVolume(float _vol);

private:
	bool isLoop;
	bool isPlaying;

	float currentBGMVolume = 0.5f;
	float currentEffectVolume = 0.5f;

	// FMOD System
	FMOD::System* system;

	// FMOD가 정상적으로 작동 하는지 안 하는지 알려 줄 수 있는 Error Message다.
	FMOD_RESULT result;

	// BGM sound 및 channel
	FMOD::Sound* bgmSound[static_cast<int>(BGM::BGMSOUND_END)];
	FMOD::Channel* bgmChannel[static_cast<int>(BGM::BGMSOUND_END)];

	// Effect sound 및 channel
	FMOD::Sound* effectSound[static_cast<int>(EFFECT::EFFECT_END)];
	FMOD::Channel* effectChannel[static_cast<int>(EFFECT::EFFECT_END)];

	// BGM저장할 친구

};

