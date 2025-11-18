#include "utils.h"
#include <iostream>
#include <sstream>

//очисткa потока ввода
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//ввод целого числа
int inputInt(const std::string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < minVal || value > maxVal) {
            std::cout << "Error! Write correct data." << std::endl;
            logAction("INPUT ERROR: Invalid integer input - prompt: " + prompt);
            clearInput();
        }
        else {
            clearInput();
            logAction("INPUT: Integer input - prompt: '" + prompt + "', value: " + std::to_string(value));
            return value;
        }
    }
}

//ввод дробного числа
float inputFloat(const std::string& prompt, float minVal, float maxVal) {
    float value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < minVal || value > maxVal) {
            std::cout << "Error! Write correct data." << std::endl;
            logAction("INPUT ERROR: Invalid float input - prompt: " + prompt);
            clearInput();
        }
        else {
            clearInput();
            logAction("INPUT: Float input - prompt: '" + prompt + "', value: " + std::to_string(value));
            return value;
        }
    }
}

//ввод строки
std::string inputString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    logAction("INPUT: String input - prompt: '" + prompt + "', value: '" + value + "'");
    return value;
}

//ввод булевого значения
bool inputBool(const std::string& prompt) {
    while (true) {
        std::string input = inputString(prompt + " (0 - no, 1 - yes): ");
        if (input == "0") {
            logAction("INPUT: Boolean input - prompt: '" + prompt + "', value: false");
            return false;
        }
        if (input == "1") {
            logAction("INPUT: Boolean input - prompt: '" + prompt + "', value: true");
            return true;
        }
        std::cout << "Error! Write 0 or 1." << std::endl;
        logAction("INPUT ERROR: Invalid boolean input - prompt: " + prompt + ", value: " + input);
    }
}

//получениe текущего времени
std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;

    //localtime
#ifdef _WIN32
    struct tm timeinfo;
    localtime_s(&timeinfo, &time_t);
    ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
#else
    struct tm* timeinfo = localtime(&time_t);
    ss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
#endif

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    ss << "." << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

//логирования
void logAction(const std::string& action) {
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << "[" << getCurrentTime() << "] " << action << std::endl;
        logFile.close();
    }
}

//разделения строки
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}