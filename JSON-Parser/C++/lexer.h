// Function declarations

std::string getTokenType(tokenTypes option);

void AddToken (std::vector <Token> &tokens, tokenTypes type, std::string value);

bool isNumber(std::string input);

tokenTypes getValueType(std::string str);

bool isClosingBracketOrComma(char ch);

bool isValidEscapeCharacterForJSON(char ch);

bool isControlCharacter(char ch);

void displayTokens(std::vector <Token> &tokens);

bool isValidString(std::string &str);

void lexer(std::ifstream &file, std::vector <Token> &tokens);