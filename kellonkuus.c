/*

  Tell a clock by playing sound waves of hours and minutes.

  Copyright (c) 2007 Elan Ruusamäe <glen@alkohol.ee>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA 02111-1307, USA.
 */

 /*
 * $Id$
 */
#include <windows.h>
#include <tchar.h>

#if defined(UNICODE)
#define _s "%ls"
#else
#define _s "%s"
#endif

#define	BASEPATH TEXT("\\Storage Card\\My Documents")

#ifndef _WIN32_WCE
#undef PlaySound
#define PlaySound(pszSound, hmod, fdwSound) printf("Play "_s"\n", pszSound);
#else
#if DEBUG
#undef PlaySound
#define PlaySound(pszSound, hmod, fdwSound) MessageBox(NULL, pszSound, TEXT("Debug"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
#endif
#endif

int main() {
	DWORD res;

	// need full path to files under WinCE
	// WinCE lacks GetCurrentDirectory()
	// see http://www.rainer-keuchel.de/wince/wince-api-diffs.txt
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
