#include <iostream>
#include <fstream>

using namespace std;


// Count the number of lines in the input file
int countNumberOfLines(ifstream &file)
{
    int numOfLines = 0;
    string line;

    while (getline(file, line))
        numOfLines++;

    return numOfLines;
}


// Count the number of bytes in the input file
int countNumberOfBytes(ifstream &file)
{
    int numOfBytes= 0;

    file.seekg(0, ios::end);    // Seek to the end of the file to get its size
    numOfBytes = file.tellg();

    return numOfBytes;
}


// Count the number of words in the input file
int countNumberOfWords(ifstream &file)
{
    int numOfWords = 0;
    string line;

    while (getline(file, line))
    {
        int index = 0;
        while (index < line.length())
        {
            if (isspace(line[index]))
            {
                index++;
                continue;;
            }

            numOfWords++;

            while (index < line.length() && !isspace(line[index]))
                index++;
        }
    }

    return numOfWords;
}


// Count the number of characters in the input file
int countNumberOfCharacters(ifstream &file)
{
    int numOfCharacters = 0;
    char ch;

    while (file.get(ch))
        numOfCharacters++;

    return numOfCharacters;
}


// Validate the option - i.e. -l, -w, -c, -m
bool isOptionValid(string option)
{
    if (option.length() != 2 || (option.length() == 2 && option[0] != '-'))
        return false;   // invalid option
    return true;        // valid option
}


int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << endl;
        return 1;
    }

    // Handle read from standard input if no filename is specified
    // i.e. cat file.txt | ccwc -l
    if (argc == 2 && cin.peek())
    {
        if (!isOptionValid(string(argv[1])))
        {
            cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << endl;
            return 1;
        }

        char option = string(argv[1])[1];

        string fileName = "inputFile.txt";

        ofstream outputFile(fileName);

        if (!outputFile)
        {
            cerr << "Error creating the file " << fileName << endl;
            return 1;
        }

        string inputText;

        // Read from standard input (stdin) and write into the inputFile.txt
        while (getline(cin, inputText))
            outputFile << inputText << endl;
        
        outputFile.close();

        ifstream inputFile(fileName);

        if (!inputFile.is_open())
        {
            cerr << "Error: Could not open file " << fileName << endl;
            return 1;
        }
        
        switch (option)
        {
            case 'l':
                cout << countNumberOfLines(inputFile) << endl;
                break;
            case 'c':
                cout << countNumberOfBytes(inputFile) << endl;
                break;
            case 'm':
                cout << countNumberOfCharacters(inputFile) << endl;
                break;
            case 'w':
                cout << countNumberOfWords(inputFile) << endl;
                break;
            default:
                cerr << "Error: Invalid option. Use -l, -w, -c or -m." << endl;
                break;
        }

        inputFile.close();
        
        if (remove(fileName.c_str()) == 0)
        {
            // File successfully deleted
        }
        else
        {
            cerr << "Error: Deleting the file " << fileName << endl;
            return 1;
        }

        return 0;
    }
    // Handle default option if no options are provided
    // i.e. ccwc file.txt
    else if (argc == 2)
    {
        ifstream inputFile(argv[1]);

        if (!inputFile.is_open())
        {
            cerr << "Error: Could not open file " << argv[1] << endl;
            return 1;
        }

        cout << countNumberOfLines(inputFile) << " ";

        inputFile.clear();               // Clear any error flags
        inputFile.seekg(0, ios::beg);    // Move to the start of the file

        cout << countNumberOfWords(inputFile) << " ";

        inputFile.clear();               // Clear any error flags
        inputFile.seekg(0, ios::beg);    // Move to the start of the file

        cout << countNumberOfBytes(inputFile) << " " <<  argv[1] << endl;

        inputFile.close();

        return 0;
    }

    // Handle regular option if all options are provided
    // i.e. ccwc -l file.txt
    if (argc == 3)
    {
        if (!isOptionValid(string(argv[1])))
        {
            cerr << "Usage: " << argv[0] << " <-l | -w | -c | -m> <filename>" << endl;
            return 1;
        }

        char option = string(argv[1])[1];

        ifstream inputFile(argv[2]);

        if (!inputFile.is_open())
        {
            cerr << "Error: Could not open file " << argv[2] << endl;
            return 1;
        }

        switch (option)
        {
            case 'l':
                cout << countNumberOfLines(inputFile) << " " << argv[2] << endl;
                break;
            case 'c':
                cout << countNumberOfBytes(inputFile) << " " << argv[2] << endl;
                break;
            case 'm':
                cout << countNumberOfCharacters(inputFile) << " " << argv[2] << endl;
                break;
            case 'w':
                cout << countNumberOfWords(inputFile) << " " << argv[2] << endl;
                break;
            default:
                cerr << "Error: Invalid option. Use -l, -w, -c or -m." << endl;
                return 1;
        }

        inputFile.close();

        return 0;
    }

    return 0;
}