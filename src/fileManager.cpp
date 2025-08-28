#include "fileManager.hpp"

fileManager::fileManager(const fs::path &huffPath, const fs::path &textPath)
    : huffFilePath(huffPath), textFilePath(textPath) {}

void fileManager::FileExists(const fs::path &FilePath) {
    if (!fs::exists(FilePath)) {
        throw std::runtime_error("file does not exist: " + FilePath.string());
    }
}

fs::path fileManager::createFileinDataDir(const fs::path &src, const std::string &extension) {
    fs::path dataDir = "data";
    if (!fs::exists(dataDir)) {
        fs::create_directory(dataDir);
    }

    fs::path newFile = dataDir / (src.stem().string() + extension);
    int suffixCount = 1;
    while (fs::exists(newFile)) {
        newFile =
            dataDir / (src.stem().string() + "(" + std::to_string(suffixCount++) + ")" + extension);
    }
    std::ofstream out(newFile);

    return newFile;
}

fs::path fileManager::moveFileToDataDir(const fs::path &src) {
    if (src.parent_path().filename() != "data") {
        fs::path buildDir = "data";
        if (!fs::exists(buildDir)) { // build data folder if does not exits
            fs::create_directory(buildDir);
        }

        fs::path newLocation = buildDir / src.filename();

        if (fs::exists(newLocation)) {
            fs::remove(newLocation); // remove if file already exists in data dir
        }

        fs::rename(src, newLocation);
        return newLocation;
    }
    return src; // if already in data dir, return the same path
}

void fileManager::checkExtension(const fs::path &filePath, const std::string &extension) {
    if (filePath.extension() != extension) {
        throw std::runtime_error("Invalid file extension: " +
                                 filePath.filename().extension().string());
    }
}

std::vector<char> fileManager::getbuffer() const {
    std::ifstream inFile(textFilePath, std::ios::binary);
    std::vector<char> buffer;

    if (inFile) {
        char c;
        while (inFile.get(c)) {
            if (c == '\r')
                continue; // skip
            buffer.push_back(c);
        }
    }

    return buffer;
}

std::string fileManager::escapeChar(char c) const {
    switch (c) {
    case '\n':
        return "\\n";
    case '\t':
        return "\\t";
    case '\\':
        return "\\\\";
    case '<':
        return "\\<";
    case '>':
        return "\\>";
    case '|':
        return "\\|";
    default:
        return std::string(1, c);
    }
}

void fileManager::writeTohuffFile(const std::vector<bool> &bitstream,
                                  const std::map<char, int> &freqTable) {
    std::ofstream outfile(huffFilePath, std::ios::binary);

    // Header
    std::string header = "HUFF 1.0.0\n";
    outfile.write(header.data(), header.size());

    for (const auto &[symbol, freq] : freqTable) {
        std::string entry = escapeChar(symbol) + "<" + std::to_string(freq) + "|";
        outfile.write(entry.data(), entry.size());
    }

    outfile.write("\n", 1);
    std::string bitstreamSize = std::to_string(bitstream.size()) + "\n";
    outfile.write(bitstreamSize.data(), bitstreamSize.size());

    // convert bitstream to byte and write them into file
    std::vector<unsigned char> bytes;
    unsigned char byte = 0;
    int bitcount = 0;

    for (const auto &bit : bitstream) {
        byte = (byte << 1) | bit; // shitf to left then OR opration
        ++bitcount;

        if (bitcount == 8) {
            bytes.push_back(byte);
            byte = 0;
            bitcount = 0;
        }
    }

    if (bitcount > 0) {
        byte <<= (8 - bitcount); // pad with zero
        bytes.push_back(byte);
    }

    outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
}

void fileManager::checkVersion(const fs::path &filePath, const std::string &version) {
    std::ifstream inFile(filePath);
    std::string fileVersion;

    if (inFile) {
        std::getline(inFile, fileVersion);

        if (fileVersion.empty()) {
            throw std::runtime_error("File is empty or corrupted: " + filePath.string());
        } else if (fileVersion.find("HUFF") == std::string::npos) {
            throw std::runtime_error("File is not compressed by this tool: " + filePath.string());
        } else if (fileVersion != version) {
            throw std::runtime_error("Invalid file version: " + fileVersion +
                                     " expected: " + version);
        }
    }
}

char fileManager::unescapeChar(const std::string &str) const {
    if (str == "\\n")
        return '\n';
    if (str == "\\t")
        return '\t';
    if (str == "\\\\")
        return '\\';
    if (str == "\\<")
        return '<';
    if (str == "\\>")
        return '>';
    if (str == "\\|")
        return '|';
    return str[0]; // Return the first character for all other cases
}

std::pair<std::map<char, int>, std::vector<bool>> fileManager::readFromhuffFile() {
    std::pair<std::map<char, int>, std::vector<bool>> freqAndBits;

    std::ifstream infile(huffFilePath, std::ios::binary);

    std::string line;

    // Skip the first line
    std::getline(infile, line);

    // Read the second line (contains the freq table)
    if (!std::getline(infile, line)) {
        throw std::runtime_error("file is empty or corrupted: " + huffFilePath.string());
    }

    std::istringstream iss(line);
    std::string token;

    while (std::getline(iss, token, '|')) { // Split by '|'

        if (token.empty())
            continue;

        std::istringstream tokenStream(token);
        std::string symbolStr, freqStr;

        if (std::getline(tokenStream, symbolStr, '<') &&
            std::getline(tokenStream, freqStr)) { // Read rest of token as frequency
            int freq = std::stoi(freqStr);
            char symbol = unescapeChar(symbolStr);
            freqAndBits.first[symbol] = freq; // Store frequency
        }
    }

    // Read the third line (contains the bitstream size)
    std::getline(infile, line);
    int totalBits = std::stoi(line);

    // Read the remaining bits
    char byte;
    while (infile.get(byte)) {
        for (int i = 7; i >= 0; --i) {
            freqAndBits.second.push_back((byte >> i) & 1);
        }
    }

    // Trim the bitstream to the correct size
    freqAndBits.second.resize(totalBits);

    return freqAndBits;
}

void fileManager::writeTotextFile(const std::vector<char> &decodedChars) {
    std::ofstream outfile(textFilePath, std::ios::binary);

    outfile.write(decodedChars.data(), decodedChars.size());
}
