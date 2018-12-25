#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	static char text[1000000];// Массив для хранения текста
	char c;//Буфферный символ
	int i = 0;//Индекс
	int end, start;//Начало и конец предложения
	int counter = 0;//Счетчик символов в тексте
	FILE *fpin;
	FILE *fpout;
	int num = 1;//Нумерация предложений
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
	while (!feof(fpin))//Чтение из файла
	{
		c = fgetc(fpin);
		if (c == '\n');
		else
		{
			text[i] = c;
			i++;
			if (c == '.' || c == '!' || c == '?')
				text[i++] = '\0';//Инициализация концов строк
		}
	}
	//Инициализация переменных
	counter = i;
	start = 0;
	end = 0;
	for (i = 0; i <= counter; i++)//Анализ последовательности символов
	{
		if (text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == '\0')//Встречен признак конца предложения
		{
			int k = i;
			do
			{
				end = k;
				k++;
			} while (text[k] == '.' || text[k] == '!' || text[k] == '?' || text[k] == ' ' || text[k] == '\0');//Ищем последний разделитель
		}
		else
		{
			if (end != 0)//Конец предложения найден
			{

				char *tmp;
				char *buf;
				int k;
				tmp = (char*)malloc((end - start) * sizeof(char));//Динамически выделяем память для хранения строки с предложением
				buf = tmp;
				for (k = start; k <= end; k++)
				{
					if (k == start && text[k] == ' ')//Удаление пробела между предложениями
					{
						continue;
					}
					*tmp = text[k];
					++tmp;
				}
				//Оформление записи в выходной файл
				fprintf(fpout,"%d. " , num);
				fputs(buf, fpout);
				fputc('\n', fpout);
				start = end;
				end = 0;
				num++;
			}
			else continue;
		}
	}
	fclose(fpin);
	fclose(fpout);
	printf("Program done, check output.txt\n");
	return 0;
}
