int putback = 0;

int line = 0;

enum tokens{
    identifier, keyword, constant, stringLiteral, punctuator
};

enum chars{
    DIG, SPC, OP, DOT, LET, QT, DQ, BS, UNDER, NLN, EDOF, OTHR
};

struct token{
    int token;
    char* print;
};