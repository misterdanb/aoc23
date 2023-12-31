#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char* numbers[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int main()
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("input", "r");
    if (fp == NULL)
        return -1;

    int sum = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        int firstfound = 0, last_found = 0;
        char calib[3] = { 0, };

        int i = 0;
        while (i < len && line[i] != 0)
        {
            if (isdigit(line[i]) && !firstfound)
            {
                calib[0] = line[i];
                firstfound = 1;
            }

            for (int j = 0; j < 10 && !firstfound; j++)
            {
                int thisisthenum = 1;
                for (int k = 0; k < strlen(numbers[j]); k++)
                {
                    if (line[i + k] == 0)
                    {
                        thisisthenum = 0;
                        break;
                    }

                    if (line[i + k] != numbers[j][k])
                    {
                        thisisthenum = 0;
                        break;
                    }
                }

                if (thisisthenum)
                {
                    calib[0] = 0x30 + j;
                    firstfound = 1;
                    break;
                }
            }

            i++;
        }

        i--;

        while (i >= 0)
        {
            if (isdigit(line[i]) && !last_found)
            {
                calib[1] = line[i];
                last_found = 1;
                break;
            }

            for (int j = 0; j < 10 && !last_found; j++)
            {
                int thisisthenum = 1;
                if (i + strlen(numbers[j]) > len)
                {
                    thisisthenum = 0;
                    continue;
                }
                
                for (int k = 0; k < strlen(numbers[j]); k++)
                {
                    if (line[i + k] != numbers[j][k])
                    {
                        thisisthenum = 0;
                        break;
                    }
                }

                if (thisisthenum)
                {
                    calib[1] = 0x30 + j;
                    last_found = 1;
                    break;
                }
            }

            i--;
        }

        sum += atoi(calib);
    }

    fclose(fp);

    if (line)
        free(line);

    printf("%d\n", sum);

    return 0;
}
