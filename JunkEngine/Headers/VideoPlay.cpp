#include "VideoPlay.h"

void VideoPlayer::play()
{
	//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpstrFile, -1, wFile, _MAX_PATH);

	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (LPVOID *)&pGraph);

	pGraph->RenderFile(wFile, NULL);
	pGraph->QueryInterface(IID_IMediaControl, (void **)&pMediaControl);
	pGraph->QueryInterface(IID_IMediaEventEx, (void**)&m_pMediaEvent);
	pGraph->QueryInterface(IID_IMediaSeeking, (void **)&pMS);
	pGraph->QueryInterface(IID_IBasicAudio, (void **)&pBA);
	pMediaControl->Run();
}
