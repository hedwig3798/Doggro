#include "AudioManager.h"
#include "PathManager.h"

AudioManager::AudioManager()
	: isLoop{}, system{}, bgmSound{}, bgmChannel{}
	, effectSound{}, effectChannel{}, isPlaying{}, result{}
{

}

AudioManager::~AudioManager()
{
	system->close();
	system->release();
}

void AudioManager::Initialize(PathManager* _pathManager)
{
	FMOD::System_Create(&system);
	result = system->init(100, FMOD_INIT_NORMAL, nullptr);

	/// BGM 담기
	std::string s = _pathManager->GetPath("Sound/Sweet Dreams My Dear.mp3");
	CreateBGM(_pathManager->GetPath("Sound/bgm_4_1_stage.wav").c_str(), BGM::TITLE, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_1_stage.wav").c_str(), BGM::STAGE1, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_2_stage.wav").c_str(), BGM::STAGE2, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_3_stage.wav").c_str(), BGM::STAGE3, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_4_1_stage.wav").c_str(), BGM::STAGE4, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_4_1_cut.wav").c_str(), BGM::STAGE4CUT, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_ending.wav").c_str(), BGM::STAGE4END, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_minigame.wav").c_str(), BGM::MINIGAME, true);
	CreateBGM(_pathManager->GetPath("Sound/bgm_next_stage.wav").c_str(), BGM::NEXT, true);

	/// Effect 담기
	CreateEffect(_pathManager->GetPath("Sound/dog_75_walk.wav").c_str(), EFFECT::Dog_SevenTeenFive_Walk, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_baby_bark.wav").c_str(), EFFECT::Dog_Baby_Bark, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_jump.wav").c_str(), EFFECT::Dog_Jump, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_lie.wav").c_str(), EFFECT::Dog_Lie, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_normal_bark.wav").c_str(), EFFECT::Dog_Normal_Bark, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_pick_up.wav").c_str(), EFFECT::Dog_Pick_Up, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_put_down.wav").c_str(), EFFECT::Dog_Put_Down, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_sit.wav").c_str(), EFFECT::Dog_Sit, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_smell.wav").c_str(), EFFECT::Dog_Smell, false);
	CreateEffect(_pathManager->GetPath("Sound/dog_walk.wav").c_str(), EFFECT::Dog_Walk, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_calendar.wav").c_str(), EFFECT::Calender, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_click.wav").c_str(), EFFECT::Click, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_clock.wav").c_str(), EFFECT::Clock, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_cut_paper.wav").c_str(), EFFECT::Cut_Paper, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_cut_rope.wav").c_str(), EFFECT::Cut_Rope, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_door_open.wav").c_str(), EFFECT::Door_Open, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_hide.wav").c_str(), EFFECT::Hide, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_knock.wav").c_str(), EFFECT::Knock, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_obj_drop.wav").c_str(), EFFECT::Obj_drop, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_pick_up.wav").c_str(), EFFECT::Pick_Up, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_rope.wav").c_str(), EFFECT::Rope, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_set_bowl.wav").c_str(), EFFECT::Set_Bowl, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_shutter.wav").c_str(), EFFECT::Shutter, false);
	CreateEffect(_pathManager->GetPath("Sound/eft_success.wav").c_str(), EFFECT::Success, false);
	CreateEffect(_pathManager->GetPath("Sound/human_cry.wav").c_str(), EFFECT::Human_Cry, false);
	CreateEffect(_pathManager->GetPath("Sound/human_stand_sit.wav").c_str(), EFFECT::Human_Stand_Sit, false);
	CreateEffect(_pathManager->GetPath("Sound/human_surprise_stand.wav").c_str(), EFFECT::Human_Surprise, false);
	CreateEffect(_pathManager->GetPath("Sound/human_walk.wav").c_str(), EFFECT::Human_Walk, false);

	SetAllBGMVolume(currentBGMVolume);
	SetAllEffectVolume(currentEffectVolume);
}

void AudioManager::Update()
{
	system->update();
}

void AudioManager::CreateBGM(const char* _filePath, BGM _bgm, bool _isLoop)
{
	if (_isLoop == true)
	{
		result = system->createSound(_filePath, FMOD_LOOP_NORMAL, 0, &bgmSound[static_cast<int>(_bgm)]);
	}
	else
	{
		result = system->createSound(_filePath, FMOD_LOOP_OFF, 0, &bgmSound[static_cast<int>(_bgm)]);
	}
}

void AudioManager::CreateEffect(const char* _filePath, EFFECT _effect, bool _isLoop)
{
	if (_isLoop == true)
	{
		result = system->createSound(_filePath, FMOD_LOOP_NORMAL, 0, &effectSound[static_cast<int>(_effect)]);
	}
	else
	{
		result = system->createSound(_filePath, FMOD_LOOP_OFF, 0, &effectSound[static_cast<int>(_effect)]);
	}
}

void AudioManager::SetBGMVolume(BGM _bgm, float _vol)
{
	result = bgmChannel[static_cast<int>(_bgm)]->setVolume(_vol);
}

void AudioManager::SetEffectVolume(EFFECT _effect, float _vol)
{
	result = effectChannel[static_cast<int>(_effect)]->setVolume(_vol);
}

void AudioManager::PlayBGM(BGM _bgm)
{
	result = bgmChannel[static_cast<int>(_bgm)]->isPlaying(&isPlaying);
	if (!isPlaying)
	{
		result = system->playSound(bgmSound[static_cast<int>(_bgm)], 0, false, &bgmChannel[static_cast<int>(_bgm)]);
	}
}

void AudioManager::PlayEffect(EFFECT _effect)
{
	result = effectChannel[static_cast<int>(_effect)]->isPlaying(&isPlaying);
	if (!isPlaying)
	{
		result = system->playSound(effectSound[static_cast<int>(_effect)], 0, false, &effectChannel[static_cast<int>(_effect)]);
	}
}

void AudioManager::StopBGM(BGM _bgm)
{
	result = bgmChannel[static_cast<int>(_bgm)]->stop();
	isPlaying = false;
}

void AudioManager::StopEffect(EFFECT _effect)
{
	result = effectChannel[static_cast<int>(_effect)]->stop();
	isPlaying = false;
}

void AudioManager::StopAllSound()
{
	// C-Style로 BGMSound를 돌면서 BGM Sound를 Stop 한다.
	for (int i = static_cast<int>(BGM::BGMSOUND_START); i < static_cast<int>(BGM::BGMSOUND_END); i++)
	{
		if (bgmChannel[i] == nullptr)
		{
			continue;
		}
		result = bgmChannel[i]->stop();
	}

	// C-Style로 EffectSound를 돌면서 Effect Sound를 Stop 한다.
	for (int i = static_cast<int>(EFFECT::EFFECT_START); i < static_cast<int>(EFFECT::EFFECT_END); i++)
	{
		if (effectChannel[i] == nullptr)
		{
			continue;
		}
		result = effectChannel[i]->stop();
	}

	isPlaying = false;
}

void AudioManager::StopAllEffect()
{
	// C-Style로 EffectSound를 돌면서 Effect Sound를 Stop 한다.
	for (int i = static_cast<int>(EFFECT::EFFECT_START); i < static_cast<int>(EFFECT::EFFECT_END); i++)
	{
		if (effectChannel[i] == nullptr)
		{
			continue;
		}
		result = effectChannel[i]->stop();
	}
	isPlaying = false;
}

void AudioManager::SetAllBGMVolume(float vol)
{
	for (int i = static_cast<int>(BGM::BGMSOUND_START); i < static_cast<int>(BGM::BGMSOUND_END); i++)
	{
		if (bgmChannel[i] == nullptr)
		{
			continue;
		}
		result = bgmChannel[i]->setVolume(vol);
	}
}

void AudioManager::SetAllEffectVolume(float vol)
{
	for (int i = static_cast<int>(EFFECT::EFFECT_START); i < static_cast<int>(EFFECT::EFFECT_END); i++)
	{
		if (effectChannel[i] == nullptr)
		{
			continue;
		}
		result = effectChannel[i]->setVolume(vol);
	}
}

void AudioManager::AddAllBGMVolume(float vol)
{
	currentBGMVolume += vol;
	if (currentBGMVolume >= 300.0f)
	{
		currentBGMVolume = 300.0f;
	}
	SetAllBGMVolume(currentBGMVolume);
}

void AudioManager::SubAllBGMVolume(float vol)
{
	currentBGMVolume -= vol;
	if (currentBGMVolume <= 0.0f)
	{
		currentBGMVolume = 0.0f;
	}
	SetAllBGMVolume(currentBGMVolume);
}

void AudioManager::AddAllEffectVolume(float vol)
{
	currentEffectVolume += vol;
	if (currentEffectVolume >= 300.0f)
	{
		currentEffectVolume = 300.0f;
	}
	SetAllEffectVolume(currentEffectVolume);
}

void AudioManager::SubAllEffectVolume(float vol)
{
	currentEffectVolume -= vol;
	if (currentEffectVolume <= 0.0f)
	{
		currentEffectVolume = 0.0f;
	}
	SetAllEffectVolume(currentEffectVolume);
}
