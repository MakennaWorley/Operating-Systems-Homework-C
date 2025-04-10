/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

// function prototypes

int parse_command(char command[], char *args[]);

#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
	int should_run = 1;
	int command_length;

	char command[MAX_LINE];
	char last_command[MAX_LINE] = "";

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

		fgets(command, MAX_LINE, stdin);

		if (strcmp(command, "!!\n") == 0)
        {
            if (strlen(last_command) == 0)
            {
                printf("No command history found.\n");
                continue;
            }
            strcpy(command, last_command);
        }
        else
        {
            strcpy(last_command, command);
        }

		command_length = parse_command(command, args);
		args[command_length] = NULL;

        for (int i = 0; i < command_length; i++)
		{
			printf("[%d] [%s]\n", i, args[i]);
		}

		if (command_length == 0)
		{
			continue;
		}

		if (strcmp(args[0], "exit") == 0)
        {
            should_run = 0;
            continue;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            printf("Fork failed.\n");
            continue;
        }
        else if (pid == 0)
        {
            // Child process
            if (execvp(args[0], args) == -1)
            {
                printf("Command not found\n");
                exit(1);
            }
        }
        else
        {
            // Parent process
            wait(NULL);
        }
    }

	return 0;
}

/**
 * Parses the command and places each token
 * into args array.
 */
int parse_command(char command[], char *args[])
{
	char *spart = strtok(command, " \n");
	int length = 0;

	while (spart != NULL)
	{
		args[length] = spart;
		length++;
		spart = strtok(NULL, " \n");
	}

	return length;
}
