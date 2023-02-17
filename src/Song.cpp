#include "Song.h"

Song::Song(const path &path) {
	mPath = path;
	mName = path.stem().string();
}

void Song::GetDataFromAudio() {
	const AudioManager am = AudioManager(mPath);
}
std::ostream &operator<<(std::ostream& os, const Song &s)
{
	return os << s.mName;
}
