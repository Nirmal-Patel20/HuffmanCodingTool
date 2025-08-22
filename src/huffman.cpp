#include "huffman.hpp"

void  huffman::compress(const std::filesystem::path& decompressedFile,const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, decompressedFile);
}

void huffman::decompress(const std::filesystem::path& compressedFile, const std::filesystem::path& outputFile) {
    fileManager fileManager(outputFile, compressedFile);
}