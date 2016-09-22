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
	//���̷�Ʈ �� ���� ������
	IGraphBuilder *pGraph;//�׷��� �Ŵ��� ������
	IMediaControl *pMediaControl;//�̵�� ��Ʈ�� ������
	IMediaEventEx  *m_pMediaEvent;//�̵�� �̺�Ʈ ������
	IMediaSeeking  *pMS;//��ġ ���� ������
	IBasicAudio   *pBA;	//���� ���� ���� ������
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