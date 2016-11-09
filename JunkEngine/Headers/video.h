#pragma once

#include "game.h"
#include "constants.h"

#include <dshow.h>
#include <Vmr9.h>

#ifndef CHECK_HR
#define CHECK_HR(hr) if (FAILED(hr)) { goto done; }
#endif

#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")

extern HWND hwnd;

class Video {
public :

	IGraphBuilder *pGraph = NULL;
	IMediaControl *pControl = NULL;
	IMediaEvent   *pEvent = NULL;

	IBaseFilter            *m_pEVR;
	IVMRWindowlessControl	*m_pWindowless;
	IVideoWindow    *pVidWin = NULL;
	IMediaSeeking	*m_pSeek;
	IFullScreenVideoEx *pVidWinF = NULL;


public :
	~Video() {
		pGraph->QueryInterface(IID_IVideoWindow, (void **)&pVidWin);
		pVidWin->put_Visible(OAFALSE);
		pVidWin->put_Owner(NULL);
		pVidWinF->Release();

		pControl->Release();
		pEvent->Release();
		pGraph->Release();
		CoUninitialize();
		SAFE_RELEASE(m_pWindowless);
	};

	HRESULT AddFilterByCLSID(
		IGraphBuilder *pGraph,          // Pointer to the Filter Graph Manager.
		const GUID& clsid,              // CLSID of the filter to create.
		IBaseFilter **ppF,              // Receives a pointer to the filter.
		LPCWSTR wszName = NULL          // A name for the filter (can be NULL).
	)
	{
		if (!pGraph || !ppF)
		{
			return E_POINTER;
		}

		*ppF = 0;

		IBaseFilter *pFilter = NULL;
		HRESULT hr = S_OK;

		CHECK_HR(hr = CoCreateInstance(
			clsid,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IBaseFilter,
			(void**)&pFilter));

		CHECK_HR(hr = pGraph->AddFilter(pFilter, wszName));

		*ppF = pFilter;
		(*ppF)->AddRef();

	done:
		SAFE_RELEASE(pFilter);
		return hr;
	}


	HRESULT InitWindowlessVMR(
		IBaseFilter *pVMR,				// Pointer to the VMR
		HWND hwnd,						// Clipping window
		IVMRWindowlessControl** ppWC	// Receives a pointer to the VMR.
	)
	{

		IVMRFilterConfig* pConfig = NULL;
		IVMRWindowlessControl *pWC = NULL;

		HRESULT hr = S_OK;

		// Set the rendering mode.  
		hr = pVMR->QueryInterface(IID_IVMRFilterConfig, (void**)&pConfig);
		if (SUCCEEDED(hr))
		{
			hr = pConfig->SetRenderingMode(VMRMode_Windowless);
		}

		// Query for the windowless control interface.
		if (SUCCEEDED(hr))
		{
			hr = pVMR->QueryInterface(IID_IVMRWindowlessControl, (void**)&pWC);
		}

		// Set the clipping window.
		if (SUCCEEDED(hr))
		{
			hr = pWC->SetVideoClippingWindow(hwnd);
		}

		// Preserve aspect ratio by letter-boxing
		if (SUCCEEDED(hr))
		{
			hr = pWC->SetAspectRatioMode(VMR_ARMODE_LETTER_BOX);
		}

		// Return the IVMRWindowlessControl pointer to the caller.
		if (SUCCEEDED(hr))
		{
			*ppWC = pWC;
			(*ppWC)->AddRef();
		}

		SAFE_RELEASE(pConfig);
		SAFE_RELEASE(pWC);

		return hr;
	}

	void play(HWND hwnd_, LPCWSTR file) {
		IBaseFilter *pVMR = NULL;
		IBaseFilter *pFilter = NULL;

		// Initialize the COM library.
		CoInitialize(NULL);

		// Create the filter graph manager and query for interfaces.
		CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void **)&pGraph);

		AddFilterByCLSID(pGraph, CLSID_VideoMixingRenderer, &pVMR, L"VMR-7");
		InitWindowlessVMR(pVMR, hwnd, &m_pWindowless);
		m_pWindowless->QueryInterface(__uuidof(IBaseFilter), (void**)&pFilter);
		pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
		pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
		pGraph->QueryInterface(IID_IMediaSeeking, (void**)&m_pSeek);

		RECT rc;
		GetClientRect(hwnd, &rc);
		m_pWindowless->SetVideoPosition(NULL, &rc);
		m_pWindowless->DisplayModeChanged();

		pGraph->RenderFile(file, NULL);
		pGraph->QueryInterface(IID_IVideoWindow, (void**)&pVidWin);

		//pVidWinF->SetEnabled(OATRUE);

		pVidWin->put_Owner((OAHWND)hwnd);
		pVidWin->put_AutoShow(OAFALSE);
		pVidWin->put_WindowStyle(WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		pVidWin->SetWindowPosition(rc.left, rc.top, rc.right - rc.left + 1, rc.bottom - rc.top + 1);
		pVidWin->put_MessageDrain((OAHWND)hwnd);
		pVidWin->put_FullScreenMode(OATRUE);

		pVidWin->SetWindowForeground(0);
		pVidWin->put_Visible(OATRUE);

		pControl->Run();

		
		
		long evCode;
		pEvent->WaitForCompletion(INFINITE, &evCode);

		pVidWin->put_FullScreenMode(OAFALSE);
		
	}
};

