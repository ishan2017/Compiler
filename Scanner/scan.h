extern int putback;

extern int line;

extern FILE *input;
extern FILE *output;
extern FILE *copy;

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

void scan();