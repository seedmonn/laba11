#define _CRT_SECURE_NO_WARNINGS
#define YES 1
#define NO 0
#define MAXLEN 1000
#include <stdio.h>
#include <string.h>
#include <windows.h>
int main(int argc, char* argv[])
{
	HANDLE hStdout;
	char line[MAXLEN];
	char filename[MAXLEN] = {0};
	int i = 0;
	int flag1, flag2, flag3;
	flag1 = flag2 = flag3 = 0;
	char* ptr;
	char* buf;
	FILE* fp;
	if (argc == 2)
		strcpy(filename, argv[1]);
	else 
	{
		printf("Please enter a file address: ");
		gets(filename);
	}
	if ((fp = fopen(filename, "r")) == NULL) //Открытие файла для чтения
	{
		printf("Cannot open input file.\n");
		return 1;
	}
	WORD foregroundColor0;
	WORD foregroundColor;
	WORD textAttribute;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	foregroundColor0 = FOREGROUND_INTENSITY | FOREGROUND_BLUE | SetConsoleTextAttribute(hStdout, foregroundColor0);
	while (!feof(fp))
	{
		ptr = fgets(line, MAXLEN, fp);
		buf = line;
		while (*buf != '\0')
		{
			if (*buf == '(')
				flag1 = YES;
			if ((*buf == ')') && (*++buf == ';'))
				flag2 = YES;
			*buf++;
		}
		if (flag1 == YES && flag2 == YES && flag3 == NO)//Если все флаги в правильном положении - подсвечиваем строку
		{
			textAttribute = foregroundColor0;
			SetConsoleTextAttribute(hStdout, textAttribute);
			printf("%s", line);
		}
		else//иначе - выводим стандартно
		{
			SetConsoleTextAttribute(hStdout, 7);
			printf("%s", line);
		}
		/*Обнуляем флаги и счетчики*/
		i = 0;
		flag1 = flag2 = flag3 = NO;
	}
	/*Восстанавливаем стандартные параметры консоли*/
	SetConsoleTextAttribute(hStdout, 7);
	fclose(fp);//Закрываем файл
	getchar();
	return 0;
}