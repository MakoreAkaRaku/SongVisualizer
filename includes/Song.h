#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include "AudioManager.h"
//#include "Visualizer.h"
using namespace std::filesystem;
class Song {
public:
	Song(const path &songPath);
	void GetDataFromAudio();

private:
	std::string mName;
	path mPath;
	//Duration of the song in milliseconds (for now).
	double mDuration;
	unsigned int mBytesPerSec, mSamplesPerSec, mBytesPerSample;
	friend std::ostream& operator<<(std::ostream& os, const Song& s);
};