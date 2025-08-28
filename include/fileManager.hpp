#ifndef fileManager_HPP
#define fileManager_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <functional>
#include <map>

namespace fs = std::filesystem;

class fileManager {
public:
    fileManager(const fs::path& huffPath, const fs::path& textPath);

    //file validation
    static fs::path createFileinDataDir(const fs::path& src, const std::string& extension);
    static fs::path moveFileToDataDir(const fs::path& src);
    static void FileExists(const fs::path& FilePath);
    static void checkExtension(const fs::path& filePath, const std::string& extension);
    static void checkVersion(const fs::path& filePath, const std::string& version);

    //methods for compress file
    std::vector<char> getbuffer () const;
    std::string escapeChar(char c) const;
    void writeTohuffFile(const std::vector<bool>& bitstream, const std::map<char,int>& freqTable);

    //methods for decompress file
    char unescapeChar(const std::string& str) const;
    std::pair<std::map<char,int>, std::vector<bool>> readFromhuffFile();
    void writeTotextFile(const std::vector<char>& decodedChars);

private:
    fs::path huffFilePath;
    fs::path textFilePath;
};

#endif // fileManager_HPP