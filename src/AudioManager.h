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

	//Directory Name where all the audios will be checked.
	static const char DIR_NAME[];
	AudioManager(path p);
private:
	/*
	* <wave - form> → riff('wave'
	* < fmt - ck >				// format
	* [<fact - ck>]				// fact chunk
	* [<cue - ck>]				// cue points
	* [<playlist - ck>]			// playlist
	* [<assoc - data - list>]	// associated data list
	* <wave - data>)			// wave data
	*/
	void WAVManager();
	void MP3Manager();
	double Hz;
	path mPath;
	// Map with supported audio types that the audio manager can handle.
	const static std::map<path, AudioType> audiotype;
	// Closes the file.
	void CloseFile();
	// Opens the file to have read access.
	void OpenFile();
};