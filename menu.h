#ifndef MENU_H
#define MENU_H

#include "pipe.h"
#include "cs.h"
#include <vector>
#include <unordered_set>

// Функция для ввода всех данных трубы
Pipe inputPipeData();

// Функция для ввода всех данных компрессорной станции
Compress inputCompressData();

// Функции для работы с трубами
void displayAllPipes(const std::vector<Pipe>& pipes);
std::vector<int> findPipesByName(const std::vector<Pipe>& pipes, const std::string& name);
std::vector<int> findPipesByRepairStatus(const std::vector<Pipe>& pipes, bool repairStatus);
void batchEditPipes(std::vector<Pipe>& pipes, const std::unordered_set<int>& pipeIds);

// Функции для работы с КС
void displayAllCompressStations(const std::vector<Compress>& stations);
std::vector<int> findStationsByName(const std::vector<Compress>& stations, const std::string& name);
std::vector<int> findStationsByUnusedPercentage(const std::vector<Compress>& stations, double minPercentage);

// Функции для сохранения и загрузки
void saveData(const std::vector<Pipe>& pipes, const std::vector<Compress>& stations);
void loadData(std::vector<Pipe>& pipes, std::vector<Compress>& stations);

// Основная функция меню
void Menu();

#endif // MENU_H