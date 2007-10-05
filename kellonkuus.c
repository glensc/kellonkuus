#include <stdio.h>
#include <time.h>

#include <windows.h>
//#include <mmsystem.h>

//#if defined(__GNUC__) && defined(__cplusplus) && defined(UNICODE)

#if defined(UNICODE)
#define T(a) L ## a
#else
#define T(a) a
#endif

#define	WAVE T("\\Storage Card\\My Documents\\critical.wav")

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

	SYSTEMTIME st;
	GetLocalTime(&st);
	printf("kell on %d %d\n", st.wHour, st.wMinute);

	TCHAR cwd[MAX_PATH];
	DWORD res = GetCurrentDirectory(sizeof(cwd), cwd);
	if (res == 0) {
		printf("GetCurrentDirectory failed (%lu)\n", GetLastError());
		return 1;
	}
	if (res > MAX_PATH) {
		printf("GetCurrentDirectory failed (buffer too small; need %lu chars)\n", res);
		return 1;
	}
	cwd[res] = '\0';
	printf("cwd: %s\n", cwd);

//	BOOL res;
//	res = PlaySound(WAVE, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
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
