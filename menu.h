#ifndef MENU_H
#define MENU_H

#include "pipe.h"
#include "cs.h"
#include <vector>
#include <unordered_set>
#include <map>
#include "connection.h"

// Функция для ввода всех данных трубы
Pipe inputPipeData();

// Функция для ввода всех данных компрессорной станции
Compress inputCompressData();

// Функции для работы с трубами
void displayAllPipes(const std::map<int, Pipe>& pipes);
std::vector<int> findPipesByName(const std::map<int, Pipe>& pipes, const std::string& name);
std::vector<int> findPipesByRepairStatus(const std::map<int, Pipe>& pipes, bool repairStatus);
void batchEditPipes(std::map<int, Pipe>& pipes, const std::unordered_set<int>& pipeIds);

// Функции для работы с КС
void displayAllCompressStations(const std::map<int, Compress>& stations);
std::vector<int> findStationsByName(const std::map<int, Compress>& stations, const std::string& name);
std::vector<int> findStationsByUnusedPercentage(const std::map<int, Compress>& stations, double minPercentage);

// Функции для соединений
void createConnection(std::map<int, Pipe>& pipes, std::map<int, Compress>& stations, std::vector<Connection>& connections);
void displayConnections(const std::vector<Connection>& connections, const std::map<int, Pipe>& pipes, const std::map<int, Compress>& stations);
void deleteConnection(std::vector<Connection>& connections);

// Функция топологической сортировки
void topologicalSort(const std::vector<Connection>& connections, const std::map<int, Compress>& stations);

// Функции для сохранения и загрузки
void saveData(const std::map<int, Pipe>& pipes, const std::map<int, Compress>& stations, const std::vector<Connection>& connections);
void loadData(std::map<int, Pipe>& pipes, std::map<int, Compress>& stations, std::vector<Connection>& connections, int& nextPipeId, int& nextStationId);

// Основная функция меню
void Menu();

#endif // MENU_H