#include <iostream>
#include <fstream>
#include <httplib.h>
#include <filesystem>

namespace fs = std::filesystem;

void uploadFile(const std::string& url, const std::string& filePath) {
    httplib::Client cli("0.0.0.0", 8080);
    std::ifstream file(filePath, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    std::vector<char> fileContent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    httplib::MultipartFormDataItems items = {
        {"files", std::string(fileContent.begin(), fileContent.end()), fs::path(filePath).filename().string(), "application/octet-stream"}
    };

    auto res = cli.Post("/upload", items);

    if (res && res->status == 200) {
        std::cout << "File " << filePath << " uploaded successfully." << std::endl;
    } else {
        std::cerr << "Error: File upload failed for " << filePath << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <directory_or_file>" << std::endl;
        return 1;
    }

    std::string item = argv[1];

    if (fs::is_regular_file(item)) {
        uploadFile("http://localhost:8080/upload", item);
    } else if (fs::is_directory(item)) {
        for (const auto& entry : fs::directory_iterator(item)) {
            if (fs::is_regular_file(entry.path())) {
                uploadFile("http://localhost:8080/upload", entry.path().string());
            } else if (fs::is_directory(entry.path())) {
                std::cout << "Skipping " << entry.path() << "/" << std::endl;
            } else {
                std::cout << "Skipping " << entry.path() << std::endl;
            }
        }
    } else {
        std::cerr << "Error: Invalid path " << item << std::endl;
        return 1;
    }

    return 0;
}
