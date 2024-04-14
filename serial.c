#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LOCATIONS 100

void fetch_weather_serial(char *filename);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <locations_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    fetch_weather_serial(filename);

    return 0;
}

void fetch_weather_serial(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char latitude[20], longitude[20];

    while (fscanf(file, "%s %s", latitude, longitude) == 2) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            execlp("/usr/bin/curl", "curl", "-o", "weather.json", 
                   "https://api.open-meteo.com/v1/forecast?latitude=52.520000&longitude=13.410000&current_weather=True", 
                   latitude, longitude, NULL);
            perror("Error executing execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL); // Wait for child to finish
        }
    }

    fclose(file);
}
