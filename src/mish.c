#include "mish.h"
#include "command_runner.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void runInteractiveMode() {
    char* input;

    input = readline("> ");
    while(strcmp(input, "exit") != 0) {
        runCommands(input);
        input = readline("> ");
    }
}


void runScriptMode(char* filename) {
    FILE* file;
    size_t bufferSize = 0;
    char* line = NULL;

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
/*    int nullfile = open("/dev/null", O_WRONLY | O_CREAT | O_TRUNC );
    if(nullfile == -1) {
        perror("Couldn't open file");
        exit(EXIT_FAILURE);
    }
    dup2(nullfile, STDOUT_FILENO);
*/
    while(getline(&line, &bufferSize, file) != -1){
        runCommands(line);
    }

    fclose(file);
}


void printUsageStatement() {
    printf("Usage: mish [SCRIPT]\n\n"
       "Description:\n"
       "  mish is a simple shell program that operates in either interactive mode or executes a provided shell script.\n\n"
       "Options:\n"
       "  SCRIPT     Optional path to a .sh script to execute non-interactively.\n\n"
       "Usage Examples:\n"
       "  Run mish in interactive mode:\n"
       "    $ mish\n\n"
       "  Execute a shell script non-interactively:\n"
       "    $ mish myscript.sh\n\n");
}
