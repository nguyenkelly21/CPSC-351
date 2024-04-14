#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>

#define MAX_STR_LEN 100
#define MAX_STRINGS 100

void searchSection(char **strings, int startIdx, int endIdx, char *target, int *result) 
{
    for (int i = startIdx; i < endIdx; i++) 
    {
        int len = strlen(strings[i]);
        while (len > 0 && isspace(strings[i][len - 1])) 
        {
            strings[i][len - 1] = '\0';
            len--;
        }
        if (strcmp(strings[i], target) == 0) 
        {
            *result = 1;
            exit(0);
        }
    }
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) 
    {
    //error check for argument 
        printf("Usage: %s <filename> <target_string> <num_processes>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *target = argv[2];
    int numProcesses = atoi(argv[3]);

    FILE *file = fopen(filename, "r"); //open file
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char **strings = (char **)malloc(sizeof(char *) * MAX_STRINGS);
    if (strings == NULL) 
    {
	    perror("Memory allocation failed");
	    return 1;
    }

    int numStrings = 0;
    char buffer[MAX_STR_LEN]; //buffer for storing each line that is read from file

    while (fgets(buffer, MAX_STR_LEN, file) != NULL) //read line from file using fgets into buffer
    {
    	    strings[numStrings] = (char *)malloc(strlen(buffer) + 1); //alloc memory
    	    
	    if (strings[numStrings] == NULL)  //to check if memory alloc failed
	    {
		perror("Memory allocation failed"); 
		return 1;
	    }
	    
	    strcpy(strings[numStrings], buffer); //copy buffer data into memory
    	    numStrings++; // Increment the counter for the next string
	 
	    if (numStrings >= MAX_STRINGS) 
	    {
		break; //stop reading if maximum number of strings reached
	    }
    }

    fclose(file); //close file 

    int sectionSize = numStrings / numProcesses;
    int result = 0;

    for (int i = 0; i < numProcesses; i++) 
    {
        pid_t pid = fork();
        if (pid == -1) 
        {
            perror("Fork failed");
            return 1;
        } 
        else if (pid == 0) 
        { // child process
            int startIdx = i * sectionSize;
	    int endIdx = (i + 1) * sectionSize;
		if (i == numProcesses - 1) 
		{
		    endIdx = numStrings;
		}
		searchSection(strings, startIdx, endIdx, target, &result);
        }
    }

    int exitStatus;
    for (int i = 0; i < numProcesses; i++) 
    {
        if (wait(&exitStatus) < 1) 
        {
            perror("Wait");
            return -1;
        }
        if (WIFEXITED(exitStatus) && WEXITSTATUS(exitStatus) == 0) 
        {
            result = 1;
            break;
        }
    }

    if (result) 
    {
        printf("The target string was found\n");
        //terminate all child processes
        for (int i = 0; i < numProcesses; i++) 
        {
            kill(0, SIGTERM);
        }
    } 
    else 
    {
        printf("The target string was not found\n");
    }

    //free allocated memory
    for (int i = 0; i < numStrings; i++) 
    {
        free(strings[i]);
    }
    free(strings);

    return 0;
}

