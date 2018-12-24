#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	static char text[1000000];//Массив для посимвольного сохранения текста
	char c;//Буфферный символ
	int i = 0;
	int end, start;//начало и конец предложения
	int counter = 0;//Счетчик символов
	FILE *fpin;
	FILE *fpout;
	fpin = fopen("input.txt", "rt");
	if (fpin == NULL)
	{
		printf("Error: input.txt\n");
		return 1;
	}
	if ((fpout = fopen("output.txt", "wt")) == NULL)
	{
		printf("Error: output.txt\n");
		return 1;
	}
	while (!feof(fpin))//Считываем файл посимвольно
	{
		c = fgetc(fpin);
		if (c == '\n');
		else
		{
			text[i] = c;
			i++;
			if (c == '.' || c == '!' || c == '?')
				text[i++] = '\0';
		}
	}
	counter = i;
	start = 0;
	end = 0;
	for (i = 0; i <= counter; i++)
	{
		if (text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == '\0')//Ищем конец предложения
		{
			int k = i;
			do
			{
				end = k;
				k++;
			} while (text[k] == '.' || text[k] == '!' || text[k] == '?' || text[k] == ' ' || text[k] == '\0');
		}
		else
		{
			if (end != 0)
			{

				char *tmp;
				char *buf;
				int k;
				tmp = (char*)malloc((end - start) * sizeof(char));//Динамически выделяем память под строку с предложением
				buf = tmp;
				for (k = start; k <= end; k++)//Записываем предложение в динамическую строку
				{
					*tmp = text[k];
					++tmp;
				}
				fputs(buf, fpout);//Запись в файл
				fputc('\n', fpout);
				start = end;
				end = 0;
			}
			else continue;
		}

	}
	fclose(fpin);
	fclose(fpout);
	printf("Program done, check output.txt\n");
	return 0;
}
