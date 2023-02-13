#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include "AudioManager.h"
//#include "Visualizer.h"
using namespace std::filesystem;
class Song {
public:
	Song(const path &songPath);

private:
	std::string mName;
	path mPath;
	double mDuration;
	friend std::ostream& operator<<(std::ostream& os, const Song& s);
};