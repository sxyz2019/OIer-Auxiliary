#pragma comment(lib, "shell32.lib")
#include <cstdio>
#include <shlobj.h>
#include <windows.h>

int main()
{
	LPITEMIDLIST lp;
	SHGetSpecialFolderLocation(0, CSIDL_DESKTOPDIRECTORY, &lp);
	char lstr[100];
	SHGetPathFromIDList(lp, lstr);
	puts(lstr);
	return 0;
}
