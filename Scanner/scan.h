enum tokens{
    ADD, SUB, MUL, DIV, EQ, INT
};

enum chars{
    DIG, SPC, OP, NLN, EDOF
};

struct token{
    int token;
    char* print;
};