#include "common.h"


// Function declarations
void calculateFrequency(std::wifstream &inputFile, std::map <std::wstring, int> &frequencyMap);
void generateCodes(huffmanNode *root, std::string code, std::map <std::wstring, std::string> &codes);
extern bool compress(std::string inputFileName, std::string compressedFileName);
