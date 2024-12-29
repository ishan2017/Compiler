enum chars{
    DIG, SPC, OP, NLN, EDOF
};

int tranSize = 10;

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

void transition(struct dfa* cur, int let);