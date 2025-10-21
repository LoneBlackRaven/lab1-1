#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>

// ������� ��� ������� ������ �����
void clearInput();

// ������� ��� ����� ������ ����� � ���������
int inputInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min(), int maxVal = std::numeric_limits<int>::max());

// ������� ��� ����� �������� ����� � ���������
float inputFloat(const std::string& prompt, float minVal = -std::numeric_limits<float>::max(), float maxVal = std::numeric_limits<float>::max());

// ������� ��� ����� ������ � ������� getline
std::string inputString(const std::string& prompt);

// ������� ��� ����� �������� ��������
bool inputBool(const std::string& prompt);

// ������� ��� �����������
void logAction(const std::string& action);

// ������� ��� ���������� ������
std::vector<std::string> splitString(const std::string& str, char delimiter);

// ������� ��� ��������� �������� ������� � ���� ������
std::string getCurrentTime();

#endif // UTILS_H