#include <iostream>
#include <fstream>
#include <cctype>
#include <filesystem>

struct FileStats {
    size_t fileSize = 0, lineCount = 0, wordCount = 0, charCount = 0;
    size_t alphaCount = 0, digitCount = 0, spaceCount = 0, specialCharCount = 0;
    std::string fileType, fileExtension;
};

void analyzeFile(const std::string& filename, FileStats& stats) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    stats.fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    char ch;
    bool inWord = false;
    size_t nonTextChars = 0;
    
    while (file.get(ch)) {
        unsigned char uch = static_cast<unsigned char>(ch);
        stats.charCount++;
        
        if (std::isalpha(uch)) stats.alphaCount++;
        else if (std::isdigit(uch)) stats.digitCount++;
        else if (std::isspace(uch)) {
            stats.spaceCount++;
            if (ch == '\n') stats.lineCount++;
            if (inWord) { stats.wordCount++; inWord = false; }
        } else {
            stats.specialCharCount++;
            if (uch < 32 && ch != '\n' && ch != '\t') nonTextChars++;
        }
        
        if (!std::isspace(uch)) inWord = true;
    }
    if (inWord) stats.wordCount++;
    
    stats.fileType = (nonTextChars > stats.charCount * 0.1) ? "Binary" : "Text";
    stats.fileExtension = std::filesystem::path(filename).extension().string();
}

void printStats(const FileStats& stats) {
    std::cout << "File Type: " << stats.fileType << "\nFile Extension: " << stats.fileExtension
              << "\nFile Size: " << stats.fileSize << " bytes\nTotal Lines: " << stats.lineCount
              << "\nTotal Words: " << stats.wordCount << "\nTotal Characters: " << stats.charCount
              << "\nAlphabetic Characters: " << stats.alphaCount << "\nNumeric Characters: " << stats.digitCount
              << "\nWhitespace Characters: " << stats.spaceCount << "\nSpecial Characters: " << stats.specialCharCount << '\n';
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    
    FileStats stats;
    analyzeFile(argv[1], stats);
    printStats(stats);
    return 0;
}
