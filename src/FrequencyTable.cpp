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
    for (auto src : m_frequencyMap) {
    std::cout << "char : ";
    if (src.first == '\n') std::cout << "\\n"; //new line
    else if (src.first == '\t') std::cout << "\\t";
    else std::cout << src.first;
    std::cout << ", Frequency : " << src.second << std::endl;
    }
}

std::unordered_map<char,int> FrequencyTable::getFrequencyMap() const{
    return m_frequencyMap;
};

void FrequencyTable::setFrequencyMap(const std::unordered_map<char,int>& freqMap) {
    m_frequencyMap = freqMap;
}