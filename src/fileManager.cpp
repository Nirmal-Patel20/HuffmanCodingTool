#include "fileManager.hpp"

fileManager::fileManager(const fs::path& huffPath, const fs::path& textPath)
    : huffFilePath(huffPath), textFilePath(textPath) {}


void fileManager::FileExists(const fs::path& FilePath) {
    if(!fs::exists(FilePath)){
        throw std::runtime_error ("file does not exist: " + FilePath.string());
    }
}


