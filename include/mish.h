#pragma once
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

extern char** environ;

void runInteractiveMode();

void runScriptMode(char* filename);

void printUsageStatement(); 
