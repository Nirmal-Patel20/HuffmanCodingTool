# 🌳 Huffman Coding – C++ Implementation

This project is a C++ implementation of Huffman Coding, a lossless data compression algorithm. It allows you to compress and decompress text files by generating optimal variable-length codes based on character frequency. The tool supports building Huffman Trees, encoding text into binary format, decoding compressed data back to its original form, and analyzing compression efficiency.

---

## 📌 Purpose

The purpose of this project was to take a break from my previous OOP-heavy projects and build something more focused on algorithms. I wanted a project that uses lighter OOP principles while emphasizing algorithmic logic, which led me to implement Huffman Coding.

---

## ✅ Features

- **Lossless Compression & Decompression** - Implements Huffman Coding to reduce file size without losing data.

- **Huffman Tree Construction** - Dynamically builds optimal prefix trees based on character frequency.

- **Encoding & Decoding** - Converts text into binary representation and restores it to its original form.

- **Frequency Table Analysis** - Displays character frequencies used during compression.

- **Command-line Arguments** - Accepts input/ output file paths and operation mode (compress or decompress) via arguments.

- **File Validation** - Ensures valid file types (e.g., . txt for compression) before processing.

- **Version & Signature Verification** - Checks that the compressed file was created by the correct version of this tool before decompression

- **Customizable Input** - Works with plain text files containing various characters (including spaces and punctuation).

---

## 📁 Project Structure

```
HuffmanCodingTool/
|
├── data/
│   ├── sample.txt                 # Example input
│   └── compressed.bin             # Example output
│
├── include/
│   ├── fileManager.hpp        # File management utilities
│   ├── FrequencyTable.hpp     # Helper: counts frequencies of characters
│   ├── huffman.hpp            # Core Huffman tree functions
│   └── UIHelper.hpp           # User interface helper functions
│
├── src/
│   ├── fileManager.cpp
│   ├── FrequencyTable.cpp
│   ├── huffman.cpp
│   ├── main.cpp                   # CLI entry point
│   └── UIHelper.cpp
│
├── .clang-format                  # Code formatting rules
├── CMakeLists.txt                 # Main CMake build file
├── CMakePresets.json              # Presets for Debug/Release builds
├── .gitignore                     # Git ignores build/artifacts
├── LICENSE                        # License information
└── README.md                      # Project description & usage

```

---

## ⚒️ How to Build using Cmake(Linux/macOS/Window)(Recommended)

```bash
git clone https://github.com/Nirmal-Patel20/HuffmanCodingTool.git
cd HuffmanCodingTool
cmake --preset ninja-release
cmake --build build/ninja-release
```
> [!NOTE]
> This command builds the project using the Ninja generator in release mode and works correctly across different platforms.
---

## 🏃 How to Run

After building the project, you can run the HuffmanCodingTool executable with the following command with command line arguments:

```bash
.\build\ninja-release\HuffmanCodingTool.exe <operation> <input_file>
```
> [!NOTE]
> Replace `<operation>` with either `--compress` or `--decompress`, and provide the appropriate file paths for `<input_file>` and the program will generate the output file automatically.

or you can simply use the given sample files in the `data` folder.

### compression
```bash
.\build\ninja-release\HuffmanCodingTool.exe --compress "data/sample.txt"
```

### decompression
```bash
.\build\ninja-release\HuffmanCodingTool.exe --decompress "data/sample.huff"
```

---

## 🏢 How the Program Works

1. ### 📝 Overview
- The program accepts command-line arguments to specify whether to compress or decompress a file.
- It uses Huffman coding for lossless compression, creating a frequency table and building a Huffman tree for encoding.
- The encoded data and metadata (e.g., frequency table, version) is then written to a binary file, which can be decompressed later using the same tool.
- For decompression, the tool reads the binary file, reconstructs the Huffman tree, and decodes the data back to its original form.

2. ### 🗂 Architecture

- The program is structured into several modules, each responsible for a specific aspect of the functionality:
  - **File Management**: Handles reading from and writing to files.
  - **Frequency Table**: Computes the frequency of each character in the input text.
  - **Huffman Coding**: Implements the Huffman algorithm for encoding, decoding, building the Huffman tree with priority queues.
  - **UIHelper**: Manages user interactions and command-line arguments.

3. ### 💾 Data Handling

- The program uses a binary format for storing compressed data, which includes:
  - **Header**: Contains metadata such as the version, original file size, and frequency table.
  - **Compressed Data**: The actual Huffman-encoded data.
- During compression, the program builds a frequency table and a Huffman tree, then encodes the input data using the tree.
- During decompression, the program reconstructs the Huffman tree from the frequency table and decodes the compressed data back to its original form.

4. ### ⚠️ Error Handling

- The program includes error handling mechanisms to manage various issues that may arise during file operations, such as:
  - **File Not Found**: If the input file does not exist, an error message is displayed, and the program exits gracefully.
  - **Read/Write Errors**: Any errors encountered while reading from or writing to files are caught and reported to the user.
  - **Invalid Input**: The program checks for valid command-line arguments and provides usage instructions if the input is incorrect, including checking the file extension.
  > [!NOTE]
  > there is only one function which throw runtime error but it not handled properly. sorry for that.

5. ### 🖥 Program Flow

- The program starts by parsing command-line arguments to determine the operation (compress or decompress) and the input file.
- It then initializes the necessary components, such as the file manager, frequency table, and Huffman coding modules.
- For compression:
  1. The program reads the input file and builds a frequency table.
  2. It constructs a Huffman tree using the frequency table and generates the Huffman codes.
  3. The input data is encoded using the Huffman codes and written to a binary output file.
- For decompression:
  1. The program reads the binary input file and reconstructs the Huffman tree from the stored frequency table.
  2. It decodes the compressed data using the Huffman tree and writes the original data to a new output file.
- Throughout the process, the program handles errors and provides feedback to the user.

## 🧠 Concepts Practiced

- Command-line argument parsing
- File I/O operations
- Data structures (trees, priority queues)
- Huffman coding algorithm
- Error handling
- Modular programming and separation of concerns

## 🤯 Challenges Faced

- The original structure was mix of file writing, Huffman coding logic and testing(which i removed from the final version) making it hard to maintain.
- The final program use `std::map` for the frequency table but before it was using `std::unordered_map`, which was causing misbehavior in huffman tree construction as there was no fix order in both operations(e.g., compress,decompress).
- At the end, i used `clang-format` to ensure consistent code formatting but somehow it broke the code so i had to fix it manually.
- This project took longer than expected due to the complexity of the Huffman coding algorithm and the need for thorough testing.

## 📢 Status
> Project completed as a learning exercise. In the future, I may turn this project into a GUI application.

## 🚓 License

This project is licensed under the [MIT License](LICENSE).

## 🧑‍💻 Author
- Nirmal Patel — Aspiring C++ developer working on real-world practice projects.