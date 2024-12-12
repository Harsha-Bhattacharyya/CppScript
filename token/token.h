#include <string>
#include <vector>

enum TokenType {
    UNKNOWN, 
    KEYWORD, 
    IDENTIFIER, 
    INTEGER_LITERAL, 
    FLOAT_LITERAL, 
    STRING_LITERAL, 
    OPERATOR, 
    PUNCTUATOR, 
    WHITESPACE 
};

struct Token {
    TokenType type;
    std::string value;
};
