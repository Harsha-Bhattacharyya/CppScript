#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_set>

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

// Set of keywords for easy lookup
std::unordered_set<std::string> keywords = {
    "if", "else", "for", "while", "int", "float", "char", "void", "return"
};

TokenType getTokenType(const std::string& token) {
    if (keywords.count(token) > 0) {
        return KEYWORD;
    } else if (isalpha(token[0]) || token[0] == '_') {
        return IDENTIFIER;
    } else if (isdigit(token[0])) {
        // Check for integers or floats
        bool isFloat = false;
        for (char c : token) {
            if (c == '.') {
                isFloat = true;
                break;
            }
        }
        return isFloat ? FLOAT_LITERAL : INTEGER_LITERAL;
    } else if (token.size() == 1 && ispunct(token[0])) {
        return PUNCTUATOR;
    } else if (token == "+=" || token == "-=" || token == "*=" || token == "/=") {
        return OPERATOR;
    } else if (token == "+" || token == "-" || token == "*" || token == "/" ||
               token == "<" || token == ">" || token == "=" || token == "!" ||
               token == "&" || token == "|" || token == "%") {
        return OPERATOR;
    }
    return UNKNOWN;
}

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string currentToken;

    for (char c : input) {
        if (isalnum(c) || c == '_' || c == '.') { // Allow '.' for floats
            currentToken += c;
        } else if (!isspace(c) && !currentToken.empty()) {
            tokens.emplace_back(getTokenType(currentToken), currentToken);
            currentToken.clear();
        } else if (!isspace(c)) {
            tokens.emplace_back(getTokenType(std::string(1, c)), std::string(1, c));
        }
    }

    if (!currentToken.empty()) {
        tokens.emplace_back(getTokenType(currentToken), currentToken);
    }

    return tokens;
}

int main() {
    std::string filename;
    std::cout << "**CppScript Lexer prototype-version-2**";
    std::cout << "**Licensed by the GNU gpl v3**";
    std::cout << "**GITHUB: https://github.com/Harsha-Bhattacharyya/CppScript**";
    std::cout << '\n';
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::ifstream file(filename);
if(filename.ends_with(".cpps")){
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    std::vector<Token> tokens = tokenize(content);

    std::ofstream output_file("tokens.tok");
    if (!output_file.is_open()) {
        std::cerr << "Error: Could not open output file: " << strerror(errno) << std::endl;
        return 1;
    }

    for (const Token& token : tokens) {
        output_file << "type:" << token.type << ", value: " << token.value << std::endl;
    }

    output_file.close();
    std::cout << "Tokens written to tokens.tok" << std::endl;
}
else{
    std::cerr << "Error: Wrong extension";
}
    return 0;
}
