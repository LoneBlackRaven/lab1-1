#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

// Функция для очистки потока ввода
void clearInput();

// Функция для ввода целого числа с проверкой
int inputInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min(), int maxVal = std::numeric_limits<int>::max());

// Функция для ввода дробного числа с проверкой
float inputFloat(const std::string& prompt, float minVal = -std::numeric_limits<float>::max(), float maxVal = std::numeric_limits<float>::max());

// Функция для ввода строки с помощью getline
std::string inputString(const std::string& prompt);

// Функция для ввода булевого значения
bool inputBool(const std::string& prompt);

// Функция для логирования
void logAction(const std::string& action);

// Функция для разделения строки
std::vector<std::string> splitString(const std::string& str, char delimiter);

// Функция для получения текущего времени в виде строки
std::string getCurrentTime();

#endif // UTILS_H