enum tokens{
    OPERATOR, INTEGER
};

enum chars{
    DIG, SPC, OP, NLN, EDOF
};

struct token{
    int token;
    char* print;
};