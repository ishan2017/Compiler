enum chars{
    DIG, SPC, OP, NLN
}

struct state{
    int id;
}

state* transition(state* cur, int next);