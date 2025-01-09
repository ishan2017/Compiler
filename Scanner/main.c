#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"

int line = 1;
int putback = 0;
FILE* input;
FILE* output;
FILE* copy;

int main(int argc, char *argv[]){
    input = fopen("./testfiles/4.txt", "r");
    copy = fopen("./testfiles/4.txt", "r");
    output = fopen("./testfiles/output.txt", "w");
    scan();
}