#include <stdio.h>
#include <stdlib.h>
#include "states.h"

struct dfa* makeDFA(int numstates){
    struct dfa* retDFA = (struct dfa*)malloc(sizeof(struct dfa));
    retDFA->numstates = numstates;
    retDFA->states = (struct state*)malloc(sizeof(struct state) * numstates);
    struct state* iterator = (struct state*)retDFA->states;
    for(int i = 0; i < numstates; i++){
        struct state* iterator = retDFA->states + i;
        iterator->id = i;
        iterator->numTrans = 0;
        iterator->final = 0;
        iterator->transitions = NULL;
    }
    retDFA->cur = 0;
    return retDFA;
}

void addTrans(struct dfa* cur, int tar, int nxt, int let){
    struct state* target = cur->states + tar;
    struct state* next = cur->states + nxt;
    if(target->numTrans == 0){
        target->transitions = (struct transition*)malloc(sizeof(struct transition));
        target->transitions->let = let;
        target->transitions->next = next;
        target->numTrans = 1;
    }
    else{
        target->numTrans = target-> numTrans + 1;
        target->transitions = (struct transition*)realloc(target->transitions, target->numTrans * sizeof(struct transition));
        struct transition* new = target->transitions + (target->numTrans - 1);
        new->let = let;
        new->next = next;
    }
}

void makeFinal(struct dfa* cur, int id){
    struct state* curr = cur->states + id;
    curr->final = 1;
}

int isFinal(struct dfa* cur, int id){
    struct state* curr = cur->states + id;
    return curr->final;
}

void printCurr(struct dfa* cur){
    struct state* curr = cur->states + cur->cur;
    printf("State: %d \nFinal: %d\n", curr->id, curr->final);
}

void transition(struct dfa* cur, int let){
    struct state* curr = cur->states + cur->cur;
    int flag = 1;
    for(int i = 0; i < curr->numTrans; i++){
        struct transition* iterator = curr->transitions + i;
        if (iterator->let == let){
            cur->cur = iterator->next->id;
            flag = 0;
            break;
        }
    }
    if(flag){
        exit(1);
    }
}