#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include <exception>
#include <string>
#include <sstream>
//Sample is used store data related to samples in an audio file by passing it's size and a pointer to the data.
//This class copies the data from the pointer, this way you can reuse same pointer for other purposes.
class Sample {
public:
	Sample(void *data, unsigned int byteSize);
	void* GetData() {
		return mSData;
	};
	int size() {
		return mByteSize;
	};
	std::string toString();
	~Sample();
	
private:
	char* mSData;
	std::string mStringedSample;
	unsigned int mByteSize;
	friend std::ostream& operator<<(std::ostream& os, const Sample& s);
};