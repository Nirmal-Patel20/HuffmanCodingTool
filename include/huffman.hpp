#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <filesystem>
#include <iostream>

#include "fileManager.hpp"
#include "FrequencyTable.hpp"

//Node Structure
struct Node {
  Node(char c, int freq) : symbol(c), frequency(freq), left(nullptr), right(nullptr) {};
  Node(Node* l, Node* r) :  symbol('\0'), frequency(l->frequency + r->frequency), left(l), right(r) {};

  //Member
  char symbol;
  int frequency;
  Node* left;
  Node* right;
};

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
  Node* root;

};

#endif // HUFFMAN_HPP