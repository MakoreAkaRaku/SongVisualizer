#include "Song.h"

Song::Song(const path &path) {
	mPath = path;
	mName = path.stem().string();
}

std::ostream &operator<<(std::ostream& os, const Song &s)
{
	return os << s.mName;
}
