/**
 * @file Right-Beat.cpp
 * @author xuxing & mxdh
 * @brief 自动对拍程序
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
#pragma GCC optimize(2)
/*
#ifndef UNICODE
#	define UNICODE
#endif
#ifndef _UNICODE
#	define _UNICODE
#endif
*/
#include <cstdio>
#include <cstdlib>
#include <io.h>
#include <iostream>
#include <shlobj.h>
#include <string>
#include <tchar.h>
#include <vector>
#include <windows.h>
using std::exit;
using std::puts;
using std::vector;

typedef long long LL;
#ifdef _UNICODE
#	define tstring wstring
#	define tcout wcout
using std::wcout;
using std::wstring;
#else
#	define tstring string
#	define tcout cout
using std::cout;
using std::string;
#endif

const int LEN = 2000, MAX = 1e8;

int len, cnt, T, num;
TCHAR now[LEN], cmd[4][LEN], tmp[LEN];
tstring res, pro1, pro2, s1, s2, name1, name2, gen, fc;

template <class T> inline void read(T &x)
{
	x = 0;
	TCHAR c = _gettchar();
	bool f = 0;
	for (; !_istdigit(c); c = _gettchar()) f ^= c == '-';
	for (; _istdigit(c); c = _gettchar())
	{
		x = (x << 3) + (x << 1) + (c ^ 48);
		if (x > MAX)
		{
			puts("Error code is 2.");
			puts("\nThank you for your trust and support.\nPress any key to exit.");
			_tsystem(_T("pause >nul"));
			exit(0);
		}
	}
	while (c != '\n') c = _gettchar();
	x = f ? -x : x;
}

/**
 * @brief Find all files
 *
 * @param path 指定目录
 * @param files 保存结果
 * @param fileType 指定的文件格式，如 .jpg
 */
void FindAllFiles(tstring path, vector<tstring> &files, tstring fileType)
{
	// 文件句柄
	intptr_t hFile = 0;
	// 文件信息
	struct _tfinddata_t fileinfo;

	tstring p;

	if ((hFile = _tfindfirst(p.assign(path).append(_T("\\*") + fileType).c_str(), &fileinfo)) != -1)
	{
		do
		{
			// 保存文件的全路径
			files.push_back(p.assign(fileinfo.name));
		} while (_tfindnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1

		_findclose(hFile);
	}
}

void succeed()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
							FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	puts("Matching success\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED
																 | FOREGROUND_GREEN
																 | FOREGROUND_BLUE);
}

void fail()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	puts("Matching failed\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED
																 | FOREGROUND_GREEN
																 | FOREGROUND_BLUE);
}

void GetExecutables()
{
	GetModuleFileName(NULL, tmp, LEN);
	_tcscat(now, tmp);
	len = _tcslen(now);
	while (now[--len] != '\\') now[len] = ' ';
	now[len] = '\0';
	for (int i = 0; i < len; ++i) res += now[i];
	// res = '\"' + res + '\"';
	vector<tstring> pro;
	FindAllFiles(res, pro, _T(".exe"));
	if (pro.size() != 4)
	{
		puts("Error code is 0.");
		puts("\nThank you for your trust and support.\nPress any key to exit.");
		_tsystem(_T("pause >nul"));
		exit(0);
	}
	bool flag = 0;
	for (int i = 0; i < 4; ++i)
		if (pro[i] == _T("datamaker.exe")) flag = 1;
	if (!flag)
	{
		puts("Error code is 1.");
		puts("\nThank you for your trust and support.\nPress any key to exit.");
		_tsystem(_T("pause >nul"));
		exit(0);
	}
	for (int i = 0; i < 4; ++i)
	{
		if (pro[i] == _T("Right-Beat.exe")) continue;
		if (pro[i] == _T("datamaker.exe"))
		{
			gen = pro[i];
			continue;
		}
		else if (!cnt)
			pro1 = pro[i], cnt ^= 1;
		else
			pro2 = pro[i];
	}
}

void GetReady()
{
	for (unsigned i = 0; i < pro1.size() && pro1[i] != '.'; ++i) name1 += pro1[i];
	s1 = _T('\"') + name1 + _T(".exe\"");
	name1 = _T('\"') + name1 + _T(".out") + _T('\"');
	for (unsigned i = 0; i < pro2.size() && pro2[i] != '.'; ++i) name2 += pro2[i];
	s2 = _T('\"') + name2 + _T(".exe\"");
	name2 = _T('\"') + name2 + _T(".out") + _T('\"');
	pro1 = _T("\"\"") + pro1 + _T("\"");
	pro2 = _T("\"\"") + pro2 + _T("\"");
	gen += _T(" > testdata.in");
	pro1 += _T(" < testdata.in > ") + name1 + _T('\"');
	pro2 += _T(" < testdata.in > ") + name2 + _T('\"');
	fc = _T("fc ") + name1 + _T(" ") + name2 + _T(" > nul");
	for (unsigned i = 0; i < gen.size(); ++i) cmd[0][i] = gen[i];
	cmd[0][gen.size()] = _T('\0');
	for (unsigned i = 0; i < pro1.size(); ++i) cmd[1][i] = pro1[i];
	cmd[1][pro1.size()] = _T('\0');
	for (unsigned i = 0; i < pro2.size(); ++i) cmd[2][i] = pro2[i];
	cmd[2][pro2.size()] = _T('\0');
	for (unsigned i = 0; i < fc.size(); ++i) cmd[3][i] = fc[i];
	cmd[3][fc.size()] = _T('\0');
}

void Judge()
{
	puts("Please enter the number of data:"); // data不可数
	read(T);
	if (T <= 0)
		num = -1;
	else
		num = T;
	system("cls");
	DWORD t1, t2;
	while (1)
	{
		if (num == 0) break;
		if (num != -1)
		{
			printf("data %d:\n", T - num + 1);
			--num;
		}
		t1 = GetTickCount();
		_tsystem(cmd[0]);
		t2 = GetTickCount();
		printf("\"datamaker.exe\" running time: %lums\n", t2 - t1);
		_tsystem(cmd[1]);
		t1 = GetTickCount();
		tcout << s1 << " running time: ";
		printf("%lums\n", t1 - t2);
		_tsystem(cmd[2]);
		t2 = GetTickCount();
		tcout << s2 << " running time: ";
		printf("%lums\n", t2 - t1);
		if (_tsystem(cmd[3]))
		{
			fail();
			break;
		}
		succeed();
	}
}

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED
																 | FOREGROUND_GREEN
																 | FOREGROUND_BLUE);
	SetConsoleTitleW(L"Right-Beat(自动对拍程序)");
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size = {8000, 2500};
	SetConsoleScreenBufferSize(handle_out, size);
	GetExecutables();
	GetReady();
	Judge();
	puts("\nThank you for your trust and support.\nPress any key to exit.");
	_tsystem(_T("pause >nul"));
	return 0;
}