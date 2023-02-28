#pragma once
#define _ALLOW_RTCc_IN_STL // Adding definition to cancel RTC on filesystem lib
#ifdef _WIN32				//If device is compiled on Windows, then define SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <filesystem>
#include <cstdio>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include "../includes/Sample.h"
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
* 
*  <<<<<< IMPORTANT: due to portability for the platform, instead of using long and short, i'm using uintxx >>>>>>
*/
struct WAV_Header {
			/* RIFF Chunk Descriptor */
	char                RIFF[4];        // RIFF Header (dunno )
	uint32_t			ChunkSize;      // RIFF Chunk Size  
	char                WAVE[4];        // WAVE Header      
			/* "fmt" sub-chunk */
	char                fmt[4];         // FMT header       
	uint32_t			Subchunk1Size;  // Size of the fmt chunk                                
	uint16_t			AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
	uint16_t			NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
	uint32_t			SamplesPerSec;  // Sampling Frequency in Hz                             
	uint32_t			bytesPerSec;    // bytes per second 
	uint16_t			blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
	uint16_t			bitsPerSample;  // Number of bits per sample      
			/* "data" sub-chunk */
	char                Subchunk2ID[4]; // "data"  string   
	uint32_t			Subchunk2Size;  // Sampled data length    
	const void out(); //Prints out the actual value of the whole struct.

};

// Possible Audio types that exist.
enum class AudioType {
	WAV = 0,
	WAVE= WAV,
	MP3,
	NOT_SUPPORTED
};

struct unsupportedexception : public exception {
	const char *what() const noexcept override;
};

struct ioexception : public exception {
	const char* what()const noexcept override;
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
	unsigned int nOfSamplesPerChan,bytesPerSample;
	list<list<Sample*>> channelData;
	FILE* mPFile;
	WAV_Header *wav_hdr;
	// Map with supported audio types that the audio manager can handle.
	const static std::map<path, AudioType> audiotype;
	// Closes the file.
	void CloseFile();
	// Opens the file to have read access.
	void OpenFile(const char *dyn_path);
};