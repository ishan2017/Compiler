#include <stdio.h>
#include <stdlib.h>
#include "states.h"

int main(int argc, char *argv[]){
    struct dfa* dfa1 = makeDFA(4);
    printCurr(dfa1);
    addTrans(dfa1, 0, 1, 3);
    transition(dfa1, 3);
    printCurr(dfa1);
    makeFinal(dfa1, 1);
    printCurr(dfa1);
}