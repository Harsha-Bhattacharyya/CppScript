install: Lexer.cpp token/token.h
  clang++ -std=c++20 Lexer.cpp -o cpps 

clean:
  rm -f cpps
