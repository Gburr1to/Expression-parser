#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"
#include "Scanner.h"
#include "Parser.h"
#include <stdexcept>
#include <exception>

using namespace std;



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
    try {
        Parser::Expr(scanner, currentToken);
        if (currentToken.isEof() && currentToken.getLexem() == "") cout << "accept" << endl;
        else cout << "reject" << endl;
    }catch (std::exception& e) {
        cout << "reject:\n" << e.what();
    }


    cout << endl;
    inputFile.close();

    return 0;
}
