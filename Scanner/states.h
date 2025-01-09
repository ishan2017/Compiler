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

void addTrans(struct dfa* cur, int tar, int nxt, int let);

void makeFinal(struct dfa* cur, int id);

int isFinal(struct dfa* cur, int id);

int getCurr(struct dfa* cur);

void printCurr(struct dfa* cur);

int transition(struct dfa* cur, int let);

void freeDfa(struct dfa* cur);