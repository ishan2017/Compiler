#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "states.h"
#include "scan.h"

char *getNext(FILE* fp){
    return fgetc(fp);
}

int getChar(int ch){
    if(ch <= 57 && ch >= 48){
        return DIG;
    }
    if(ch == 32){
        return SPC;
    }
    if(ch == 42 || ch == 43 || ch == 45 || ch == 47 || ch == 61){
        return OP;
    }
    if(ch == 10){
        return NLN;
    }
    if(ch == -1){
        return EDOF;
    }
}

void addToken(FILE* output, struct token* tok){
    fprintf(output, tok->print);
}

void scan(FILE* input, FILE* output){
    struct dfa* dfa1 = makeDFA(3);
    addTrans(dfa1, 0, 0, SPC);
    addTrans(dfa1, 0, 0, NLN);
    addTrans(dfa1, 0, 0, EDOF);
    addTrans(dfa1, 0, 1, DIG);
    addTrans(dfa1, 0, 2, OP);
    addTrans(dfa1, 1, 1, DIG);
    addTrans(dfa1, 1, 1, EDOF);
    addTrans(dfa1, 1, 0, SPC);
    addTrans(dfa1, 1, 2, OP);
    addTrans(dfa1, 2, 2, EDOF);
    addTrans(dfa1, 2, 1, DIG);
    addTrans(dfa1, 2, 0, SPC);
    int c;
    while((c = getNext(input)) != EOF){
        int next = getNext(c);
        int curState = getCurr(dfa1);
        transition(dfa1, next);
        int nextState = getCurr(dfa1);
        if(curState != nextState){
            struct token* tok = (struct token*)malloc(sizeof(struct token));
            tok->print = (char *)malloc(20);
            if(curState == 1){
                tok->token = INTEGER;
                strcpy(tok->print, "INTEGER ");
                addToken(output, tok);
            }
            if(curState == 2){
                tok->token = OPERATOR;
                strcpy(tok->print, "OPERATOR ");
                addToken(output, tok);
            }
            free(tok->print);
            free(tok);
        }
    }
}