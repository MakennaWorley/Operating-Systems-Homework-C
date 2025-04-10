/**
 * A simple C program that prompts the user
 * for a line of text.
 *
 * @author Makenna Worley
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LEN  = 256;

void getPhrase(char phrase[])
{
	printf("Enter a phrase : ");

	fgets(phrase, LEN, stdin);
}

void reportPhrase(char phrase[]) 
{
	int i = 0;
	int vowelCount[5] = {0};

	for(i = 0; i < strlen(phrase); i++)
	{
		if (phrase[i] == 'A' || phrase[i] == 'a') vowelCount[0]++;
		else if (phrase[i] == 'E' || phrase[i] == 'e') vowelCount[1]++;
		else if (phrase[i] == 'I' || phrase[i] == 'i') vowelCount[2]++;
		else if (phrase[i] == 'O' || phrase[i] == 'o') vowelCount[3]++;
		else if (phrase[i] == 'U' || phrase[i] == 'u') vowelCount[4]++;
	}

	printf("\nVowel Histogram:\n");
	char vowelLabels[] = {'a', 'e', 'i', 'o', 'u'};

	for (i = 0; i < 5; i++)
	{
		printf("%c: ", vowelLabels[i]);

		for (int j = 0; j < vowelCount[i]; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}


int main(int argc, char *argv[])
{
	char phrase[LEN];

	getPhrase(phrase);

	reportPhrase(phrase);
}
