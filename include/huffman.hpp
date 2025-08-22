#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <filesystem>
#include <iostream>

#include "fileManager.hpp"
#include "FrequencyTable.hpp"

class huffman {
public:

  // Compress a file into a .huff file
  // If outputPath is empty, create "compressed.huff" in current directory
  void compress(const std::filesystem::path& decompressedFile, const std::filesystem::path& outputFile);

  // Decompress a .huff file back to original text
  // If outputPath is empty, remove ".huff" and restore ".txt" in current directory
  void decompress(const std::filesystem::path& compressedFile, const std::filesystem::path& outputFile);

  private:

  FrequencyTable FreqTable;
};

#endif // HUFFMAN_HPP