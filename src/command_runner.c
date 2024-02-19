#include "mish.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_ARGS 20
#define WRITE 1
#define READ 0
#define PIPE '|' 

void printStrings(char** strs){
    int counter = 0;
    while(*(strs + counter) != NULL) {
        printf("%s\n", *(strs + counter));
        counter++;
    }
}

char* trimWhitespaces(char* str) {
    char* endOfToken = str + strlen(str) - 1;

    while(*endOfToken == ' ' || *endOfToken == '\n') endOfToken--;
    *(endOfToken + 1) = '\0';
    while(*str == ' ') str++; 

    return str;
}


void free2dCharArray(char** arr) {
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}


void runCdCmd(char** args){
    char** temp = args;
    int amtArgs = 0;
    while(*(temp++)) {
        amtArgs++;
    }

    if(amtArgs != 2) {
        printf("Please provide one directory\n");
    }
    else if(chdir(args[1]) == -1) {
        perror("change directory");
    }
}


void runSetEnvCmd(char** args) {
    char* set = strchr(args[0], '=');
    if(set) {
        *(set++) = '\0';
    }
    else {
        printf("Please provide something to set the environment variable\n");
        return;
    }

    char* env = args[0];
    if(setenv(env, set, 1) == -1) {
        perror("environment set");
    }  
}


void executePipedCommands(char* command) {
    // count the amouant of commands 
    // it will always be at least one 
    int numCommands = 1;
    char* pipeStr = strchr(command, PIPE);
    while(pipeStr){
        numCommands++;
        pipeStr = strchr(pipeStr + 1, PIPE);
    }

    // amount of pipes needs to be numCommands - 1
    int pipefd[numCommands - 1][2];
    for(int i = 0; i < numCommands - 1; i++)
    {
        if(pipe(pipefd[i]) == -1) {
            perror("pipe failed");
            exit(EXIT_FAILURE);
        }
    }

    int counter = 0;
    char* saveStr;
    char* choppedStr = strtok_r(command, "|", &saveStr);
    while(choppedStr) {
        bool redirectOutput = false;
        bool redirectInput = false;

        // set the filename and set redirect in/output flags
        char* filename = strchr(choppedStr, '>');
        if(filename) {
            redirectOutput = true;
            *(filename++) = '\0';
            filename = trimWhitespaces(filename);
        }
        else{
            filename = strchr(choppedStr, '<');
            if(filename) {
                redirectInput = true;
                *(filename++) = '\0';
                filename = trimWhitespaces(filename);
            }
        }

        // create arg array here
        char** args = (char**)malloc(sizeof(char*) * MAX_NUM_ARGS);
        if(!args){
            perror("memalloc");
            exit(EXIT_FAILURE);
        }

        // args will be seprated by at least one space
        int i = 0;
        char* saveStrArgs;
        char* arg = strtok_r(choppedStr, " ", &saveStrArgs);
        while(arg){
            char* argCopy = strdup(arg);
            argCopy = trimWhitespaces(argCopy);
            args[i++] = argCopy;
            arg = strtok_r(NULL, " ", &saveStrArgs);
        }
        
        args[i] = NULL;

        if(strcmp(args[0], "cd") == 0) {
            runCdCmd(args);
        }
        else if(strchr(args[0], '=')) {
            runSetEnvCmd(args);
        }
        else {
            // create the child process
            pid_t pid = fork();
            if(pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }
            else if(pid == 0) {
                //child process
                //redirect input to come from last pipe
                if(counter != 0) {
                    dup2(pipefd[counter - 1][READ], STDIN_FILENO);
                    close(pipefd[counter - 1][READ]);
                }
                // redirect output to go to the current pipe
                if(counter != numCommands - 1) {
                    dup2(pipefd[counter][WRITE], STDOUT_FILENO);
                    close(pipefd[counter][WRITE]);
                }

                // redirect output to the file
                if(redirectInput){
                    int file = open(filename, O_RDONLY);
                    if(file == NULL){
                        perror("file error");
                        exit(EXIT_FAILURE);
                    }
                    dup2(file, STDIN_FILENO);
                    close(file);
                }
                // redirect input to the file
                else if(redirectOutput){
                    int file_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

                    if (file_descriptor == -1) {
                        perror("Error opening file");
                        exit(EXIT_FAILURE);
                    }
                    dup2(file_descriptor, STDOUT_FILENO);
                    close(file_descriptor);
                }
                if(strcmp(args[0], "cd") == 0) {
                    runCdCmd(args);
                    exit(0);
                }
                else if(strchr(args[0], '=')) {
                    runSetEnvCmd(args);
                    exit(0);
                }
                else {
                    // execute the command with the environment
                    execvpe(args[0], args, environ);
                    perror("exec");
                    exit(EXIT_FAILURE);
                }
            }
            else {
                // parent process
                // close the read end of last pipe
                if (counter != 0) {
                    close(pipefd[counter - 1][READ]);
                }
                // close the write end of curr pipe
                if (counter != numCommands - 1) {
                    close(pipefd[counter][WRITE]);
                }
            }
        }
        free2dCharArray(args);
        choppedStr = strtok_r(NULL, "|", &saveStr);
        counter++;
    }

    if(numCommands != counter) {
        perror("Incorrect Piping");
    }
    // wait for all of the processes
    for(int i = 0; i < numCommands; i++)
        wait(NULL);
}


void runCommands(char* input) {
    int numCommands = 0;
    if(strcmp(input, "\n") == 0)
        return;

    // separate each command string by & symbols and run them
    char* savePtrOne;
    char* token = strtok_r(input, "&", &savePtrOne);
    while(token) {
        numCommands++;

        char* newStr = strdup(token);
        newStr = trimWhitespaces(newStr);
        if(strcmp(newStr, "") != 0){
            executePipedCommands(newStr);
        }

        token = strtok_r(NULL, "&", &savePtrOne);
    }
}

