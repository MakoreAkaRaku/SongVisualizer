#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include "SongVisualizer.h"
#include <filesystem>
#include <iostream>
using namespace std::filesystem;

int main(int n, char **args) {
	std::error_code err;
	path c_path = current_path();
	c_path.append(DIR_NAME);
	if (!exists(c_path)){
		if (!create_directory(c_path,err)) {
			std::cerr<< err.message();
			return 1;
		}
	}
	directory_iterator dir_it = directory_iterator(c_path);
	directory_iterator itBeg = begin(dir_it);
	directory_iterator itEnd = end(dir_it);
	itBeg++;
	while (is_empty(c_path)|| itBeg == itEnd) {
		std::cerr << "Directory has no songs, please put at least a song\nPress 'Enter' key to continue\n";
		std::cin.get() >> n;
		dir_it = directory_iterator(c_path);
		itBeg = begin(dir_it);
		itEnd = end(dir_it);
		itBeg++;
	}
	std::cout << c_path;
}