#include <stdio.h>
#include <time.h>

#include <windows.h>
#include <tchar.h>

//#include <mmsystem.h>

//#if defined(__GNUC__) && defined(__cplusplus) && defined(UNICODE)

#if defined(UNICODE)
#define _s "%ls"
#else
#define _s "%s"
#endif

#define	BASEPATH TEXT("\\Storage Card\\My Documents")
/*
 * http://www.rainer-keuchel.de/wince/wince-api-diffs.txt
 */

#ifndef _WIN32_WCE
#undef PlaySound
#define PlaySound(pszSound, hmod, fdwSound) printf("Play "_s"\n", pszSound);
//#else
//#undef PlaySound
//#define PlaySound(pszSound, hmod, fdwSound) MessageBox(NULL, pszSound, TEXT("Debug"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
#endif

int main() {
	DWORD res;

	// need full path to files under WinCE
#ifdef _WIN32_WCE
	TCHAR *cwd = BASEPATH;
	res = _tcslen(cwd);
#else
	TCHAR cwd[MAX_PATH];
	res = GetCurrentDirectory(sizeof(cwd), cwd);
	if (res == 0) {
		printf("GetCurrentDirectory failed (%lu)\n", GetLastError());
		return 1;
	}
	if (res > sizeof(cwd)) {
		printf("GetCurrentDirectory failed (buffer too small; need %lu chars)\n", res);
		return 1;
	}
#endif

	SYSTEMTIME st;
	GetLocalTime(&st);

	TCHAR buf[MAX_PATH * 2];
	_tcsncpy(buf, cwd, res);

	TCHAR *p = buf + res;

	_tcscpy(p, TEXT("\\default.wav"));
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	_stprintf(p, TEXT("\\%d.wav"), st.wHour);
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	_stprintf(p, TEXT("\\%02d.wav"), st.wMinute);
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	return 0;
}
