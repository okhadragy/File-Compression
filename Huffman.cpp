#include "Huffman.h"
#include "FrequencyCounter.cpp"
#include "HashMap.cpp"


#define INTERNAL_NODE_CHARACTER char(128)
#define THE_EOF char(129)
#define HEADER_TEXT_SEPERATOR char(132)

int Huffman::myCompartor::operator()(Node *node1, Node *node2)
{
    return node1->frequency > node2->frequency;
}

void Huffman::constructTree(HashMap<char, int> frequencyMap)
{
    priority_queue<Node *, vector<Node *>, myCompartor> HufferQueue;
    Node *leftNode, *rightNode, *newNode;
    Pair<char, int>** table = frequencyMap.getTable();

    for (int i = 0; i < frequencyMap.getSize(); i++)
    {
        Pair<char, int>* current = table[i];
        
        while (current)
        {
            HufferQueue.push(new Node(current->key, current->value));
            current = current->next;
        }
    }
    
    HufferQueue.push(new Node(THE_EOF, 1));

    while (HufferQueue.size() != 1)
    {
        leftNode = HufferQueue.top();
        HufferQueue.pop();
        rightNode = HufferQueue.top();
        HufferQueue.pop();
        newNode = new Node(INTERNAL_NODE_CHARACTER, leftNode->frequency + rightNode->frequency);
        HufferQueue.push(newNode);
        newNode->left = leftNode;
        newNode->right = rightNode;
    }
    root = HufferQueue.top();
}

void Huffman::encodeCharacters(Node *rootNode, string codeString)
{

    if (!rootNode)
        return;
    if (rootNode->character != INTERNAL_NODE_CHARACTER)
    {
        codeMap[rootNode->character] = codeString;
    }

    encodeCharacters(rootNode->left, codeString + "0");
    encodeCharacters(rootNode->right, codeString + "1");
}

void Huffman::constructCodeMap()
{
    encodeCharacters(root, "");
}

void Huffman::readFile(ifstream &inputStream, string &file, char &remainder)
{
    char character;
    while (inputStream.get(character))
    {
        file += codeMap[character];
    }
    inputStream.close();
    file += codeMap[THE_EOF];

    // complete the last 8 bits
    remainder = 8 - file.size() % 8;
    for (int i = 0; i < remainder; ++i)
    {
        file += '0';
    }
}

void Huffman::encodeFile(ifstream &inputStream, string &encodedFile, char &remainder)
{
    string file;
    readFile(inputStream, file, remainder);
    stringstream stringStream(file);
    bitset<8> bits;
    while (stringStream >> bits)
    {
        char c = char(bits.to_ulong());
        encodedFile += c;
    }
}

void Huffman::writeHeader(ofstream &outputStream, char remainder)
{
    for (const auto &item : codeMap)
    {
        stringstream stringStream(item.second);
        bitset<8> bits;
        stringStream >> bits;
        char c = char(bits.to_ulong());
        outputStream << c << (char)item.second.size() << item.first;
    }
    
    outputStream << HEADER_TEXT_SEPERATOR << remainder;
}

void Huffman::writeFile(ofstream &outputStream, string file)
{
    for (int i = 0; i < file.size(); i++)
    {
        outputStream << file[i];
    }

    outputStream.flush();
    outputStream.close();
}

void Huffman::construct(string inputFile)
{
    FrequencyCounter f(inputFile);
    constructTree(f.getFrequencyMap());
    constructCodeMap();
}

void Huffman::compressTofile(string inputFile, string outputFile)
{
    construct(inputFile);
    string file;
    char remainder;
    ifstream inputStream;
    ofstream outputStream;

    outputStream.open(outputFile, ios::binary);
    inputStream.open(inputFile, ios::binary);
    if (!inputStream.is_open())
    {
        throw logic_error("Can't open the input file.");
    }
    if (!outputStream.is_open())
    {
        throw logic_error("Can't open the output file.");
    }

    if (inputStream.peek() == ifstream::traits_type::eof())
    {
        throw logic_error("The input file is empty.");
    }
    
    
    encodeFile(inputStream, file, remainder);
    writeHeader(outputStream, remainder);
    writeFile(outputStream, file);
}

void Huffman::readHeader(ifstream &inputStream)
{
    char codeChar, sizeChar, character;
    string code;
    inputStream.get(codeChar);
    while (codeChar != HEADER_TEXT_SEPERATOR)
    {   
        inputStream.get(sizeChar);
        inputStream.get(character);
        bitset<8> bits(codeChar);
        code = bits.to_string().substr((8-(int)sizeChar),8);
        deCodeMap[code] = character;
        inputStream.get(codeChar);
    }
}

void Huffman::readEncodedFile(ifstream &inputStream, string &file)
{
    char reminder, character;
    inputStream.get(reminder);

    while (inputStream.get(character))
    {
        bitset<8> bits(character);
        file += bits.to_string();
    }
    inputStream.close();
    file.erase((file.size() - 1) - reminder, file.size());
}

void Huffman::decodeFile(ifstream &inputStream, string &decodedFile)
{
    string file, code;

    readEncodedFile(inputStream, file);
    for (int i = 0; i < file.size(); i++)
    {
        code += file[i];
        if (deCodeMap.find(code) != deCodeMap.end())
        {
            decodedFile += deCodeMap[code];
            code = "";
        }
    }
}

void Huffman::decompressToFile(string inputFile, string outputFile)
{
    string file;
    ifstream inputStream;
    ofstream outputStream;
    outputStream.open(outputFile, ios::binary);
    inputStream.open(inputFile, ios::binary);

    if (!inputStream.is_open())
    {
        throw logic_error("Can't open the input file.");
    }
    if (!outputStream.is_open())
    {
        throw logic_error("Can't open the output file.");
    }

    if (inputStream.peek() == ifstream::traits_type::eof())
    {
        throw logic_error("The input file is empty.");
    }

    readHeader(inputStream);
    decodeFile(inputStream, file);
    writeFile(outputStream, file);
}
