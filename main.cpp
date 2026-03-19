#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"
#include "Scanner.h"

using namespace std;

// Pomožna funkcija, ki preslika integer ID tokena v njegovo besedilno ime
string getTerminalName(int tokenID) {
    switch (tokenID) {
        case Scanner::tInt: return "int";
        case Scanner::tHex: return "hex";
        case Scanner::tVariable: return "variable";
        case Scanner::tPlus: return "plus";
        case Scanner::tMinus: return "minus";
        case Scanner::tTimes: return "times";
        case Scanner::tDivide: return "divide";
        case Scanner::tModulo: return "modulo";
        case Scanner::tBwand: return "bwand";
        case Scanner::tBwor: return "bwor";
        case Scanner::tLparen: return "lparen";
        case Scanner::tRparen: return "rparen";
        default: return "error";
    }
}

void Bitwise(Scanner& scanner, Token& currentToken);
void BitwiseApostroph(Scanner& scanner, Token& currentToken);
void Additive(Scanner& scanner, Token& currentToken);
void AdditiveApostroph(Scanner& scanner, Token& currentToken);
void Multiplicative(Scanner& scanner, Token& currentToken);
void MultiplicativeApostroph(Scanner& scanner, Token& currentToken);
void Unary(Scanner& scanner, Token& currentToken);
void Primary(Scanner& scanner, Token& currentToken);

void Primary(Scanner& scanner, Token& currentToken) {
    int type = currentToken.getToken();
    if (type == Scanner::tInt || type == Scanner::tHex || type == Scanner::tVariable) {
        currentToken = scanner.nextToken();
    } else if (type == Scanner::tLparen) {
        currentToken = scanner.nextToken();
        Bitwise(scanner, currentToken);
        if (currentToken.getToken() == Scanner::tRparen) {
            currentToken = scanner.nextToken();
        } else {
            cout << "reject" << endl; exit(0);
        }
    } else {
        cout << "reject" << endl; exit(0);
    }
}

void Unary(Scanner& scanner, Token& currentToken) {
    int type = currentToken.getToken();
    if (type == Scanner::tPlus || type == Scanner::tMinus) {
        currentToken = scanner.nextToken();
        Primary(scanner, currentToken);
    } else {
        Primary(scanner, currentToken);
    }
}

void MultiplicativeApostroph(Scanner& scanner, Token& currentToken) {
    if (currentToken.getToken() == Scanner::tTimes || currentToken.getToken() == Scanner::tDivide ||
        currentToken.getToken() == Scanner::tModulo) {
        currentToken = scanner.nextToken();
        Unary(scanner, currentToken);
        MultiplicativeApostroph(scanner, currentToken);
    }
}

void AdditiveApostroph(Scanner& scanner, Token& currentToken) {
    if (currentToken.getToken() == Scanner::tPlus || currentToken.getToken() == Scanner::tMinus) {
        currentToken = scanner.nextToken();
        Multiplicative(scanner, currentToken);
        AdditiveApostroph(scanner, currentToken);
    }
}

void BitwiseApostroph(Scanner& scanner, Token& currentToken) {
    if (currentToken.getToken() == Scanner::tBwand || currentToken.getToken() == Scanner::tBwor) {
        currentToken = scanner.nextToken();
        Additive(scanner, currentToken);
        BitwiseApostroph(scanner, currentToken);
    }
}

void Multiplicative(Scanner& scanner, Token& currentToken) {
    Unary(scanner, currentToken);
    MultiplicativeApostroph(scanner, currentToken);
}

void Additive(Scanner& scanner, Token& currentToken) {
    Multiplicative(scanner, currentToken);
    AdditiveApostroph(scanner, currentToken);
}

void Bitwise(Scanner& scanner, Token& currentToken) {
    Additive(scanner, currentToken);
    BitwiseApostroph(scanner, currentToken);
}

void Expr(Scanner& scanner, Token& currentToken){
    Bitwise(scanner, currentToken);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Napacna uporaba! Zazenite s: " << argv[0] << " <vhodna_datoteka>" << endl;
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Napaka pri odpiranju datoteke: " << argv[1] << endl;
        return 1;
    }

    Scanner scanner(&inputFile);
    Token currentToken;
    //getToken nas zanima (int...)

    currentToken = scanner.nextToken();
    Expr(scanner, currentToken);
    //je dovolj, če rečem, da mora biti current token == ""?
    if (currentToken.isEof() && currentToken.getLexem() == "") cout << "accept" << endl;
    else cout << "reject" << endl;

    cout << endl;
    inputFile.close();

    return 0;
}