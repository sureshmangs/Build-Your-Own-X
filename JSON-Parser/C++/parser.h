// Function declarations

bool parseLeftCurlyBracket(std::vector <Token> &tokens);

bool parseLeftSquareBracket(std::vector <Token> &tokens);

void displayParsingStart();

void displayParsingEnd();

void displayParsing(std::vector <Token> &tokens);

void eat(std::vector <Token> &tokens);

bool isClosingToken(tokenTypes type);

bool isValidDataType(tokenTypes type);

bool parser(std::vector <Token> &tokens);