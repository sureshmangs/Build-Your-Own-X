#include <iostream>

#include "compress.h"
#include "decompress.h"



int main(int argc, char* argv[])
{
    if (argc < 4 || argc > 5)
    {
        std::cerr << "Usage: ./huffman -c | -d <sourceFileName> <destinationFileName [displayData]\n";
        return 1;
    }

    if (std::string(argv[1]) != "-c" && std::string(argv[1]) != "-d")
    {
        std::cerr << "Usage: ./huffman -c | -d <sourceFileName> <destinationFileName [displayData]\n";
        return 1;
    }

    std::string sourceFile       = std::string(argv[2]);
    std::string destinationFile  = std::string(argv[3]);

    if (sourceFile == destinationFile)
    {
        std::cerr << "Error: The source file and the destination file cannot have ame name\n";
        return 1;
    }

    // Used to display the compression and de-compression process
    if (argc == 5)
        displayData = argv[4];

    if (std::string(argv[1]) == "-c")
    {
        if (displayData)
            std::cout << "Perform compression\n";

        if (compress(sourceFile, destinationFile))
        {
            if (displayData)
                std::cout << "Compression complete\n";

            std::cout << "Size of " << sourceFile << " : " << countNumberOfBytes(sourceFile) << " bytes\n";
            std::cout << "Size of " << destinationFile << " : " << countNumberOfBytes(destinationFile) << " bytes\n";
        }
        else
            return 1;   // compression was not successful
    }
    else if (std::string(argv[1]) == "-d")
    {
        if (displayData)
            std::cout << "Perform de-compression\n";

        if (decompress(sourceFile, destinationFile))
        {
            if (displayData)
                std::cout << "De-compression complete\n";

            std::cout << "Size of " << sourceFile << " : " << countNumberOfBytes(sourceFile) << " bytes\n";
            std::cout << "Size of " << destinationFile << " : " << countNumberOfBytes(destinationFile) << " bytes\n";
        }
        else
            return 1;   // de-compression was not successful
    }

    return 0;
}