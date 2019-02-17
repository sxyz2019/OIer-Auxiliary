#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <tchar.h>
#include <windows.h>

const int N = 100, LEN = 2000;
char s[LEN], now[LEN], name[LEN], pro[N][LEN], cmd[LEN], defSrc[LEN], src[LEN],
	path[LEN], tmp[LEN];

template <class T> inline void read(T &x)
{
	x = 0;
	char c = getchar();
	bool f = 0;
	for (; !isdigit(c); c = getchar()) f ^= c == '-';
	for (; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	while (c != '\n') c = getchar(); // fixed:数字后字符
	x = f ? -x : x;
}

bool execmd(const char cmd[], char *result)
{
	static const int SIZE = 128;
	char buffer[SIZE];
	FILE *pipe = popen(cmd, "r");
	if (pipe == 0) return false;
	while (!feof(pipe))
		if (fgets(buffer, SIZE, pipe)) strcat(result, buffer);
	int len = strlen(result);
	while (result[len - 1] == '\n') // fixed:修复win10换行符
	{
		--len;
		result[len] = 0;
	}
	pclose(pipe);
	return true;
}

bool checkName(const char name[])
{
	static const int LEN = 50;
	int len = strlen(name);
	if (!len || len > LEN) return false; // fixed:空字符串
	if (name[0] == ' ' || name[len - 1] == ' ')
		return false; // fixed:文件夹名称末尾空格报错 名称开头空格报错
	for (int i = 0; i < len; ++i)
		if (name[i] == '<' || name[i] == '>' || name[i] == '^' || name[i] == '&'
			|| name[i] == '%' || name[i] == '"' || name[i] == '\''
			|| name[i] == '\\' || name[i] == '/' || name[i] == '*'
			|| name[i] == ':' || name[i] == '|' || name[i] == '?'
			|| name[i] == '\t') // fixed:名称tab报错
			return false;
	return true;
}

void catPath(char s[], const char path[])
{
	strcat(s, " \"");
	strcat(s, path);
	strcat(s, "\"");
}

void merge(char s[], const char cmd[], const char path[])
{
	strcpy(s, cmd);
	catPath(s, path);
}

void merge(char s[], const char cmd[], const char path1[], const char path2[])
{
	strcpy(s, cmd);
	catPath(s, path1);
	catPath(s, path2);
}

void getFilePath(char now[], int k, const char ext[])
{
	strcpy(now, src);
	strcat(now, "\\");
	strcat(now, pro[k]);
	strcat(now, "\\");
	strcat(now, pro[k]);
	strcat(now, ext);
}

int main()
{
	int n;
	puts("Input your name:");
	gets(name);
	while (!checkName(name))
	{
		puts("\nError code is 0.\nPlease input again:");
		gets(name);
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
		gets(pro[i]);
		while (!checkName(pro[i]))
		{
			puts("\nError code is 2.\nPlease input again:");
			printf("Problem %d:", i);
			gets(pro[i]);
		}
		putchar('\n');
	}
	system("cls");
	puts("Loading...\n");
	DWORD t1, t2;
	t1 = GetTickCount();
	if (execmd("echo %username%", tmp))
	{
		strcat(src, "C:\\Users\\");
		strcat(src, tmp);
		strcat(src, "\\Desktop\\");
		strcat(src, name);
		merge(now, "md", src);
		system(now);
		strcat(defSrc, "C:\\Users\\");
		strcat(defSrc, tmp);
		strcat(defSrc, "\\Desktop\\OIer Auxiliary\\Default Source.txt");
		for (int i = 1; i <= n; ++i)
		{
			strcpy(tmp, src);
			strcat(tmp, "\\");
			strcat(tmp, pro[i]);
			merge(now, "md", tmp);
			system(now);
		}
		for (int i = 1; i <= n; ++i)
		{
			getFilePath(path, i, ".in");
			merge(now, "type nul > ", path);
			system(now);
		}
		for (int i = 1; i <= n; ++i)
		{
			getFilePath(path, i, ".out");
			merge(now, "type nul > ", path);
			system(now);
		}
		for (int i = 1; i <= n; ++i)
		{
			getFilePath(path, i, ".cpp");
			merge(now, "copy", defSrc, path);
			strcat(now, " > nul");
			system(now);
		}
		for (int i = 1; i <= n; ++i)
		{
			getFilePath(path, i, ".cpp");
			merge(now, "echo. >>", path);
			system(now);
			for (int j = 0; j <= 9; ++j)
			{
				strcpy(cmd, "echo ");
				if (j == 0) strcat(cmd, "/*");
				if (j == 1)
					strcat(cmd, "****************************************");
				if (j == 2) strcat(cmd, "FileOpen:");
				if (j == 3)
					strcat(cmd, "freopen(\""), strcat(cmd, pro[i]),
						strcat(cmd, ".in\", \"r\", stdin);");
				if (j == 4)
					strcat(cmd, "freopen(\""), strcat(cmd, pro[i]),
						strcat(cmd, ".out\", \"w\", stdout);");
				if (j == 5) strcat(cmd, "FileClose:");
				if (j == 6) strcat(cmd, "fclose(\"stdin\");");
				if (j == 7) strcat(cmd, "fclose(\"stdout\");");
				if (j == 8)
					strcat(cmd, "****************************************");
				if (j == 9) strcat(cmd, "*/");
				strcat(cmd, " >>");
				getFilePath(path, i, ".cpp");
				merge(now, cmd, path);
				system(now);
			}
		}
		t2 = GetTickCount();
		printf("Completed.Use time:%.3lfs\n", (t2 - t1) / 1000.0);
		puts("\nDo you want to open the files now?(Y/N)");
		gets(s);
		while (strlen(s) != 1
			   || (s[0] != 'Y' && s[0] != 'N' && s[0] != 'y' && s[0] != 'n'))
		{
			puts("\nError code is 3.\nPlease input again:\n");
			gets(s);
		}
		if (s[0] == 'Y' || s[0] == 'y')
			for (int i = 1; i <= n; ++i)
			{
				getFilePath(path, i, ".cpp");
				ShellExecute(NULL, _T("open"), _T(path), NULL, NULL, SW_SHOW);
			}
		puts("\nThank you for your trust and support.\nPress any key to exit.");
	}
	else
		puts("Error code is 4.");
	system("pause >nul");
	return 0;
}