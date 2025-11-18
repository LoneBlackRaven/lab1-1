#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

//очистака ввода
void clearInput();

//целое число
int inputInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min(), int maxVal = std::numeric_limits<int>::max());

//дробное число
float inputFloat(const std::string& prompt, float minVal = -std::numeric_limits<float>::max(), float maxVal = std::numeric_limits<float>::max());

//строка
std::string inputString(const std::string& prompt);

//бул значение
bool inputBool(const std::string& prompt);

//логирование
void logAction(const std::string& action);

//разделение строки
std::vector<std::string> splitString(const std::string& str, char delimiter);

//время
std::string getCurrentTime();

#endif // UTILS_H