#ifndef fileManager_HPP
#define fileManager_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <functional>

namespace fs = std::filesystem;

class fileManager {
public:
    fileManager(const fs::path& huffPath, const fs::path& textPath);

    //file validation
    static fs::path createFileinDataDir(const fs::path& src, const std::string& extension);
    static fs::path moveFileToDataDir(const fs::path& src);
    static void FileExists(const fs::path& FilePath);
    static void checkExtension(const fs::path& filePath, const std::string& extension);

    //methods
    std::vector<char> getbuffer () const;
    void writeTohuffFile(const std::vector<bool>& bitstream, const std::unordered_map<char,int>& freqTable);

private:
    fs::path huffFilePath;
    fs::path textFilePath;
};

#endif // fileManager_HPP