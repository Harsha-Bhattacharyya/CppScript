#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

vector<string> tokenize(const string& input) {
    vector<string> tokens;
    string currentToken;

    for (char c : input) {
        if (isalpha(c) || isdigit(c) || c == '_') {
            currentToken += c;
        } else if (!isspace(c) && !currentToken.empty()) {
            tokens.push_back(currentToken);
            currentToken.clear();
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

int main() {
    string filename;
    cin >> filename;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());

    vector<string> tokens = tokenize(content);

    cout << "Tokens: ";
    for (const string& token : tokens) {
        cout << token << " ";
    }
    cout << endl;

    return 0;
}
