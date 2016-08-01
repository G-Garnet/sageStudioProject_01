#ifndef _SOUNDS_H               
#define _SOUNDS_H               
#define WIN32_LEAN_AND_MEAN

#include <xact3.h>
#include "constants.h"

class Junk2DSound
{
	// properties
private:
	IXACT3Engine* xactEngine;   // 
	IXACT3WaveBank* waveBank;   //
	IXACT3SoundBank* soundBank; //
	XACTINDEX cueI;             // 
	void* mapWaveBank;          // 
	void* soundBankData;
	bool coInitialized;         // 

public:
	Junk2DSound();
	virtual ~Junk2DSound();

	// ¸â¹ö ÇÔ¼öµé
	HRESULT initialize();
	void run();
	void playCue(const char cue[]);
	void stopCue(const char cue[]);
};

#endif
