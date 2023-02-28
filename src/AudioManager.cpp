#include "../includes/AudioManager.h"
const std::map<path,AudioType> AudioManager::audiotype = {
	{path(".wav"),AudioType::WAV},
	{path(".wave"),AudioType::WAVE},
	{path(".mp3"),AudioType::MP3}
};

const char *AudioManager::DIR_NAME = "Songs";

const AudioType AudioManager::GetAudioType(path extension){
	AudioType type;
	try
	{
		type = audiotype.at(extension);
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
	const AudioType type = GetAudioType(p.filename().extension());
	try {
		OpenFile(dyn_path.c_str());
		switch (type)
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
	catch (const exception &ex) {
		cerr << "Error: " << ex.what() << " in AudioManager() for file " << dyn_path;
		
	}
	CloseFile();
}

void AudioManager::WAVManager() {

	size_t headerSize = sizeof(WAV_Header);
	try {
		wav_hdr = (WAV_Header*)malloc(headerSize);
		if (!wav_hdr) {
			throw exception("Could not allocate more memory");
		}
		if (fread(wav_hdr, 1, headerSize, mPFile) != headerSize) {
			throw exception("WAV-File reading was not possible");
		}
		bytesPerSample = wav_hdr->bitsPerSample / 8;
		// NºSamples = dataSize / (NºOfChannels * bytesPerSample).
		nOfSamplesPerChan = wav_hdr->Subchunk2Size / (wav_hdr->NumOfChan * bytesPerSample);
		for (size_t i = 0; i < wav_hdr->NumOfChan; i++)
		{
			channelData.push_back(list<Sample*>());
		}
		//For each sample
		char* dataBuff = (char*)malloc(sizeof(char) *bytesPerSample);
		if (!dataBuff) {
			throw exception("Could not allocate more memory");
		}
		for (size_t i = 0; i < nOfSamplesPerChan; i++)
		{
			//We read the sample from the wav file.
			if (fread(dataBuff, 1, bytesPerSample, mPFile) != bytesPerSample) {
				throw exception("WAV-File reading was not possible");
			}
			//For right Channel we create a Sample.
			channelData.front().push_back(new Sample(dataBuff, bytesPerSample));
		}
		//If there's another channel, repeat it to store in the left channel.
		if (wav_hdr->NumOfChan > 1) {
			for (size_t i = 0; i < nOfSamplesPerChan; i++)
			{
				//We read the sample from the wav file.
				if (fread(dataBuff, 1, bytesPerSample, mPFile) != bytesPerSample) {
					throw exception("WAV-File reading was not possible");
				}
				//For left Channel we create a Sample.
				channelData.back().push_back(new Sample(dataBuff, bytesPerSample));
			}

		}
		free(dataBuff); // Freeing the buffer once we stopped using it.
	}
	catch (exception& ex) {
		cout << ex.what();
	}
}

void AudioManager::OpenFile(const char *dyn_path) {
	mPFile= fopen(dyn_path, "rb");  //Must explicitly tell that is a binary file.

	if (!mPFile) {
		throw ioexception();
	}
}

void AudioManager::CloseFile(){
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