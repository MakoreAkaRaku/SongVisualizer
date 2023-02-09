#pragma once
#include <filesystem>
#include <iostream>

class Song {
public:
	Song(wchar_t* path);

	~Song() {
		delete mName;
		delete mPath;
		std::cout << "Goodbye!";
	}
private:
	wchar_t* mName;
	wchar_t* mPath;
	double mDuration;
};