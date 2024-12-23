#include "FrequencyCounter.h"

const unordered_map<char, int> &FrequencyCounter::getFrequencyMap() const {
    return frequencyMap;
}

void FrequencyCounter::readFile(string fileName) {
    char character;
    ifstream inputFile;

    inputFile.open(fileName, ios::in);
    if (!inputFile.is_open())
    {
        throw logic_error("Can't open the input file.");
    }

    if (inputFile.peek() == ifstream::traits_type::eof())
    {
        throw logic_error("The input file is empty.");
    }
    
    while(inputFile.get(character)){
        frequencyMap[character]++;
    }
    inputFile.close();
}

FrequencyCounter::FrequencyCounter(string fileName){
    readFile(fileName);
}

