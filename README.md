# Huffman Coding Tool

## Structure

```
HuffmanCodingTool/
│
├── CMakeLists.txt                 # Main CMake build file
├── CMakePresets.json              # Presets for Debug/Release builds
├── include/
│   ├── FrequencyTable.hpp     # Helper: counts frequencies of characters 
│   ├── huffman.hpp            # Core Huffman tree functions
│   ├── node.hpp               # Tree node class/struct
│   ├── encoder.hpp            # Encoding logic
│   └── decoder.hpp            # Decoding logic
│
├── src/
│   ├── FrequencyTable.cpp
│   ├── main.cpp                   # CLI entry point
│   ├── huffman.cpp
│   ├── node.cpp
│   ├── encoder.cpp
│   └── decoder.cpp
│
├── data/
│   ├── sample.txt                 # Example input
│   └── compressed.bin             # Example output
│
├── .clang-format                  # Code formatting rules
├── .gitignore                     # Git ignores build/artifacts
└── README.md                      # Project description & usage

```
