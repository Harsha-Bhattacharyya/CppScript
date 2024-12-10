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
    cout << "**CppScript Lexer prototype-version-1**";
    cout << "**Licensed by the GNU gpl v3**";
    cout << "**GITHUB: https://github.com/Harsha-Bhattacharyya/CppScript**";
    cout << '\n';
    cout << "Enter the file name: ";
    cin >> filename;
    if(filename.ends_with(".cpps")){
        ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());

    vector<string> tokens = tokenize(content);
     //start the ofstream
    string outputFilename = filename - ".cpps" + ".tok"; 

    ofstream outputFile(outputFilename);

    if (!outputFile.is_open()) {
        cerr << "Error: Could not create output file" << endl;
        return 1;
    }

    for (const string& token : tokens) {
        outputFile << token << endl;
    }

    cout << "Tokens written to " << outputFilename << endl;
    }
   else{
       cout << "Wrong file name!"
   }

    return 0;
}
