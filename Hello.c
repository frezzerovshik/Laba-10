#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	static char text[1000000];
	char c;
	int i = 0;
	int end, start;
	int counter = 0;
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
	while (!feof(fpin))
	{
		c = fgetc(fpin);
		if (c == '\n');
		else
		{
			text[i] = c;
			i++;
			if (c == '.')
				text[i++] = '\0';
		}
	}
	counter = i;
	start = 0;
	end = 0;
	for (i = 0; i <= counter; i++)
	{
		if (text[i] == '.' || text[i] == '!' || text[i] == '?' || text[i] == '\0')
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
				tmp = (char*)malloc((end - start) * sizeof(char));
				buf = tmp;
				for (k = start; k <= end; k++)
				{
					*tmp = text[k];
					++tmp;
				}
				fputs(buf, fpout);
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