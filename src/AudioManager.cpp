#include "AudioManager.h"
const std::map<path,AudioType> AudioManager::audiotype = {
	{path(".wav"),AudioType::WAV},
	{path(".wave"),AudioType::WAVE},
	{path(".mp3"),AudioType::MP3}
};

const char *AudioManager::DIR_NAME = "Songs";

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
	string dyn_path = "./" + string(DIR_NAME) + "/" + p.filename().string();
	// using dynamic path: ./ + DIR_NAME + / + filename.extension
	const AudioType type = GetAudioType(p);
	try {
		if (type == AudioType::NOT_SUPPORTED) {
			throw unsupportedexception();
		}
		// Opening the file to process it
		OpenFile(dyn_path.c_str());
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
		CloseFile();
	}
	catch (exception ex) {
		cerr << "Error: " << ex.what() << "in AudioManager() for file " << dyn_path;
	}
}

void AudioManager::WAVManager() {
	//WIP
}

void AudioManager::OpenFile(const char *dyn_path) {
	fopen_s(&mPFile,dyn_path,"r");
	//mPFile = fopen_s(dyn_path,"r");
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

const char* unsupportedexception::what()noexcept {
	return "unsupported file type";
}

const char* ioexception::what()noexcept {
	return "input/output exception occurred";
}