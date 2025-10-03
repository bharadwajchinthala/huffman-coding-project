#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_SIZE 50  // maximum number of characters allowed

// Structure of a Huffman Tree node
struct HuffmanNode {
char symbol;          // character
int weight;           // frequency of the character
HuffmanNode *leftChild;   // left child
HuffmanNode *rightChild;  // right child
};

// Create a new node
HuffmanNode* createHuffmanNode(char symbol, int weight) {
HuffmanNode* newNode = new HuffmanNode;   // make new node
newNode->symbol = symbol;                 // set character
newNode->weight = weight;                 // set frequency
newNode->leftChild = NULL;                // no left child yet
newNode->rightChild = NULL;               // no right child yet
return newNode;                           // return new node
}

// Find two smallest frequency nodes
void getTwoLowestNodes(HuffmanNode* nodeList[], int currentSize, int &lowestIdx1, int &lowestIdx2) {
lowestIdx1 = -1;  // store index of smallest node
lowestIdx2 = -1;  // store index of second smallest node


for (int idx = 0; idx < currentSize; idx++) {
    if (nodeList[idx] != NULL) {
        // if first smallest not set or found smaller node
        if (lowestIdx1 == -1 || nodeList[idx]->weight < nodeList[lowestIdx1]->weight) {
            lowestIdx2 = lowestIdx1;   // shift old smallest to second
            lowestIdx1 = idx;          // update first smallest
        }
        // if second smallest not set or found smaller than second
        else if (lowestIdx2 == -1 || nodeList[idx]->weight < nodeList[lowestIdx2]->weight) {
            lowestIdx2 = idx;          // update second smallest
        }
    }
}


}

// Print Huffman codes using preorder traversal
void printHuffmanCodes(HuffmanNode* rootNode, string code) {
if (rootNode == NULL) return;  // stop if node is empty


// if it is a leaf node (real character)
if (rootNode->leftChild == NULL && rootNode->rightChild == NULL) {
    cout << rootNode->symbol << ": " << code << endl;  // print symbol with its code
}

// go left, add 0
printHuffmanCodes(rootNode->leftChild, code + "0");
// go right, add 1
printHuffmanCodes(rootNode->rightChild, code + "1");


}

int main() {
int charCount;                      // number of characters
char inputSymbols[MAX_SIZE];        // store characters
int frequencies[MAX_SIZE];          // store frequencies
HuffmanNode* nodeArray[MAX_SIZE];   // store nodes


// take number of characters
cout << "Enter number of input symbols: ";
cin >> charCount;

// take characters
cout << "Enter symbols: ";
for (int i = 0; i < charCount; i++) {
    cin >> inputSymbols[i];
}

// take frequencies
cout << "Enter corresponding frequencies: ";
for (int i = 0; i < charCount; i++) {
    cin >> frequencies[i];
}

// make nodes for each character
for (int i = 0; i < charCount; i++) {
    nodeArray[i] = createHuffmanNode(inputSymbols[i], frequencies[i]);
}

int activeNodes = charCount;  // total active nodes

// build the Huffman tree
while (activeNodes > 1) {
    int minIdx1, minIdx2;

    // find two nodes with smallest frequency
    getTwoLowestNodes(nodeArray, activeNodes, minIdx1, minIdx2);

    // store the two smallest nodes
    HuffmanNode* leftNode = nodeArray[minIdx1];
    HuffmanNode* rightNode = nodeArray[minIdx2];

    // make new node joining them
    HuffmanNode* mergedNode = createHuffmanNode('$', leftNode->weight + rightNode->weight);
    mergedNode->leftChild = leftNode;   // set left
    mergedNode->rightChild = rightNode; // set right

    // replace smallest node with new node
    nodeArray[minIdx1] = mergedNode;
    // move last node into second smallest place
    nodeArray[minIdx2] = nodeArray[activeNodes - 1];
    nodeArray[activeNodes - 1] = NULL;  // clear last spot

    activeNodes--; // reduce count
}

// final root node
HuffmanNode* root = nodeArray[0];

// print all Huffman codes
cout << "\nHuffman Codes (Preorder Traversal):\n";
printHuffmanCodes(root, "");

return 0;


}
