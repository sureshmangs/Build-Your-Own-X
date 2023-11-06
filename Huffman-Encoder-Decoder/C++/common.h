#include <map>



// Used to represent the end of line
#define ENDOFLINE L"EOL"
// Used to represent the end of header in compressed file
#define ENDOFHEADER L"EOH"



class huffmanNode {
public:
    std::wstring data;
    int frequency;
    huffmanNode* left;
    huffmanNode* right;

    huffmanNode(std::wstring value, int freq)
    {
        data = value;
        frequency = freq;
        left = NULL;
        right = NULL;
    }
};



// Custom comparator class
class CompareHuffmanNode {
public:
    bool operator()(huffmanNode *a, huffmanNode *b)
    {
        if (a->frequency == b->frequency)
            return a->data > b->data;
        return a->frequency > b->frequency;
    }
};



// Function declarations for globally used functions
extern int countNumberOfBytes(std::string file);
extern huffmanNode* buildHuffmanTree(std::map <std::wstring, int> &frequencyMap);
extern void displayTree(huffmanNode *root);


// Globally used fields
extern bool displayData;