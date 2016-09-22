#ifndef _VIDEOPLAY_H
#define _VIDEOPLAY_H
#define WIN32_LEAN_AND_MEAN

#include "dshow.h"
#include <strmif.h>
#include <control.h>
#include <uuids.h>

#include "constants.h"

class VideoPlayer {
private : 
	//다이렉트 쇼 관련 변수들
	IGraphBuilder *pGraph;//그래프 매니져 포인터
	IMediaControl *pMediaControl;//미디어 컨트롤 포인터
	IMediaEventEx  *m_pMediaEvent;//미디어 이벤트 포인터
	IMediaSeeking  *pMS;//위치 관련 포인터
	IBasicAudio   *pBA;	//볼륨 조절 관련 포인터
	LONGLONG pos = 0;
	LONG      g_lVolume = VOLUME_FULL;
	BOOL DS_isPlaying = FALSE;

	//OPENFILENAME OFN;
	char  lpstrFile[MAX_PATH] = "";
	WCHAR wFile[MAX_PATH];

public :

	virtual ~VideoPlayer() {
		m_pMediaEvent->Release();
		pMS->Release();
		pBA->Release();
		pMediaControl->Release();
		pGraph->Release();
		CoUninitialize();
	};

	void play();
	//void stop();

};

#endif