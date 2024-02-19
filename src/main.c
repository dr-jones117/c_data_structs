#include "mish.h"
#include <signal.h>

void ctrlCHandler() {
    exit(0);
}

int main(int argc, char** argv) {
    // if a ctrl-c is pressed, exit the program
    signal(SIGINT, ctrlCHandler);

    if(argc == 1) {
        runInteractiveMode();
    }
    else if(argc == 2) {
        runScriptMode(argv[1]);
    }
    else { 
        printUsageStatement();
        exit(EXIT_FAILURE);
    }

    return 0;
}

