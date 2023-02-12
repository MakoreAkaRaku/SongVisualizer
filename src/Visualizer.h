#pragma once
#include <string>
#include <set>

class Visualizer{
public:
	const static std::set<std::string> SUPPORTED_FORMATS; // , ".mp3", ".wma", ".flag"
private:
	byte* data;

};