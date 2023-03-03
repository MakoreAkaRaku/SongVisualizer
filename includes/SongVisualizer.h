#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include <string>
#include <iostream>
#include "Song.h"
#include <list>
#include <windows.h>

using namespace std;
namespace fs = filesystem;

/// Returns a list with Songs that are currently supported.
/// Returns an empty list if there's no supported format.
list<Song> CreatePlayList(path sPath);

// Sets the directory where the songs must be localized.
path SetDirectory();