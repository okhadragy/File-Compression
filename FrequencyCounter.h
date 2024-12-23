#include <bits/stdc++.h>

using namespace std;

#ifndef FREQUENCY_COUNTER_H_
#define FREQUENCY_COUNTER_H_

class FrequencyCounter {

private:
    unordered_map<char,int> frequencyMap;
public:
    const unordered_map<char, int> &getFrequencyMap() const;
    void readFile(string fileName);
    FrequencyCounter(string fileName);
};

#endif  