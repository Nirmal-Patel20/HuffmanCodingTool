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
