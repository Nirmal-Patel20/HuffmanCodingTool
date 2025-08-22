#include "huffman.hpp"

void  huffman::compress(const std::filesystem::path& decompressedFile,const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, decompressedFile);

    std::vector<char> buffer = fileManager.getbuffer();//build buffer

    FreqTable.buildUsingBuffer(buffer);//build FrequencyTable
}

void huffman::decompress(const std::filesystem::path& compressedFile, const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, compressedFile);
}