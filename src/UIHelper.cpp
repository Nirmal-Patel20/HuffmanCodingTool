#include "UIHelper.hpp"

const char *UIHelper::get_exe_name(const char *path) {
    const char *slash = strrchr(path, '/'); // Unix
    if (!slash)
        slash = strrchr(path, '\\'); // Windows
    return slash ? slash + 1 : path;
}

std::string UIHelper::checkValidOptions(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage:\n";
        std::cerr << "  " << get_exe_name(argv[0]) << " --compress <input>\n";
        std::cerr << "  " << get_exe_name(argv[0]) << " --decompress <input>\n";
        exit(EXIT_FAILURE);
    }

    std::string option = argv[1];
    if (option != "--compress" && option != "--decompress") {
        std::cerr << "Invalid option: " << option << std::endl;
        std::cerr << "Available options are: --compress, --decompress" << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
        fileManager::FileExists(argv[2]);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Please provide a valid file path." << std::endl;
        exit(EXIT_FAILURE);
    }
    return option;
}