#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <filesystem>
#include <iostream>

class huffman {
  public:
    // constructor and distructor
    huffman(); // default parameter
    huffman(const std::string &inputFile, const std::string &outputFile);

    // public API
    void compress();
    void decompress();

  private:
    std::string m_inputFile;
    std::string m_outputFile;

};

#endif // HUFFMAN_HPP