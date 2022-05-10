enum TokenType
{
    Delimiter,
    Comma,
    Comparison,
    Assignment,
    MathSign,
    IOstring,
    KeyWord,
    IO,
    Type,
    Identificator,
    Number,
    Error,
};

struct Token
{
    enum TokenType name;
    char* value;
    int pos;
};
