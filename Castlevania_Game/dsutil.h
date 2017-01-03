#pragma once

// Copied and edited from many sources.
// Works on Visual Studio 2015.
// Please do not care about this shit.

#include "dxerr.h"
#include <dsound.h>

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

//-----------------------------------------------------------------------------
// Miscellaneous helper functions
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

//-----------------------------------------------------------------------------
// Classes used by this header
//-----------------------------------------------------------------------------
class CSoundManager;
class CSound;
class CWaveFile;

//-----------------------------------------------------------------------------
// Typing macros 
//-----------------------------------------------------------------------------
#define WAVEFILE_READ   1
#define WAVEFILE_WRITE  2

//-----------------------------------------------------------------------------
// Name: class CSoundManager.
// Desc: 
//-----------------------------------------------------------------------------
class CSoundManager
{
protected:
	LPDIRECTSOUND8 m_pDS;

public:
	CSoundManager();
	~CSoundManager();

	HRESULT Initialize(HWND hWnd, DWORD dwCoopLevel);
	HRESULT SetPrimaryBufferFormat(DWORD dwPrimaryChannels, DWORD dwPrimaryFreq, DWORD dwPrimaryBitRate);

	HRESULT Create(CSound** ppSound, LPTSTR strWaveFileName, DWORD dwCreationFlags = 0, GUID guid3DAlgorithm = GUID_NULL, DWORD dwNumBuffers = 1);
};

//-----------------------------------------------------------------------------
// Name: class CSound.
// Desc: Encapsulates functionality of a DirectSound buffer..
//-----------------------------------------------------------------------------
class CSound
{
protected:
	LPDIRECTSOUNDBUFFER* m_apDSBuffer;
	DWORD                m_dwDSBufferSize;
	CWaveFile*           m_pWaveFile;
	DWORD                m_dwNumBuffers;
	DWORD                m_dwCreationFlags;

	HRESULT RestoreBuffer(LPDIRECTSOUNDBUFFER pDSB, BOOL* pbWasRestored);

public:
	CSound(LPDIRECTSOUNDBUFFER* apDSBuffer, DWORD dwDSBufferSize, DWORD dwNumBuffers, CWaveFile* pWaveFile, DWORD dwCreationFlags);
	virtual ~CSound();

	HRESULT FillBufferWithSound(LPDIRECTSOUNDBUFFER pDSB, BOOL bRepeatWavIfBufferLarger);
	LPDIRECTSOUNDBUFFER GetFreeBuffer();

	HRESULT Play(DWORD dwPriority = 0, DWORD dwFlags = 0, LONG lVolume = 0, LONG lFrequency = -1, LONG lPan = 0);
	HRESULT Play(LONG lVolume, LONG lFrequency);
	HRESULT Stop();
	HRESULT Reset();
};

//-----------------------------------------------------------------------------
// Name: class CWaveFile.
// Desc: Encapsulates reading or writing sound data to or from a wave file.
//-----------------------------------------------------------------------------
class CWaveFile
{
public:
	WAVEFORMATEX* m_pwfx;        // Pointer to WAVEFORMATEX structure
	HMMIO         m_hmmio;       // MM I/O handle for the WAVE
	MMCKINFO      m_ck;          // Multimedia RIFF chunk
	MMCKINFO      m_ckRiff;      // Use in opening a WAVE file
	DWORD         m_dwSize;      // The size of the wave file
	MMIOINFO      m_mmioinfoOut;
	DWORD         m_dwFlags;
	BOOL          m_bIsReadingFromMemory;
	BYTE*         m_pbData;
	BYTE*         m_pbDataCur;
	ULONG         m_ulDataSize;
	CHAR*         m_pResourceBuffer;

protected:
	HRESULT ReadMMIO();
	HRESULT WriteMMIO(WAVEFORMATEX *pwfxDest);

public:
	CWaveFile();
	~CWaveFile();

	HRESULT Open(LPTSTR strFileName, WAVEFORMATEX* pwfx, DWORD dwFlags);
	HRESULT Close();

	HRESULT Read(BYTE* pBuffer, DWORD dwSizeToRead, DWORD* pdwSizeRead);
	HRESULT Write(UINT nSizeToWrite, BYTE* pbData, UINT* pnSizeWrote);

	DWORD   GetSize();
	HRESULT ResetFile();
};