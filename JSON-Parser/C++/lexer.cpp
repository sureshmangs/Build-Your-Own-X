#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

#include "common.h"
#include "token.h"
#include "lexer.h"



// To get a token type in string format

std::string getTokenType(tokenTypes option)
{
    switch(option)
    {
        case LEFTCURLYBRACKET:
            return "LEFTCURLYBRACKET";
        case RIGHTCURLYBRACKET:
            return "RIGHTCURLYBRACKET";
        case LEFTSQUAREBRACKET:
            return "LEFTSQUAREBRACKET";
        case RIGHTSQUAREBRACKET:
            return "RIGHTSQUAREBRACKET";
        case LEFTROUNDBRACKET:
            return "LEFTROUNDBRACKET";
        case RIGHTROUNDBRACKET:
            return "RIGHTROUNDBRACKET";
        case DOT:
            return "DOT";
        case COLON:
            return "COLON";
        case COMMA:
            return "COMMA";
        case DOUBLEQUOTE:
            return "DOUBLEQUOTE";
        case STRINGVALUE:
            return "STRINGVALUE";
        case BOOLEAN:
            return "BOOLEAN";
        case NUMBER:
            return "NUMBER";
        case NULLVALUE:
            return "NULLVALUE";
        default:
            return "UNKNOWN";
    }
}



// Add a token to the tokens vector

void AddToken (std::vector <Token> &tokens, tokenTypes type, std::string value)
{
    Token token;
    token.type = type;
    token.value = value;
    tokens.push_back(token);
}



// Check whether the string is a valid number

bool isNumber(std::string input)
{
    // Regular expression to match valid numbers
    std::regex numberPattern("^[-+]?(0|([1-9]\\d*\\.?\\d*)|0?\\.\\d+)([eE][-+]?\\d+)?$");

    // Check if the input matches the pattern
    return std::regex_match(input, numberPattern);
}



// Check whether the value is a number, boolean, null

tokenTypes getValueType(std::string str)
{
    if (str == "true" || str == "false")
        return BOOLEAN;
    else if (str == "null")
        return NULLVALUE;
    else if (isNumber(str))
        return NUMBER;
    else
        return UNKNOWN;
}



// Check whether the character is a closing bracket or a comma

bool isClosingBracketOrComma(char ch)
{
    return ch == ')' || ch == '}' || ch == ']' || ch == ',';
}



/*  Escape characters are special characters used in strings and text to represent
    characters that are difficult or impossible to represent directly.
    These characters typically start with a backslash \ followed by one or more
    characters and are used to encode non-printable or special characters, such
    as newline, tab, or quotation marks, within a string.
*/

bool isValidEscapeCharacterForJSON(char ch)
{
    if (ch == '"' || ch == '\\' || ch == '/' || ch == 'b' ||
        ch == 'f' || ch == 'n' || ch == 'r' || ch == 't')
        return true;
    return false;
}



/*  Control characters are characters that do not represent printable symbols but
    instead serve to control or manipulate the appearance and behavior of the text.
    These characters are typically not visible when rendered or printed and are
    used for various purposes, such as formatting, signaling, and control.
    Few examples:
            Newline (Line Feed) (\n)
            Carriage Return     (\r)
            Tab                 (\t)
            Backspace           (\b)
            Form Feed           (\f)
            Vertical Tab        (\x0B)
*/

bool isControlCharacter(char ch)
{
    return (std::iscntrl(ch));
}



//  Displaying the tokens created in lexical analysis

void displayTokens(std::vector <Token> &tokens)
{
    if (!displayData)
        return;

    std::cout << "Tokenization:\n";
    std::cout << "-------------------------------\n";
    for (auto &token: tokens)
    {
        std::cout << getTokenType(token.type) << " : " << token.value << "\n";
    }
    std::cout << "-------------------------------\n\n";
}



/*  Check whether a string is valid or not.
    A valid string has doublequotes at the start and end.
    If it contains a backslash then it must have an escape
    character after it.
*/

bool isValidString(std::string &str)
{
    for (int index = 0; index < str.length(); index++)
    {
        if (str[index] == '\\')
        {
            index++;
            // The backslash must have an escape character after it
            if (index >= str.length())
                return false;

            // Check if the next character is a valid escape character
            if (isValidEscapeCharacterForJSON(str[index]))
            {
                continue;
            }
            else if (str[index] == 'u')
            {
                // Handle Unicode escape sequence (\uXXXX)
                // Check for next 4 hexadecimal digits (\uXXXX)
                for (int j = 0; j < 4; j++)
                {
                    index++;
                    // Check if the next character doesn't exists
                    // or if it's not a hexadecimal character
                    if (index >= str.length() || !isxdigit(str[index]))
                        return false;
                }
            }
            else
                // Any other character following a backslash is invalid
                return false;
        }
    }
    return true;
}


// Perform lexical analysis

void lexer(std::ifstream &file, std::vector <Token> &tokens)
{
    std::string line;
    while (getline(file, line))
    {
        int index = 0;
        while (index < line.length())
        {
            // Ignore white spaces at the beginining and end of th tokens
            if (isspace(line[index]))
            {
                index++;
                continue;
            }

            switch(line[index])
            {
                case '{':
                    AddToken(tokens, LEFTCURLYBRACKET, "{");
                    break;

                case '}':
                    AddToken(tokens, RIGHTCURLYBRACKET, "}");
                    break;

                case '[':
                    AddToken(tokens, LEFTSQUAREBRACKET, "[");
                    break;

                case ']':
                    AddToken(tokens, RIGHTSQUAREBRACKET, "]");
                    break;

                case '(':
                    AddToken(tokens, LEFTROUNDBRACKET, "(");
                    break;

                case ')':
                    AddToken(tokens, RIGHTROUNDBRACKET, ")");
                    break;

                case ':':
                    AddToken(tokens, COLON, ":");
                    break;

                case ',':
                    AddToken(tokens, COMMA, ",");
                    break;

                case '"':
                    {
                        // Check for String values
                        std::string str = "";
                        bool strEndsWithDoubleQuotes = false;

                        str += line[index]; // adding " to str
                        index++;

                        while (index < line.length())
                        {
                            if (line[index] == '\\')    // backslash
                            {
                                str += line[index]; // adding backslash to str
                                index++;
                                if (index < line.length())
                                {
                                    str += line[index];
                                    index++;
                                }
                                continue;
                            }
                            else if (isControlCharacter(line[index]))
                            {
                                str += line[index]; // add control character
                                break;
                            }

                            if (line[index] == '"')
                            {
                                str += line[index]; // adding " to str
                                // used to check whether the string
                                // has ended with a doublequote
                                strEndsWithDoubleQuotes = true;
                                break;
                            }
                            str += line[index];
                            index++;
                        }

                        if (isValidString(str) && strEndsWithDoubleQuotes)
                            AddToken(tokens, STRINGVALUE, str);
                        else
                        {
                            AddToken(tokens, UNKNOWN, str);
                            return;
                        }
                    }
                    break;

                default:
                    {
                        // Check for Number, Boolean and NULL values
                        std::string str = "";
                        while (index < line.length() && !isClosingBracketOrComma(line[index]))
                        {
                            if (isspace(line[index]))
                                break;

                            str += line[index];
                            index++;
                        }
                        
                        // Check whether the value is a number, boolean, null
                        tokenTypes valueType = getValueType(str);
                        AddToken(tokens, valueType, str);

                        if (valueType == UNKNOWN)
                            return;

                        if (index < line.length() && isClosingBracketOrComma(line[index]))
                            index--;
                    }
            }
            index++;    // read next character
        }
    }
}