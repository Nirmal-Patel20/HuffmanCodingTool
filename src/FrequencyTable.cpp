#include "FrequencyTable.hpp"

void FrequencyTable::buildUsingBuffer(const std::vector<char>& buffer){
    for(const char& c : buffer){
        ++m_frequencyMap[c];
    }
}

void FrequencyTable::addFrequency(char c){
    ++m_frequencyMap[c];
}

int FrequencyTable::getFrequency(char c) const {
    auto it = m_frequencyMap.find(c);
    return (it != m_frequencyMap.end()) ? it->second : 0;
}

void FrequencyTable::showFrequencyTable() const {
    for(auto src : m_frequencyMap){
        std::cout << "char : " << src.first << " ,Frequency : " << src.second << std::endl;
    }
}