#include <bits/stdc++.h>
#include "FrequencyCounter.cpp"
#include "pq.cpp"

using namespace std;
#ifndef HUFFMANCODING_HUFFER_H
#define HUFFMANCODING_HUFFER_H

class Huffman
{
private:
    class Node
    {
    public:
        char character;
        int frequency;
        Node *right;
        Node *left;
        Node(char character, int frequency) : character(character), frequency(frequency), right(0), left(0) {}
        ~Node()
        {
            delete left;
            delete right;
        }
    };

    Node *root;
    HashMap<char, string> codeMap;
    HashMap<string, char> deCodeMap;

    void constructTree(HashMap<char, int> frequencyMap);
    void encodeCharacters(Node *rootNode, string codeString);
    void constructCodeMap();
    void construct(string inputFile);
    void readFile(ifstream &inputStream, string &file, char &remainder);
    void encodeFile(ifstream &inputStream, string &encodedFile, char &remainder);
    void writeHeader(ofstream &outputStream, char remainder);
    void writeFile(ofstream &outputStream, string file);
    void readHeader(ifstream &inputStream);
    void readEncodedFile(ifstream &inputStream, string &file);
    void decodeFile(ifstream &inputStream, string &decodedFile);

public:
    Huffman();
    ~Huffman();
    void compressTofile(string inputFile, string outputFile);
    void decompressToFile(string inputFile, string outputFile);
};

#endif
