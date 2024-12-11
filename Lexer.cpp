#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <thread>

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
const char* keywords[] = {
    "if", "else", "for", "while", "int", "float", "char", "void", "return", "nullptr" 
};

TokenType getTokenType(const std::string& token) {
    for (const char* keyword : keywords) {
        if (keyword && token == keyword) {
            return KEYWORD;
        }
    }

    if (isalpha(token[0]) || token[0] == '_') { 
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

std::vector<Token> tokenize_part(const std::string& input) {
    return tokenize(input); 
}

int main(){
    
    std::cout << "enter the file name: ";
    std::cin >> filename;
   if(filename.ends_with(".cpps"){ std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());

    // Divide input into three parts (simplified)
    size_t one_third = content.size() / 3;
    std::string part1 = content.substr(0, one_third);
    std::string part2 = content.substr(one_third, one_third);
    std::string part3 = content.substr(one_third * 2); 

    std::vector<std::thread> threads;
    std::vector<std::vector<Token>> results; 

    threads.emplace_back(tokenize_part, part1); 
    threads.emplace_back(tokenize_part, part2); 
    threads.emplace_back(tokenize_part, part3); 

    for (auto& thread : threads) {
        thread.join(); 
    }

    std::vector<Token> all_tokens;
    for (const auto& result : results) {
        all_tokens.insert(all_tokens.end(), result.begin(), result.end()); 
    }
std::ofstream output_file(filename - ".cpps" + ".tok");
if (output_file.is_open()) {
    for (const Token& token : all_tokens) {
        output_file << token.type << " " << token.value << std::endl;
    }
    output_file.close();
    std::cout << "Tokens written to file" << std::endl;
} else {
    std::cerr << "Error: Could not open output file" << std::endl;
}
                                 }
    else{
        cout << "wrong extension";
    }
    return 0;
}
