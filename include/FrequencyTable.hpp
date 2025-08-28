#ifndef FREQUENCYTABLE_HPP
#define FREQUENCYTABLE_HPP

#include <iostream>
#include <vector>
#include <map>

class FrequencyTable {
    public :
    
    //constructor and destructor
    FrequencyTable() = default;
    ~FrequencyTable() = default;

    void buildUsingBuffer(const std::vector<char>& buffer);
    void addFrequency(char c);
    int getFrequency(char c) const;
    void showFrequencyTable() const;
    std::map<char,int> getFrequencyMap() const;
    void setFrequencyMap(const std::map<char,int>& freqMap);

    private:

    std::map<char,int> m_frequencyMap;
};

#endif // FREQUENCYTABLE_HPP