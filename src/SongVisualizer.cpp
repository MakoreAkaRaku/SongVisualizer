#include "../includes/SongVisualizer.h"

int WinMain(int argc, char** argv)
{

}
int main(int n, char **args) {
	try {
		path c_path = SetDirectory();
		list<Song> songList = CreatePlayList(c_path);
		while (songList.empty()) {
			cerr << "Directory has no songs, please put at least a song\nPress 'Enter' key to continue\n";
			cin.get();
			songList = CreatePlayList(c_path);
		}
		cout << endl << "Found " << songList.size() << "songs" << endl;
		for (auto s : songList) {
			cout << s;
			if (&s != &songList.back())
				cout << "\n";
		}
		songList.back().GetDataFromAudio();
	}
	catch (exception& ex)
	{
		cerr << ex.what();
	}
}

list<Song> CreatePlayList(path sPath) {
	list<Song> songList = list<Song>();
	if (!fs::is_empty(sPath)) {
		directory_iterator dir_it = directory_iterator(sPath);
		//For each file we must see if the format is supported
		for (directory_entry entry : dir_it) {
			path filename = entry.path().filename();
			//We verify that we can do a visualizer for that format
			const bool isValidFormat = (AudioManager::GetAudioType(filename.extension())) != AudioType::NOT_SUPPORTED;
			if (isValidFormat) {
				Song s = Song(entry.path());
				songList.push_back(s);
			}
		}
	}
	return songList;
}

path SetDirectory()
{
	error_code err;
	path c_path = current_path();
	c_path.append(AudioManager::DIR_NAME);
	if (!exists(c_path))
	{
		if (!create_directory(c_path, err))
		{
			string err_msg = string("Could not create ") + string(AudioManager::DIR_NAME, " directory");
			throw exception(err_msg.c_str());
		}
	}

}