#ifndef MENU_H
#define MENU_H

#include "pipe.h"
#include "cs.h"
#include <vector>
#include <unordered_set>

// ������� ��� ����� ���� ������ �����
Pipe inputPipeData();

// ������� ��� ����� ���� ������ ������������� �������
Compress inputCompressData();

// ������� ��� ������ � �������
void displayAllPipes(const std::vector<Pipe>& pipes);
std::vector<int> findPipesByName(const std::vector<Pipe>& pipes, const std::string& name);
std::vector<int> findPipesByRepairStatus(const std::vector<Pipe>& pipes, bool repairStatus);
void batchEditPipes(std::vector<Pipe>& pipes, const std::unordered_set<int>& pipeIds);

// ������� ��� ������ � ��
void displayAllCompressStations(const std::vector<Compress>& stations);
std::vector<int> findStationsByName(const std::vector<Compress>& stations, const std::string& name);
std::vector<int> findStationsByUnusedPercentage(const std::vector<Compress>& stations, double minPercentage);

// ������� ��� ���������� � ��������
void saveData(const std::vector<Pipe>& pipes, const std::vector<Compress>& stations);
void loadData(std::vector<Pipe>& pipes, std::vector<Compress>& stations);

// �������� ������� ����
void Menu();

#endif // MENU_H