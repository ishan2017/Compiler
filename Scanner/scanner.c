#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "states.h"
#include "scan.h"

int getNext(FILE* fp){
    int c;
    if (putback){
        c = putback;
        putback = 0;
        return c;
    }
    c = fgetc(fp);
    return c;
}

int skip(FILE *fp){
    int c = getNext(fp);
    while(' ' == c || '\n' == c || '\f' == c || '\r' == c || '\t' == c){
        c = getNext(fp);
    }
    return c;
}

int getChar(int ch){
    if(ch <= '9' && ch >= '0'){
        return DIG;
    }
    if(ch == 42 || ch == 43 || ch == 45 || ch == 47 || ch == 61){
        return OP;
    }
    if(ch <= 'Z' && ch >= 'A' || ch <= 'z' && ch >= 'a'){
        return LET;
    }
    switch(ch){
        case ' ':
            return SPC;
        case '\n':
            return NLN;
        case -1:
            return EDOF;
        case '_':
            return UNDER;
        case '.':
            return DOT;
        case 39:
            return QT;
        case '"':
            return DQ;
        case 92:
            return BS;
    }
    return OTHR;
}

void addToken(FILE* output, struct token* tok){
    fprintf(output, tok->print);
}

void scanIdn(FILE* input, struct dfa* idn){

}

void scanCnst(FILE* input, struct dfa* cnst){
    
}

void scanStr(FILE* input, struct dfa* str){
    
}

void scanPunc(FILE* input){
    
}

void scanKey(FILE* input){
    
}

void scan(FILE* input, FILE* output){
    struct dfa* idn = makeDFA(2);
    addTrans(idn, 0, 1, UNDER);
    addTrans(idn, 0, 1, LET);
    addTrans(idn, 1, 1, LET);
    addTrans(idn, 1, 1, UNDER);
    addTrans(idn, 1, 1, DIG);
    makeFinal(idn, 1);
    struct dfa* cnst = makeDFA(6);
    addTrans(cnst, 0, 1, DIG);
    addTrans(cnst, 1, 1, DIG);
    addTrans(cnst, 1, 2, DOT);
    addTrans(cnst, 2, 2, DIG);
    addTrans(cnst, 0, 3, QT);
    addTrans(cnst, 3, 4, LET);
    addTrans(cnst, 3, 4, DIG);
    addTrans(cnst, 3, 4, DOT);
    addTrans(cnst, 3, 4, OP);
    addTrans(cnst, 3, 4, SPC);
    addTrans(cnst, 3, 4, DQ);
    addTrans(cnst, 3, 4, UNDER);
    addTrans(cnst, 3, 4, NLN);
    addTrans(cnst, 3, 4, OTHR);
    addTrans(cnst, 4, 5, QT);
    makeFinal(cnst, 1);
    makeFinal(cnst, 2);
    makeFinal(cnst, 5);
    struct dfa* str = makeDFA(3);
    addTrans(str, 0, 1, DQ);
    addTrans(str, 1, 1, LET);
    addTrans(str, 1, 1, DIG);
    addTrans(str, 1, 1, DOT);
    addTrans(str, 1, 1, OP);
    addTrans(str, 1, 1, SPC);
    addTrans(str, 1, 1, QT);
    addTrans(str, 1, 1, UNDER);
    addTrans(str, 1, 1, NLN);
    addTrans(str, 1, 1, OTHR);
    addTrans(str, 1, 2, DQ);
    makeFinal(str, 2);

}