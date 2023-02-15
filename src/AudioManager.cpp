#include "AudioManager.h"
const std::map<path,AudioType> AudioManager::audiotype = {
	{path(".wav"),AudioType::WAV},
	{path(".wave"),AudioType::WAVE},
	{path(".mp3"),AudioType::MP3}
};
const AudioType AudioManager::GetAudioType(path p){
	AudioType type;
	try
	{
		type = audiotype.at(p);
	}
	catch (const std::out_of_range&)
	{
		type = AudioType::NOT_SUPPORTED;
	}
	return type;
}

AudioManager::AudioManager(path p)
{
	AudioType type = GetAudioType(p);
	switch (type)
	{
	case AudioType::WAV:
		WAVManager();
		break;
	case AudioType::MP3:
		MP3Manager();
		break;
	default:
		break;
	}
}

void AudioManager::WAVManager() {
	//WIP
}

void AudioManager::MP3Manager()
{
	//TODO
}
