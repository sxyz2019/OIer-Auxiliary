/**
 * @file OIer-Auxiliary.cpp
 * @author xuxing & mxdh
 * @brief OI助手
 * @version 1.2.0
 * @date 2019-02-21

 * @copyright Copyright (c) 2019 sxyz2019

 * This file is part of OIer-Auxiliary.

 * OIer-Auxiliary is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * OIer-Auxiliary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with OIer-Auxiliary.  If not, see <https://www.gnu.org/licenses/>.
 */
/*
#ifndef UNICODE
#	define UNICODE
#endif
#ifndef _UNICODE
#	define _UNICODE
#endif
*/
#pragma GCC optimize(2)
#include <cstdio>
#include <shlobj.h>
#include <tchar.h>
#include <windows.h>

using std::puts;

const int N = 100, LEN = 2000;
TCHAR s[LEN], now[LEN], name[LEN], pro[N][LEN], cmd[LEN], defSrc[LEN], src[LEN], path[LEN],
	desktop[LEN];
int n;

template <class T> inline void read(T &x)
{
	x = 0;
	TCHAR c = _gettchar();
	bool f = 0;
	for (; !_istdigit(c); c = _gettchar()) f ^= c == '-';
	for (; _istdigit(c); c = _gettchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	while (c != '\n') c = _gettchar(); // fixed:数字后字符
	x = f ? -x : x;
}

bool execmd(const char cmd[], TCHAR *result)
{
	static const int SIZE = 128;
	TCHAR buffer[SIZE];
	FILE *pipe = popen(cmd, "r");
	if (pipe == 0) return false;
	while (!feof(pipe))
		if (_fgetts(buffer, SIZE, pipe)) _tcscat(result, buffer);
	int len = _tcslen(result);
	while (result[len - 1] == '\n') // fixed:修复win10换行符
	{
		--len;
		result[len] = 0;
	}
	pclose(pipe);
	return true;
}

bool isLegal(const char ch)
{
	return ch != '<' && ch != '>' && ch != '^' && ch != '&' && ch != '%' && ch != '"' && ch != '\''
		   && ch != '\\' && ch != '/' && ch != '*' && ch != ':' && ch != '|' && ch != '?'
		   && ch != '\t';
}

bool checkName(const TCHAR name[])
{
	static const int maxLenName = 50;
	int len = _tcslen(name);
	if (!len || len > maxLenName) return false; // fixed:空字符串
	if (name[0] == ' ' || name[len - 1] == ' ') return false;
	for (int i = 0; i < len; ++i)
		if (!isLegal(name[i])) return false;
	return true;
}

void catPath(TCHAR s[], const TCHAR path[])
{
	_tcscat(s, _T(" \""));
	_tcscat(s, path);
	_tcscat(s, _T("\""));
}

void merge(TCHAR s[], const TCHAR cmd[], const TCHAR path[])
{
	_tcscpy(s, cmd);
	catPath(s, path);
}

void merge(TCHAR s[], const TCHAR cmd[], const TCHAR path1[], const TCHAR path2[])
{
	_tcscpy(s, cmd);
	catPath(s, path1);
	catPath(s, path2);
}

void getFilePath(TCHAR now[], int k, const TCHAR ext[])
{
	_tcscpy(now, src);
	_tcscat(now, _T("\\"));
	_tcscat(now, pro[k]);
	_tcscat(now, _T("\\"));
	_tcscat(now, pro[k]);
	_tcscat(now, ext);
}

void getStr(TCHAR s[])
{
	_fgetts(s, LEN, stdin);
	int len = _tcslen(s);
	while (s[len - 1] == '\n') // fixed:修复win10换行符
	{
		--len;
		s[len] = 0;
	}
}

void input()
{
	puts("Input your name:");
	getStr(name);
	while (!checkName(name))
	{
		puts("\nError code is 0.\nPlease input again:");
		getStr(name);
	}
	putchar('\n');
	puts("Input the number of problems:");
	read(n);
	putchar('\n');
	while (n > 50 || n < 1)
	{
		puts("\nError code is 1.\nPlease input again:");
		read(n);
	}
	puts("Input the filename of each problem:");
	for (int i = 1; i <= n; ++i)
	{
		printf("Problem %d:", i);
		getStr(pro[i]);
		while (!checkName(pro[i]))
		{
			puts("\nError code is 2.\nPlease input again:");
			printf("Problem %d:", i);
			getStr(pro[i]);
		}
		putchar('\n');
	}
}
void createFolder()
{
	_tcscpy(src, desktop);
	_tcscat(src, _T("\\"));
	_tcscat(src, name);
	merge(now, _T("md"), src);
	_tsystem(now);
	for (int i = 1; i <= n; ++i)
	{
		_tcscpy(path, src);
		_tcscat(path, _T("\\"));
		_tcscat(path, pro[i]);
		merge(now, _T("md"), path);
		_tsystem(now);
	}
}

void createData()
{
	for (int i = 1; i <= n; ++i)
	{
		getFilePath(path, i, _T(".in"));
		merge(now, _T("type nul > "), path);
		_tsystem(now);
	}
	for (int i = 1; i <= n; ++i)
	{
		getFilePath(path, i, _T(".out"));
		merge(now, _T("type nul > "), path);
		_tsystem(now);
	}
}

void createSource()
{
	for (int i = 1; i <= n; ++i)
	{
		getFilePath(path, i, _T(".cpp"));
		merge(now, _T("copy"), defSrc, path);
		_tcscat(now, _T(" > nul"));
		_tsystem(now);
	}
	for (int i = 1; i <= n; ++i)
	{
		getFilePath(path, i, _T(".cpp"));
		merge(now, _T("echo. >>"), path);
		_tsystem(now);
		for (int j = 0; j <= 9; ++j)
		{
			_tcscpy(cmd, _T("echo "));
			if (j == 0) _tcscat(cmd, _T("/*"));
			if (j == 1) _tcscat(cmd, _T("****************************************"));
			if (j == 2) _tcscat(cmd, _T("FileOpen:"));
			if (j == 3)
				_tcscat(cmd, _T("freopen(\"")), _tcscat(cmd, pro[i]),
					_tcscat(cmd, _T(".in\", \"r\", stdin);"));
			if (j == 4)
				_tcscat(cmd, _T("freopen(\"")), _tcscat(cmd, pro[i]),
					_tcscat(cmd, _T(".out\", \"w\", stdout);"));
			if (j == 5) _tcscat(cmd, _T("FileClose:"));
			if (j == 6) _tcscat(cmd, _T("fclose(stdin);"));
			if (j == 7) _tcscat(cmd, _T("fclose(stdout);"));
			if (j == 8) _tcscat(cmd, _T("****************************************"));
			if (j == 9) _tcscat(cmd, _T("*/"));
			_tcscat(cmd, _T(" >>"));
			getFilePath(path, i, _T(".cpp"));
			merge(now, cmd, path);
			_tsystem(now);
		}
	}
}

void openFiles()
{
	puts("\nDo you want to open the files now?(Y/N)");
	getStr(s);
	while (_tcslen(s) != 1 || (s[0] != 'Y' && s[0] != 'N' && s[0] != 'y' && s[0] != 'n'))
	{
		puts("\nError code is 3.\nPlease input again:\n");
		getStr(s);
	}
	if (s[0] == 'Y' || s[0] == 'y')
		for (int i = 1; i <= n; ++i)
		{
			getFilePath(path, i, _T(".cpp"));
			ShellExecute(NULL, _T("open"), path, NULL, NULL, SW_SHOW);
		}
}

int main()
{
	SetConsoleTitleW(L"OIer-Auxiliary(OIer助手)");
	input();
	_tsystem(_T("cls"));
	puts("Loading...\n");
	DWORD t1, t2;
	t1 = GetTickCount();
	LPITEMIDLIST lp;
	SHGetSpecialFolderLocation(0, CSIDL_DESKTOPDIRECTORY,
							   &lp); // fixed:win10Onedrive桌面显示
	SHGetPathFromIDList(lp, desktop);
	_tcscpy(defSrc, desktop);
	_tcscat(defSrc, _T("\\OIer-Auxiliary\\Default Source.txt"));
	createFolder();
	createData();
	createSource();
	t2 = GetTickCount();
	printf("Completed.Use time:%.3lfs\n", (t2 - t1) / 1000.0);
	openFiles();
	puts("\nThank you for your trust and support.\nPress any key to exit.");
	_tsystem(_T("pause >nul"));
	return 0;
}