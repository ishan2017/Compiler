#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "states.h"
#include "scan.h"

int getNext(){
    int c;
    if (putback){
        c = putback;
        putback = 0;
        return c;
    }
    c = fgetc(input);
    if(c == '\n'){
        line++;
    }
    return c;
}

int skip(){
    int c = getNext(input);
    while(' ' == c || '\n' == c || '\f' == c || '\r' == c || '\t' == c){
        c = getNext(input);
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

void addToken(struct token* tok){
    fprintf(output, tok->print);
}

int scanDFA(struct dfa* dfa){
    long pos = ftell(input);
    fseek(copy, pos, SEEK_SET);
    int c;
    while(1){
        c = getNext(copy);
        if(transition(dfa, getChar(c))){
            putback = c;
            break;
        }
    }
    if(isFinal(dfa, dfa->cur)){
        dfa->cur = 0;
        return 1;
    }
    dfa->cur = 0;
    return 0;
}

int scanPunc(){
    return 0;
}

int scanKey(){
    return 0;
}

void error(){
    printf("Syntax error on line: %d", line);
    exit(1);
}

void scan(){
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
    while(1){
        char c = skip(input);
        if(c == EOF){
            break;
        }
        putback = c;
        int flag = 1;
        struct token* tok = (struct token*)malloc(sizeof(struct token));
        switch(getChar(c)){
            case LET:
                if(scanKey(input)){
                    flag = 0;
                    tok->token = keyword;
                    tok->print = "KEYWORD ";
                    break;
                }
            case UNDER:
                if(scanDFA(idn)){
                    flag = 0;
                    tok->token = identifier;
                    tok->print = "IDENTIFIER ";
                }
                break;
            case QT:
                if(scanDFA(cnst)){
                    flag = 0;
                    tok->token = constant;
                    tok->print = "CONSTANT ";
                }
                break;
            case DIG:
                if(scanDFA(cnst)){
                    flag = 0;
                    tok->token = constant;
                    tok->print = "CONSTANT ";
                }
                break;
            case DQ:
                if(scanDFA(str)){
                    flag = 0;
                    tok->token = stringLiteral;
                    tok->print = "STRINGLITERAL ";
                }
                break;
            case OP:
                if(scanPunc(input)){
                    flag = 0;
                    tok->token = punctuator;
                    tok->print = "PUNCTUATOR ";
                }
                break;
        }
        if(flag){
            error();
        }
        addToken(tok);
    }
    freeDfa(idn);
    freeDfa(cnst);
    freeDfa(str);
}