#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include <string>
#include <iostream>
#include "Song.h"

using namespace std;
using namespace VISUALIZER;
namespace fs = filesystem;

const char DIR_NAME[] = "Songs";
const std::string GIT_FILE = std::string(".gitignore");
list<Song>* CreatePlayList(path sPath);