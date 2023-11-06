#include <iostream>
#include <fstream>
#include <map>
#include "compress.h"



/**
 *  Calculate frequency of each character in the input file
 *
 *  @param      {wifstream} input file
 *  @param      {map <wstring, int>} map to be updated with frequency of characters
 *  @returns
 */
void calculateFrequency(std::wifstream &inputFile, std::map <std::wstring, int> &frequencyMap)
{
    std::wstring line;

    while (!inputFile.eof())
    {
        getline(inputFile, line);

        for (auto &ch: line)
        {
            std::wstring str(1, ch);
            frequencyMap[str]++;
        }
        frequencyMap[ENDOFLINE]++;
    }
}



/**
 *  Generate binary code for each leaf node in the huffman tree
 *
 *  @param      {huffmanNode*} poiner to the root node of the huffman tree
 *  @param      {string} binary code consisting of 0's and 1's
 *  @param      {map <wstring, string>} map representing the binary codes for characters
 *  @returns
 */
void generateCodes(huffmanNode *root, std::string code, std::map <std::wstring, std::string> &codes)
{
    if (!root)
        return;

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);

    if (!root->left && !root->right)
        codes[root->data] = code;
}



/**
 *  Perform the compression of source file into destination file
 *  1. Compute the frequency of characters from source file
 *  2. Build the huffman tree from the frequency of characters
 *  3. Generate binary code for each unique character using the huffman tree
 *  4. Write the header to the destination file which consists of frequecy
 *     of characters and mark the end of header using ENDOFHEADER
 *  5. Write the actual compressed data into the destination file
 *
 *  @param      {string} name of the source file
 *  @param      {string} name of the destination file
 *  @returns    {bool}  return true if compression was successful
 */
bool compress(std::string sourceFile, std::string destinationFile)
{
    std::wifstream inputFile(sourceFile, std::ios::in | std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << sourceFile << "\n";
        return false;
    }

    // Set the file's locale to support UTF-8
    inputFile.imbue(std::locale("en_US.UTF-8"));

    std::map <std::wstring, int> frequencyMap;

    calculateFrequency(inputFile, frequencyMap);

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

    std::map <std::wstring, std::string> codes;

    generateCodes(root, "", codes);

    if (displayData)
    {
        std::cout << "\nDisplay binary codes for characters:\n";

        int maxLen = 0;
        for (auto it = codes.begin(); it != codes.end(); it++)
        {
            std::wcout << it->first << " : ";
            std::cout << it->second << "\n";

            if (maxLen < it->second.length())
                maxLen = it->second.length();
        }

        std::cout << "The length of the longest codes is:" << maxLen << "\n";
    }

    // Create the compressed file
    std::wofstream outputFile(destinationFile, std::ios::binary | std::ios::trunc);

    if (!outputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << destinationFile << "\n";
        return false;
    }

    // Set the file's locale to support Unicode characters (UTF-8)
    outputFile.imbue(std::locale("en_US.UTF-8"));

    // Write the header (i.e., frequency of characters and end of header)
    // Frequency is stored as <character><occurenceOfCharacter>
    for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++)
    {
        outputFile << it->first;
        outputFile << std::to_wstring(it->second);
        outputFile << "\n";
    }

    // Add the charcters specifying the end of the header
    outputFile << ENDOFHEADER << "\n";

    // Closing the file as it needs to be opened in char
    // format to write the actual compressed data
    outputFile.close();

    inputFile.clear();                  // Clear any error flags
    inputFile.seekg(0, std::ios::beg);  // Move to the start of the file

    std::ofstream outputFile1(destinationFile, std::ios::out | std::ios::binary | std::ios::app);

    if (!outputFile1.is_open())
    {
        std::cerr << "Error: Could not open file " << destinationFile << "\n";
        return false;
    }

    // Write the actual data in compressed file
    // Here, we take a char field and mark it's 8 bits based on
    // the binary code of a character and write the field to
    // the destination file
    std::wstring line;
    while (getline(inputFile, line))
    {
        char buffer = 0;
        int bitsWritten = 0;
        for (auto &x: line)
        {
            std::wstring str(1, x);
            std::string code = codes[str];

            // Setting the 8 bits of buffer using the binary code
            for (auto &ch: code)
            {
                if (ch == '1')
                    buffer |= (1 << (7 - bitsWritten));

                bitsWritten++;

                if (bitsWritten == 8)
                {
                    // Write the buffer to the destination file
                    outputFile1 << buffer;
                    buffer = 0; // Reset or empty the buffer
                    bitsWritten = 0;
                }
            }
        }

        // Add end of line code after every actual end of line
        std::string code = codes[ENDOFLINE];
        for (auto &ch: code)
        {
            if (ch == '1')
                buffer |= (1 << (7 - bitsWritten));

            bitsWritten++;

            if (bitsWritten == 8)
            {
                // Write the buffer to the destination file
                outputFile1 << buffer;
                buffer = 0; // Reset or empty the buffer
                bitsWritten = 0;
            }
        }

        // Write the remaining buffer data to the destination file
        if (bitsWritten > 0)
            outputFile1 << buffer;
    }

    inputFile.close();
    outputFile1.close();

    return true;    // Compression was successful
}