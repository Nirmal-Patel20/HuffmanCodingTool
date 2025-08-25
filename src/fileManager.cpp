#include "fileManager.hpp"

fileManager::fileManager(const fs::path& huffPath, const fs::path& textPath)
    : huffFilePath(huffPath), textFilePath(textPath) {}


void fileManager::FileExists(const fs::path& FilePath) {
    if(!fs::exists(FilePath)){
        throw std::runtime_error ("file does not exist: " + FilePath.string());
    }
}

fs::path fileManager::createFileinDataDir(const fs::path& src, const std::string& extension) {
    fs::path dataDir = "data";
    if(!fs::exists(dataDir)){
        fs::create_directory(dataDir);
    }

    fs::path newFile = dataDir / (src.stem().string() + extension);
    int suffixCount = 1;
    while(fs::exists(newFile)){
        newFile = dataDir / (src.stem().string() + "("+ std::to_string(suffixCount++) + ")" + extension);
    }
    std::ofstream out (newFile);

    return newFile;
}

fs::path fileManager::moveFileToDataDir(const fs::path& src) {
    if(src.parent_path().filename() != "data"){
        fs::path buildDir = "data";
        if (!fs::exists(buildDir)) { //build data folder if does not exits
            fs::create_directory(buildDir);
        }

        fs::path newLocation = buildDir / src.filename();

        if(fs::exists(newLocation)){
            fs::remove(newLocation); //remove if file already exists in data dir
        }

        fs::rename(src, newLocation);
        return newLocation;
    }
    return src; //if already in data dir, return the same path
}


void fileManager::checkExtension(const fs::path& filePath, const std::string& extension) {
    if (filePath.extension() != extension) {
        throw std::runtime_error("Invalid file extension: " + filePath.filename().extension().string());
    }
}

std::vector<char> fileManager::getbuffer() const {
    std::ifstream inFile(textFilePath, std::ios::binary);
    std::vector<char> buffer;

    if(inFile){
        char c;
        while(inFile.get(c)){
            if(c == '\r') continue; //skip 
            buffer.push_back(c);
        }
    }
    
    return buffer;
}

void fileManager::writeTohuffFile(const std::vector<bool>& bitstream, const std::unordered_map<char,int>& freqTable){
    std::ofstream outfile(huffFilePath);

    //magic number
    outfile << "HUFF 1.0.0" << std::endl;

    //write frequency table
    for(const auto& [symbol,freq] : freqTable){
        outfile << (symbol == '\n' ? "\\n" : std::string(1,symbol)) << "," << freq << ".";
    }

    outfile << std::endl;
    outfile << bitstream.size() << std::endl;

    //convert bitstream to byte and write them into file
    unsigned char byte = 0;
    int bitcount = 0;

    for(const auto& bit : bitstream){
        byte = (byte << 1) | bit; //shitf to left then OR opration
        ++bitcount;

        if(bitcount == 8){
            outfile.put(byte);
            byte = 0;
            bitcount = 0;
        }
    }

    if(bitcount > 0){
        byte <<= (8 - bitcount); //pad with zero
        outfile.put(byte);
    }
    
}
