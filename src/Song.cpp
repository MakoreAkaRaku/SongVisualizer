#include "Song.h"
Song::Song(const path &path) {
	mPath = path;
	mName= path.stem().string();
}
