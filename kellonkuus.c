#include <stdio.h>
#include <time.h>

#include <windows.h>
//#include <mmsystem.h>

//#if defined(__GNUC__) && defined(__cplusplus) && defined(UNICODE)

#if defined(UNICODE)
#define T(a) L ## a
#define _s "%ls"
#else
#define T(a) a
#define _s "%s"
#endif

#define	BASEPATH T("\\Storage Card\\My Documents")
/*
 * http://www.rainer-keuchel.de/wince/wince-api-diffs.txt
 */

#ifndef _WIN32_WCE
#undef PlaySound
#define PlaySound(pszSound, hmod, fdwSound) printf("Play "_s"\n", pszSound);
#endif

int main() {
//	time_t t = time(NULL);
//	struct tm tm;
//	int hour = 0, minute = 0;

//	localtime_r(&t, &tm);
//	printf("kell on %d %d\n", tm.tm_hour, tm.tm_min);

//	{
//		HMMIO hmmio;
//		/* Open the file for reading with buffered I/O. Let windows use its default internal buffer */
//		if (!(hmmio = mmioOpen("C:\\WINDOWS\\CHORD.WAV", 0, MMIO_READ|MMIO_ALLOCBUF)))
//		{
//			        printf("An error opening the file!\n");
//		}
//	}
//

	DWORD res;

	// need full path to files under WinCE
#ifdef _WIN32_WCE
	TCHAR *cwd = BASEPATH;
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
	printf("cwd: "_s"\n", cwd);

	SYSTEMTIME st;
	GetLocalTime(&st);
	printf("kell on %d %d\n", st.wHour, st.wMinute);

	TCHAR buf[MAX_PATH * 2];
	strncpy(buf, cwd, res);
	TCHAR *p = buf + res;

	strcpy(p, "\\default.wav");
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	sprintf(p, "\\%d.wav", st.wHour / 10);
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	sprintf(p, "\\%d.wav", st.wHour % 10);
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	sprintf(p, "\\%d.wav", st.wMinute / 10);
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

	sprintf(p, "\\%d.wav", st.wMinute % 10);
	res = PlaySound(buf, NULL, SND_FILENAME | SND_NODEFAULT);

//	BOOL res;
//	res = PlaySound(WAVE, NULL, SND_FILENAME | SND_NODEFAULT);
//	char buf[128];
//   	sprintf(buf, L"retval: %s", res);

	/*
#if defined(UNICODE)
	MessageBox(NULL, T("Kell on kuus, tagurpidi Ã¼heksa :)"), T("Kell"), MB_OK | MB_ICONINFORMATION);
#else
	MessageBox(NULL, T("Kell on kuus, tagurpidi üheksa :)"), T("Kell"), MB_OK | MB_ICONINFORMATION);
#endif
*/

	return 0;
}
