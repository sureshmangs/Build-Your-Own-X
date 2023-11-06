#include <iostream>

#include "decompress.h"
#include "common.h"
#include <fstream>
#include <map>



/**
 *  Perform the de-compression of source file into destination file
 *  1. Read the header of the source file to compute the frequency
 *     of characters used in the original file until ENDOFHEADER is
 *     encountered
 *  2. Build the huffman tree from the frequency of characters
 *  3. Read the actual compressed data from the source file and 
 *     write equivalent original data to destination file
 *
 *  @param      {string} name of the source file
 *  @param      {string} name of the destination file
 *  @returns    {bool}  return true if compression was successful
 */
bool decompress(std::string sourceFile, std::string destinationFile)
{
    std::wifstream inputFile(sourceFile, std::ios::in | std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << sourceFile << "\n";
        return false;
    }

    // Set the file's locale to support UTF-8
    inputFile.imbue(std::locale("en_US.UTF-8"));

    // Read the header to compute frequency of characters
    std::map <std::wstring, int> frequencyMap;

    std::wstring line;
    while (getline(inputFile, line))
    {
        // Found the end of the header
        if (line == ENDOFHEADER)
            break;

        // Frequency is stored as <character><occurenceOfCharacter> in compression
        if (line.length() < 2)
        {
            std::cerr << "Error: In de-compression while reading the header\n";
            return false;
        }

        std::wstring data         = L"";
        std::wstring frequencyStr = L"";

        if (isdigit(line[1]))
        {
            data += line[0];
            frequencyStr = line.substr(1);
        }
        else
        {
            data = ENDOFLINE;
            frequencyStr = line.substr(data.length());
        }
        try
        {
            frequencyMap[data] = stoi(frequencyStr);
        }
        catch(...)
        {
            std::cerr << "Error: In de-compression while computing the frequency in header\n";
            return false;
        }
    }

    // Position after the header has been successfully read
    int actualDataPosition = inputFile.tellg();

    // Closing the file as it needs to be opened in char
    // format to read actual compressed data
    inputFile.close();

    if (displayData)
    {
        std::cout << "Display frequency of characters:\n";
        std::cout << "Total unique characters: " << frequencyMap.size() << "\n";
        
        for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++)
            std::wcout << it->first <<  " : " << it->second << "\n";
    }

    huffmanNode *root = NULL;

    root = buildHuffmanTree(frequencyMap);

    if (displayData)
    {
        std::cout << "Display huffman tree:\n";
        displayTree(root);
    }

    int numOfLines = frequencyMap[ENDOFLINE];

    // Read the actual compressed data
    std::ifstream inputFile1(sourceFile, std::ios::in | std::ios::binary);

    if (!inputFile1.is_open())
    {
        std::cerr << "Error: Could not open file " << sourceFile << "\n";
        return false;
    }

    // Move to position to read the actual compressed data
    inputFile1.seekg(actualDataPosition, std::ios::beg);

    std::wofstream outputFile(destinationFile, std::ios::out | std::ios::binary);

    if (!outputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << destinationFile << "\n";
        return false;
    }

    // Set the file's locale to support Unicode characters (UTF-8)
    outputFile.imbue(std::locale("en_US.UTF-8"));

    // Here, we read a character from the source file and use it's
    // individual bits one by one to find a equivalent original
    // character in the huffman tree
    huffmanNode *current = root;
    char ch;
    while (!inputFile1.eof() && inputFile1.get(ch))
    {
        // Read the data from the characters 8 bits
        for (int i = 7; i >= 0; i--)
        {
            bool bit = ch & (1 << i);

            if (bit)
                current = current->right;
            else
                current = current->left;
                
            if (current == NULL)
            {
                std::cerr << "Error: In de-compression while reading the compressed data\n";
                return false;
            }

            // Check if the leaf node character
            if (!current->left && !current->right)
            {
                if (current->data == ENDOFLINE)
                {
                    if (numOfLines > 1)
                    {
                        outputFile << "\n";
                        numOfLines--;
                    }

                    current = root;

                    break; // one line has been read
                }
                else
                {
                    outputFile << current->data;
                    current = root;
                }
            }
        }
    }

    inputFile1.close();
    outputFile.close();

    return true;    // De-compression was successful
}