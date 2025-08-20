#include "huffman.hpp"

huffman::huffman() : huffman("data/decompressed.txt", "data/compressed.huff") {}

huffman::huffman(const std::string &inputFile, const std::string &outputFile)
    : m_inputFile(inputFile), m_outputFile(outputFile) {
}

void huffman::compress() {
    //compress process
}

void huffman::decompress() {
    //decompress process
}