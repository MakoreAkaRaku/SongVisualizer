#include "SongVisualizer.h"

int main(int n, char **args) {
	error_code err;
	path c_path = current_path();
	c_path.append(DIR_NAME);
	if (!exists(c_path)){
		if (!create_directory(c_path,err)) {
			cerr<< err.message();
			return 1;
		}
	}
	list<Song> *songList = CreatePlayList(c_path);
	while (songList->empty()) {
		//delete songList;
		cerr << "Directory has no songs, please put at least a song\nPress 'Enter' key to continue\n";
		cin.get();
		songList = CreatePlayList(c_path);
	}
	cout << songList;
}

//Returns a list with Songs that are currently supported. Returns en empty list there's no supported format.
list<Song>* CreatePlayList(path sPath) {
	list<Song> *songList = new list<Song>();
	if (!fs::is_empty(sPath)) {
		directory_iterator dir_it = directory_iterator(sPath);
		//For each file we must see if the format is supported
		for (directory_entry entry : dir_it) {
			path filename = entry.path().filename();
			//We verify that we can do a visualizer for that format
			bool isValidFormat = (Visualizer::SUPPORTED_FORMATS.find(filename.extension().string())) != Visualizer::SUPPORTED_FORMATS.end();
			if (isValidFormat) {
				Song s = Song(entry.path());
				songList->push_back(s);
			}
		}
	}
	return songList;
}