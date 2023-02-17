#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#include <filesystem>
#include <cstdio>
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std::filesystem;
using namespace std;




/*
* <WAVE - FORM> → RIFF('WAVE'
* < FMT - CK >				// FORMAT
* [<FACT - CK>]				// FACT CHUNK
* [<CUE - CK>]				// CUE POINTS
* [<PLAYLIST - CK>]			// PLAYLIST
* [<ASSOC - DATA - LIST>]	// ASSOCIATED DATA LIST
* <WAVE - DATA>)			// WAVE DATA
*/
struct WAV_Header {
			/* RIFF Chunk Descriptor */
	char                RIFF[4];        // RIFF Header (dunno )
	unsigned long       ChunkSize;      // RIFF Chunk Size  
	char                WAVE[4];        // WAVE Header      
			/* "fmt" sub-chunk */
	char                fmt[4];         // FMT header       
	unsigned long       Subchunk1Size;  // Size of the fmt chunk                                
	unsigned short      AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
	unsigned short      NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
	unsigned long       SamplesPerSec;  // Sampling Frequency in Hz                             
	unsigned long       bytesPerSec;    // bytes per second 
	unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
	unsigned short      bitsPerSample;  // Number of bits per sample      
			/* "data" sub-chunk */
	char                Subchunk2ID[4]; // "data"  string   
	unsigned long       Subchunk2Size;  // Sampled data length    

};

// Possible Audio types that exist.
enum class AudioType {
	WAV = 0,
	WAVE= WAV,
	MP3,
	NOT_SUPPORTED
};

struct unsupportedexception : public exception {
	const char* what()const override;
};

struct ioexception : public exception {
	const char* what()const override;
};

class AudioManager {
public:
	// Returns the AudioType from the pathfile.
	// If the file is not supported yet, returns NOT_SUPPORTED.
	static const AudioType GetAudioType(path extension);

	//Directory Name where all the audios will be checked.
	static const char *DIR_NAME;
	AudioManager(path p);
private:
	void WAVManager();
	void MP3Manager();
	double Hz;
	FILE* mPFile;
	WAV_Header *wav_hdr;
	// Map with supported audio types that the audio manager can handle.
	const static std::map<path, AudioType> audiotype;
	// Closes the file.
	void CloseFile();
	// Opens the file to have read access.
	void OpenFile(const char *dyn_path);
};