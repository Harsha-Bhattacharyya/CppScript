#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
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
    cout << "Enter the file name: ";
    cin >> filename;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());

    vector<string> tokens = tokenize(content);
     //start the ofstream
    string outputFilename = filename + ".tok"; 

    ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not create output file" << endl;
        return 1;
    }

    for (const string& token : tokens) {
        outputFile << token << endl;
    }

    cout << "Tokens written to " << outputFilename << endl;

    return 0;
}
