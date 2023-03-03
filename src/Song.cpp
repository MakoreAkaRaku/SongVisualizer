#include "../includes/Song.h"

Song::Song(const path &path) {
	mPath = path;
	mName = path.stem().string();
}

void Song::GetDataFromAudio() {
	AudioManager am = AudioManager(mPath);
	mBytesPerSec = am.GetBytesPerSec();
	mSamplesPerSec = am.GetSamplesPerSec();
	mBytesPerSample = am.GetBytesPerSample();
}
std::ostream &operator<<(std::ostream& os, const Song &s)
{
	return os << s.mName;
}
