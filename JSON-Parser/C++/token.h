// Define valid token types

typedef enum {
    LEFTCURLYBRACKET,       // {
    RIGHTCURLYBRACKET,      // }  
    LEFTSQUAREBRACKET,      // [
    RIGHTSQUAREBRACKET,     // ]
    LEFTROUNDBRACKET,       // (
    RIGHTROUNDBRACKET,      // )
    DOT,                    // .
    COLON,                  // :
    COMMA,                  // ,
    DOUBLEQUOTE,            // "
    STRINGVALUE,            // string
    BOOLEAN,                // true, false
    NUMBER,                 // number
    NULLVALUE,              // null
    UNKNOWN
} tokenTypes_et;

typedef int tokenTypes;


// Define a token data type

struct Token
{
    tokenTypes  type;
    std::string value;
};