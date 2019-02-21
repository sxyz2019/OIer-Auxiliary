#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <io.h>
#include <fstream>
#include <shlobj.h>
#include <tchar.h>
#include <windows.h>
using namespace std;
typedef long long LL;

const int LEN = 2000, MAX = 1e8;

int len, cnt, T, num;
char now[LEN], cmd[4][LEN];
string res, pro1, pro2, s1, s2, name1, name2, gen, fc;

template <class T> inline void read(T &x)
{
	x = 0;
	TCHAR c = _gettchar();
	bool f = 0;
	for (; !_istdigit(c); c = _gettchar()) f ^= c == '-';
	for (; _istdigit(c); c = _gettchar()) {
		x = (x << 3) + (x << 1) + (c ^ 48);
		if (x > MAX) {
			puts("Error code is 2.");
    		puts("\nThank you for your trust and support.\nPress any key to exit.");
			_tsystem(_T("pause >nul"));
    		exit(0);
		}
	}
	while (c != '\n') c = _gettchar();
	x = f ? -x : x;
}

/*
path: 指定目录
files: 保存结果
fileType: 指定的文件格式，如 .jpg
*/
void getAllFiles(string path, vector<string>& files,string fileType) 
{
    // 文件句柄
    long hFile = 0;
    // 文件信息
    struct _finddata_t fileinfo;  
 
    string p;
 
    if ((hFile = _findfirst(p.assign(path).append("\\*" + fileType).c_str(), &fileinfo)) != -1) {
        do {
            // 保存文件的全路径
            files.push_back(p.assign(fileinfo.name));
 
           } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
 
        _findclose(hFile);
    }
}

void success()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	puts("Matching success\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void failed()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
    puts("Matching failure\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    SetConsoleTitle("Right-Beat(自动对拍程序)");
	strcat(now, _pgmptr);
	len = strlen(now);
	while (now[--len] != '\\') now[len] = ' ';
	now[len] = '\0';
	for (int i = 0; i < len; ++i) res += now[i];
	//res = '\"' + res + '\"';
    vector <string> pro;
    getAllFiles(res, pro, ".exe");
    if (pro.size() != 4)
	{
    	puts("Error code is 0.");
    	puts("\nThank you for your trust and support.\nPress any key to exit.");
		_tsystem(_T("pause >nul"));
    	return 0;
	}
	bool flag = 0;
    for (int i = 0; i < pro.size(); ++i)
    	if (pro[i] == "datamaker.exe") flag = 1;
	if (!flag) {
		puts("Error code is 1.");
    	puts("\nThank you for your trust and support.\nPress any key to exit.");
		_tsystem(_T("pause >nul"));
    	return 0;
	}
	for (int i = 0; i < 4; ++i)
	{
		if (pro[i] == "Right-Beat.exe") continue;
		if (pro[i] == "datamaker.exe") { gen = pro[i]; continue; }
		else if (!cnt) pro1 = pro[i], cnt ^= 1;
		else pro2 = pro[i];
	}
	for (int i = 0; i < pro1.size() && pro1[i] != '.'; ++i)
		name1 += pro1[i];
	s1 = '\"' + name1 + ".exe\"";
	name1 = '\"' + name1 + ".out" + '\"';
	for (int i = 0; i < pro2.size() && pro2[i] != '.'; ++i)
		name2 += pro2[i];
	s2 = '\"' + name2 + ".exe\"";
	name2 = '\"' + name2 + ".out" + '\"';
	pro1 = "\"\"" + pro1 + "\"";
	pro2 = "\"\"" + pro2 + "\"";
//	cout << pro1 << '\n' << pro2 << '\n';
//	cout << s1 << '\n' << s2 << '\n';
	gen += " > testdata.in";
	pro1 += " < testdata.in > " + name1 + '\"';
	pro2 += " < testdata.in > " + name2 + '\"';
//	cout << pro1 << '\n' << pro2 << '\n';
	fc = "fc " + name1 + " " + name2 + " > nul";
	for (int i = 0; i < gen.size(); ++i) cmd[0][i] = gen[i]; cmd[0][gen.size()] = '\0';
	for (int i = 0; i < pro1.size(); ++i) cmd[1][i] = pro1[i]; cmd[1][pro1.size()] = '\0';
	for (int i = 0; i < pro2.size(); ++i) cmd[2][i] = pro2[i]; cmd[2][pro2.size()] = '\0';
	for (int i = 0; i < fc.size(); ++i) cmd[3][i] = fc[i]; cmd[3][fc.size()] = '\0';
//	for (int i = 0; i < 4; ++i)
//		puts(cmd[i]);
	puts("Please enter the number of datas:");
	read(T);
	if (T <= 0) num = -1;
	else num = T;
	system("cls");
	DWORD t1, t2;
	while (1) {
		if (num == 0) break; 
		if (num != -1) {
			printf("data %d:\n", T - num + 1);
			--num;
		}
		t1 = GetTickCount();
		system(cmd[0]);
		t2 = GetTickCount();
		printf("\"datamaker.exe\" running time: %dms\n", t2 - t1);
		system(cmd[1]);
		t1 = GetTickCount();
		cout << s1 << " running time: ";
		printf("%dms\n", t1 - t2);
		system(cmd[2]);
		t2 = GetTickCount();
		cout << s2 << " running time: ";
		printf("%dms\n", t2 - t1);
		if (system(cmd[3])) {
			failed();
			break;
		}
		success();
	}
    puts("\nThank you for your trust and support.\nPress any key to exit.");
	_tsystem(_T("pause >nul"));
	return 0;
}