#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>

void runCommand(const std::string& command, const std::vector<std::string>& args) {
    // Create a command string from the provided arguments
    std::string fullCommand = command;
    for (const auto& arg : args) {
        fullCommand += " " + arg;
    }

    // Measure the start time
    auto start = std::chrono::high_resolution_clock::now();

    // Run the command using WinAPI ShellExecute
    std::wstring commandWStr(fullCommand.begin(), fullCommand.end());
    ShellExecuteW(NULL, L"open", commandWStr.c_str(), NULL, NULL, SW_SHOWNORMAL);

    // Measure the end time
    auto end = std::chrono::high_resolution_clock::now();
    
    // Calculate the duration
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: timeit <command> [args...]" << std::endl;
        return 1;
    }

    // The first argument is the command to run
    std::string command = argv[1];

    // Collect all remaining arguments as the command's arguments
    std::vector<std::string> args;
    for (int i = 2; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    // Run the command and measure the time
    runCommand(command, args);

    return 0;
}
