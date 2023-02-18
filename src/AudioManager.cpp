#include "../includes/AudioManager.h"
const std::map<path,AudioType> AudioManager::audiotype = {
	{path(".wav"),AudioType::WAV},
	{path(".wave"),AudioType::WAVE},
	{path(".mp3"),AudioType::MP3}
};

const char *AudioManager::DIR_NAME = "Songs";

const AudioType AudioManager::GetAudioType(path extension){
	AudioType type;
	try
	{
		type = audiotype.at(extension);
	}
	catch (const std::out_of_range&)
	{
		type = AudioType::NOT_SUPPORTED;
	}
	return type;
}

AudioManager::AudioManager(path p)
{
	string dyn_path = "./" + string(DIR_NAME) + "/" + p.filename().string();
	// using dynamic path: ./ + DIR_NAME + / + filename.extension
	const AudioType type = GetAudioType(p.filename().extension());
	try {
		switch (type)
		{
		case AudioType::WAV:
			OpenFile(dyn_path.c_str());
			WAVManager();
			break;
		case AudioType::MP3:
			OpenFile(dyn_path.c_str());
			MP3Manager();
			break;
		case AudioType::NOT_SUPPORTED:
			throw unsupportedexception();
			break;
		}
		CloseFile();
	}
	catch (const exception &ex) {
		cerr << "Error: " << ex.what() << " in AudioManager() for file " << dyn_path;
	}
}

void AudioManager::WAVManager() {
	//WIP
}

void AudioManager::OpenFile(const char *dyn_path) {
	mPFile= fopen(dyn_path, "r");

	if (!mPFile) {
		throw ioexception();
	}
}

void AudioManager::CloseFile(){
	if (fclose(mPFile) == EOF) {
		throw ioexception();
	}
}

void AudioManager::MP3Manager()
{
	//TODO
}

const char* unsupportedexception::what()const {
	return "unsupported file type";
}

const char* ioexception::what()const {
	return "input/output exception occurred";
}