#include <iostream>
#include <cstring>
#include <filesystem>
#include <fstream>

#include "huffman.hpp"
#include "UIHelper.hpp"


int main(int argc, char* argv[]) {

    std::string option = UIHelper::checkValidOptions(argc, argv);

    std::filesystem::path input_file;
    std::filesystem::path output_file;


    huffman fileCompressor;

    if(option == "--compress"){
        input_file = fileManager::moveFileToDataDir(argv[2]);
        output_file = fileManager::createFileinDataDir(input_file,".huff");

        fileCompressor.compress(input_file, output_file);
    } else if(option == "--decompress"){
        input_file = fileManager::moveFileToDataDir(input_file);
        output_file = fileManager::createFileinDataDir(input_file,".txt");

        fileCompressor.decompress(input_file, output_file);
    }
}