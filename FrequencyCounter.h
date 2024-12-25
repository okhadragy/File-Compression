#include "HashMap.cpp"

using namespace std;

#ifndef FREQUENCY_COUNTER_H_
#define FREQUENCY_COUNTER_H_

class FrequencyCounter {

private:
    HashMap<char, int> frequencyMap;
public:
    const HashMap<char, int> &getFrequencyMap() const;
    void readFile(string fileName);
    FrequencyCounter(string fileName);
};

#endif  