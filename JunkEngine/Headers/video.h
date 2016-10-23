#pragma once

#include "game.h"
#include "constants.h"

#include <dshow.h>
#include <Vmr9.h>

#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")

class Video {
public :
	IGraphBuilder *pGraph = NULL;
	IMediaControl *pControl = NULL;
	IMediaEvent   *pEvent = NULL;

	IBaseFilter            *m_pEVR;
	IVMRWindowlessControl	*m_pWindowless;


public :
	~Video() {
		IVideoWindow    *pVidWin = NULL;
		pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin);
		pVidWin->put_Visible(OAFALSE);
		pVidWin->put_Owner(NULL);

		pControl->Release();
		pEvent->Release();
		pGraph->Release();
		CoUninitialize();
	};

	void play(HWND hwnd) {
		// Initialize the COM library.
		CoInitialize(NULL);

		// Create the filter graph manager and query for interfaces.
		CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void **)&pGraph);

		pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
		pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

		IVideoWindow *pVidWindow = NULL;
		pGraph->RenderFile(L"C:\\test.avi", NULL);
		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWindow);

		pVidWindow->put_Owner((OAHWND)hwnd);
		pVidWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
		pVidWindow->SetWindowPosition(0, 0, 1280, 720);
		pVidWindow->put_MessageDrain((OAHWND)hwnd);
		pVidWindow->put_Visible(OATRUE);

		pControl->Run();
		
		long evCode;
		pEvent->WaitForCompletion(INFINITE, &evCode);

		
	}
};