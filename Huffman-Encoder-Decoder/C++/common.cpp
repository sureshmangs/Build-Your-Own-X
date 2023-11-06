#include <iostream>
#include <fstream>
#include <queue>

#include "common.h"



// Initialize the globally used flag to display the
// huffman compression and de-compression process
bool displayData = false;



/**
 *  Count the number of bytes in the input file
 *
 *  @param      {string} input file
 *  @returns    {int} number of bytes in the input file
 */
int countNumberOfBytes(std::string file)
{
    std::ifstream inputFile(file, std::ios::in | std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open file " << file << "\n";
        return 0;
    }

    int numOfBytes = 0;

    // Seek to the end of the file to get it's size
    inputFile.seekg(0, std::ios::end);
    numOfBytes = inputFile.tellg();

    return numOfBytes;
}



/**
 *  Build the huffman tree
 *
 *  @param      {map <wstring, int>} map representing the frequency of characters
 *  @returns    {huffmanNode*} pointer to the root node of the huffman tree
 */
huffmanNode* buildHuffmanTree(std::map <std::wstring, int> &frequencyMap)
{
    // Create a min heap using priority queue
    std::priority_queue <huffmanNode*, std::vector<huffmanNode*>, CompareHuffmanNode> minHeap;
    
    for (auto it = frequencyMap.begin(); it != frequencyMap.end(); it++)
    {
        huffmanNode *node = new huffmanNode(it->first, it->second);
        minHeap.push(node);
    }

    huffmanNode *root = NULL;

    while (minHeap.size() > 1)  // atleast two elements in the queue
    {
        huffmanNode *leftNode = minHeap.top();
        minHeap.pop();

        huffmanNode *rightNode = minHeap.top();
        minHeap.pop();

        int sum = leftNode->frequency + rightNode->frequency;

        huffmanNode *newNode = new huffmanNode(L"", sum);

        newNode->left  = leftNode;
        newNode->right = rightNode;

        root = newNode;

        minHeap.push(newNode);
    }

    return root;
}



/**
 *  Display the huffman tree in in-order tree traversal format
 *
 *  @param      {huffmanNode*} pointer to the root node of the huffman tree
 *  @returns
 */
void displayTree(huffmanNode *root)
{
    if (!root)
        return;

    displayTree(root->left);
    std::wcout << root->data << " ";
    displayTree(root->right);
}