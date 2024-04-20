#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LOCATIONS 100

void fetch_weather_parallel(char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <locations_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];
    fetch_weather_parallel(filename);
    return 0;
}

void fetch_weather_parallel(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    char latitude[20], longitude[20];
    int child_count = 0;
    int i = 1;
    while (fscanf(file, "%s %s", latitude, longitude) == 2) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
           // Child process
            char outputfilename[200];
            sprintf(outputfilename, "file_parallel%d.json", i);
            char url[200];
            sprintf(url, "https://api.open-meteo.com/v1/forecast?latitude=%s&longitude=%s&current_weather=True", latitude, longitude);
            execlp("/usr/bin/curl", "curl", "-o", outputfilename, url, NULL);          
            perror("Error executing execlp");
            exit(EXIT_FAILURE);
        } else {
            child_count++;
            i++;
        }
    }
    while (child_count > 0) {
        wait(NULL);
        child_count--;
    }
}