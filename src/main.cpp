#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "UIHelper.hpp"
#include "huffman.hpp"

int main(int argc, char *argv[]) {

    std::string option = UIHelper::checkValidOptions(argc, argv);

    std::filesystem::path input_file;
    std::filesystem::path output_file;

    huffman fileCompressor;

    if (option == "--compress") {
        fileManager::checkExtension(fs::path(argv[2]), ".txt");
        input_file = fileManager::moveFileToDataDir(argv[2]);
        output_file = fileManager::createFileinDataDir(input_file, ".huff");

        fileCompressor.compress(input_file, output_file);
    } else if (option == "--decompress") {
        fileManager::checkExtension(fs::path(argv[2]), ".huff");
        input_file = fileManager::moveFileToDataDir(argv[2]);
        try {
            fileManager::checkVersion(input_file, "HUFF 1.0.0");
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
        output_file = fileManager::createFileinDataDir(input_file, ".txt");

        fileCompressor.decompress(input_file, output_file);
    }
}