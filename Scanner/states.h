struct transition{
    int let;
    struct state* next;
};

struct state{
    int numTrans;
    int id;
    int final;
    struct transition* transitions;
};

struct dfa{
    int numstates;
    int cur;
    struct state* states;
};

struct dfa* makeDFA(int numstates);

void addTrans(struct state* target, struct state* next, int let);

void makeFinal(struct dfa* cur, int id);

int isFinal(struct dfa* cur, int id);

void printCurr(struct dfa* cur);

void transition(struct dfa* cur, int let);