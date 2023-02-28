#include "../includes/Sample.h"

Sample::Sample(void *data, unsigned int byteSize) {
	if (byteSize > 0) {
		//We allocate the memory that Sample will use to store it's data.
		mSData = (char *) malloc(sizeof(char)*byteSize);
		if (memcpy(mSData, data, byteSize) != mSData) {
			throw std::exception("Could not copy data to Sample object");
		}
		mStringedSample = std::string(mSData);
	}
	else {
		throw std::exception("Sample must have a size greater than 0 bytes");
	}
}

std::string Sample::toString() {
	return mStringedSample;
}

Sample::~Sample() {
	if (mByteSize) {
		free(mSData);
	}
}

std::ostream& operator<<(std::ostream& os,const Sample& s) {
	return os << s.mStringedSample;
}