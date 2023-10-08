#include <iostream>
#include <fstream>
#include <vector>

#include "common.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"



int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cerr << "Usage: " << argv[0] << " <fileName> [displayData]\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);

    if (!inputFile.is_open())
    {
        std::cerr << "Error in opening file " << argv[1] << "\n";
        return 1;
    }

    // For displaying the tokens and parsing phase
    if (argc == 3)
        displayData = argv[2];

    std::vector <Token> tokens;

    // Perform lexical analysis
    lexer(inputFile, tokens);

    inputFile.close();

    tokenSize = tokens.size();

    displayTokens(tokens);

    // Check if invalid JSON found in lexical analysis
    if (tokenSize > 0 && tokens[tokenSize - 1].type == UNKNOWN)
    {
        std::cout << "INVALID JSON\n";
    }
    else
    {
        // perform parsing
        if (!parser(tokens))
            std::cout << "INVALID JSON\n";
        else
            std::cout << "VALID JSON\n";
    }

    return 0;
}