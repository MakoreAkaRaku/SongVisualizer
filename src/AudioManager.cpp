#include "../includes/AudioManager.h"
const std::map<path, AudioType> AudioManager::mAudioType = {
	{path(".wav"),AudioType::WAV},
	{path(".wave"),AudioType::WAVE},
	{path(".mp3"),AudioType::MP3}
};

const char* AudioManager::DIR_NAME = "Songs";

const AudioType AudioManager::GetAudioType(path extension) {
	AudioType type;
	try
	{
		type = mAudioType.at(extension);
	}
	catch (const std::out_of_range&)
	{
		type = AudioType::NOT_SUPPORTED;
	}
	return type;
}

AudioManager::AudioManager(path p)
{
	string dyn_path = "./" + string(DIR_NAME) + "/" + p.filename().string();
	// using dynamic path: ./ + DIR_NAME + / + filename.extension
	mType = GetAudioType(p.filename().extension());
	try {
		OpenFile(dyn_path.c_str());
		switch (mType)
		{
		case AudioType::WAV:
			WAVManager();
			break;
		case AudioType::MP3:
			OpenFile(dyn_path.c_str());
			MP3Manager();
			break;
		case AudioType::NOT_SUPPORTED:
			throw unsupportedexception();
			break;
		}
	}
	catch (const exception& ex) {
		cerr << "Error: " << ex.what() << " in AudioManager() for file " << dyn_path;

	}
	CloseFile();
}

list<list<Sample*>> AudioManager::GetChannelsData() {
	return mChannelData;
}

unsigned int AudioManager::GetNumOfSamplesPerChan() {
	return mNOfSampPerChan;
}
unsigned int AudioManager::GetNumOfBytesPerSample() {
	return mBytesPerSample;
}
unsigned int AudioManager::GetNumOfBytesPerSec() {
	return mBytesPerSec;
}
void AudioManager::WAVManager() {

	size_t headerSize = sizeof(WAV_Header);
	try {
		mWav_hdr = (WAV_Header*)malloc(headerSize);
		if (!mWav_hdr) {
			throw exception("Could not allocate more memory");
		}
		if (fread(mWav_hdr, 1, headerSize, mPFile) != headerSize) {
			throw exception("WAV-File reading was not possible");
		}
		mBytesPerSec = mWav_hdr->bytesPerSec;
		mBytesPerSample = mWav_hdr->bitsPerSample / 8;
		// NºSamples = dataSize / (NºOfChannels * bytesPerSample).
		mNOfSampPerChan = mWav_hdr->Subchunk2Size / (mWav_hdr->NumOfChan * mBytesPerSample);
		for (size_t i = 0; i < mWav_hdr->NumOfChan; i++)
		{
			mChannelData.push_back(list<Sample*>());
		}
		//For each sample
		char* dataBuff = (char*)malloc(sizeof(char) * mBytesPerSample);
		if (!dataBuff) {
			throw exception("Could not allocate more memory");
		}
		for (size_t i = 0; i < mNOfSampPerChan; i++)
		{
			//We read the sample from the wav file.
			if (fread(dataBuff, 1, mBytesPerSample, mPFile) != mBytesPerSample) {
				throw exception("WAV-File reading was not possible");
			}
			//For right Channel we create a Sample.
			mChannelData.front().push_back(new Sample(dataBuff, mBytesPerSample));
		}
		//If there's another channel, repeat it to store in the left channel.
		if (mWav_hdr->NumOfChan > 1) {
			for (size_t i = 0; i < mNOfSampPerChan; i++)
			{
				//We read the sample from the wav file.
				if (fread(dataBuff, 1, mBytesPerSample, mPFile) != mBytesPerSample) {
					throw exception("WAV-File reading was not possible");
				}
				//For left Channel we create a Sample.
				mChannelData.back().push_back(new Sample(dataBuff, mBytesPerSample));
			}

		}
		free(dataBuff); // Freeing the buffer once we stopped using it.
	}
	catch (exception& ex) {
		cout << ex.what();
	}
}

void AudioManager::OpenFile(const char* dyn_path) {
	mPFile = fopen(dyn_path, "rb");  //Must explicitly tell that is a binary file.

	if (!mPFile) {
		throw ioexception();
	}
}

void AudioManager::CloseFile() {
	if (fclose(mPFile) == EOF) {
		throw ioexception();
	}
}

void AudioManager::MP3Manager()
{
	//TODO
}

const char* unsupportedexception::what()const noexcept {
	return "unsupported file type";
}

const char* ioexception::what()const noexcept {
	return "input/output exception occurred";
}

const void WAV_Header::out() {
	cout << "RIFF: " << RIFF << "\n";
	cout << "ChunkSize: " << ChunkSize << "\n";
	cout << "WAVE: " << WAVE << "\n";
	cout << "fmt: " << fmt << "\n";
	cout << "Subchunk1Size: " << Subchunk1Size << "\n";
	cout << "AudioFormat: " << AudioFormat << "\n";
	cout << "NumOfChan: " << NumOfChan << "\n";
	cout << "SamplesPerSec: " << SamplesPerSec << "\n";
	cout << "bytesPerSec: " << bytesPerSec << "\n";
	cout << "blockAlign: " << blockAlign << "\n";
	cout << "bitsPerSample: " << bitsPerSample << "\n";
	cout << "Subchunk2ID:" << Subchunk2ID << "\n";
	cout << "SubChunk2Size:" << Subchunk2Size << "\n";
}