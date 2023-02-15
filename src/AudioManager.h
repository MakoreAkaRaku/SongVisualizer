#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include <filesystem>
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std::filesystem;

// Possible Audio types that exist.
enum class AudioType {
	WAV = 0,
	WAVE= WAV,
	MP3,
	NOT_SUPPORTED
};

class AudioManager {
public:
	// Returns the AudioType from the pathfile.
	// If the file is not supported yet, returns NOT_SUPPORTED.
	static const AudioType GetAudioType(path p);
	AudioManager(path p);
private:
	void WAVManager();
	void MP3Manager();
	double Hz;
	// Map with supported audio types that the audio manager can handle.
	const static std::map<path, AudioType> audiotype;
};