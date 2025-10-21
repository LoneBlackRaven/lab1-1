#include "menu.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

// Функция для ввода всех данных трубы
Pipe inputPipeData() {
    std::cout << "=== Enter pipe data ===" << std::endl;
    std::string name = inputString("Enter pipe name: ");
    float length = inputFloat("Enter pipe length (km): ", 0.0f);
    int diametr = inputInt("Enter pipe diameter (mm): ", 1);
    bool repair = inputBool("Is pipe on repair?");

    Pipe pipe(name, length, diametr, repair);
    logAction("PIPE CREATED - ID: " + std::to_string(pipe.getId()) +
        ", Name: '" + name + "', Length: " + std::to_string(length) +
        "km, Diameter: " + std::to_string(diametr) + "mm, Repair: " +
        (repair ? "yes" : "no"));
    return pipe;
}

// Функция для ввода всех данных компрессорной станции
Compress inputCompressData() {
    std::cout << "=== Enter CS data ===" << std::endl;
    std::string name = inputString("Enter CS name: ");
    int count = inputInt("Enter quantity of enterprises: ", 1);
    int count_working = inputInt("Enter quantity of working enterprises: ", 0, count);
    std::string classification = inputString("Enter classification: ");
    bool working = inputBool("Is CS working?");

    Compress compress(name, count, count_working, classification, working);
    logAction("STATION CREATED - ID: " + std::to_string(compress.getId()) +
        ", Name: '" + name + "', Total: " + std::to_string(count) +
        ", Working: " + std::to_string(count_working) +
        ", Classification: '" + classification + "', Working: " +
        (working ? "yes" : "no"));
    return compress;
}

// Функция для отображения всех труб
void displayAllPipes(const std::vector<Pipe>& pipes) {
    if (pipes.empty()) {
        std::cout << "No pipes available." << std::endl;
        logAction("DISPLAY: No pipes to display");
        return;
    }

    logAction("DISPLAY: Showing " + std::to_string(pipes.size()) + " pipes");
    for (const auto& pipe : pipes) {
        pipe.display();
        std::cout << std::endl;
    }
}

// Функция для поиска труб по имени
std::vector<int> findPipesByName(const std::vector<Pipe>& pipes, const std::string& name) {
    std::vector<int> result;
    for (const auto& pipe : pipes) {
        if (pipe.getName().find(name) != std::string::npos) {
            result.push_back(pipe.getId());
        }
    }
    logAction("SEARCH PIPES BY NAME: '" + name + "' - Found " + std::to_string(result.size()) + " pipes");
    return result;
}

// Функция для поиска труб по статусу ремонта
std::vector<int> findPipesByRepairStatus(const std::vector<Pipe>& pipes, bool repairStatus) {
    std::vector<int> result;
    for (const auto& pipe : pipes) {
        if (pipe.getRepair() == repairStatus) {
            result.push_back(pipe.getId());
        }
    }
    logAction("SEARCH PIPES BY REPAIR STATUS: " + std::string(repairStatus ? "in repair" : "not in repair") +
        " - Found " + std::to_string(result.size()) + " pipes");
    return result;
}

// Функция для пакетного редактирования труб
void batchEditPipes(std::vector<Pipe>& pipes, const std::unordered_set<int>& pipeIds) {
    if (pipeIds.empty()) {
        std::cout << "No pipes selected for editing." << std::endl;
        logAction("BATCH EDIT: No pipes selected");
        return;
    }

    logAction("BATCH EDIT: Starting batch edit for " + std::to_string(pipeIds.size()) + " pipes");
    std::cout << "Batch editing " << pipeIds.size() << " pipes." << std::endl;

    // Предлагаем варианты редактирования
    std::cout << "Choose what to edit:\n";
    std::cout << "1. Toggle repair status\n";
    std::cout << "2. Change diameter\n";
    std::cout << "3. Delete pipes\n";

    int choice = inputInt("Enter your choice: ", 1, 3);

    for (auto& pipe : pipes) {
        if (pipeIds.count(pipe.getId())) {
            switch (choice) {
            case 1: {
                bool newStatus = !pipe.getRepair();
                pipe.setRepair(newStatus);
                logAction("BATCH EDIT - Pipe ID: " + std::to_string(pipe.getId()) +
                    " - Repair status changed to: " + (newStatus ? "yes" : "no"));
                break;
            }
            case 2: {
                int newDiameter = inputInt("Enter new diameter for pipe ID " +
                    std::to_string(pipe.getId()) + ": ", 1);
                pipe.setDiametr(newDiameter);
                logAction("BATCH EDIT - Pipe ID: " + std::to_string(pipe.getId()) +
                    " - Diameter changed to: " + std::to_string(newDiameter) + "mm");
                break;
            }
            case 3: {
                // Помечаем для удаления (удаление будет выполнено после цикла)
                logAction("BATCH EDIT - Pipe ID: " + std::to_string(pipe.getId()) + " marked for deletion");
                break;
            }
            }
        }
    }

    // Удаление помеченных труб
    if (choice == 3) {
        pipes.erase(std::remove_if(pipes.begin(), pipes.end(),
            [&pipeIds](const Pipe& pipe) {
                return pipeIds.count(pipe.getId());
            }), pipes.end());
        logAction("BATCH EDIT - Deleted " + std::to_string(pipeIds.size()) + " pipes");
        std::cout << "Pipes deleted successfully." << std::endl;
    }
}

// Функция для отображения всех КС
void displayAllCompressStations(const std::vector<Compress>& stations) {
    if (stations.empty()) {
        std::cout << "No compress stations available." << std::endl;
        logAction("DISPLAY: No stations to display");
        return;
    }

    logAction("DISPLAY: Showing " + std::to_string(stations.size()) + " stations");
    for (const auto& station : stations) {
        station.display();
        std::cout << std::endl;
    }
}

// Функция для поиска КС по имени
std::vector<int> findStationsByName(const std::vector<Compress>& stations, const std::string& name) {
    std::vector<int> result;
    for (const auto& station : stations) {
        if (station.getName().find(name) != std::string::npos) {
            result.push_back(station.getId());
        }
    }
    logAction("SEARCH STATIONS BY NAME: '" + name + "' - Found " + std::to_string(result.size()) + " stations");
    return result;
}

// Функция для поиска КС по проценту незадействованных цехов
std::vector<int> findStationsByUnusedPercentage(const std::vector<Compress>& stations, double minPercentage) {
    std::vector<int> result;
    for (const auto& station : stations) {
        if (station.getUnusedPercentage() >= minPercentage) {
            result.push_back(station.getId());
        }
    }
    logAction("SEARCH STATIONS BY UNUSED PERCENTAGE: >=" + std::to_string(minPercentage) +
        "% - Found " + std::to_string(result.size()) + " stations");
    return result;
}

// Функция для сохранения данных
void saveData(const std::vector<Pipe>& pipes, const std::vector<Compress>& stations) {
    std::string filename = inputString("Enter filename for saving: ");
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file for writing!" << std::endl;
        logAction("SAVE ERROR: Cannot open file '" + filename + "' for writing");
        return;
    }

    // Заголовок файла
    file << "=== PIPELINE SYSTEM DATA ===" << std::endl;
    file << "Saved: " << getCurrentTime() << std::endl;
    file << "=================================" << std::endl << std::endl;

    // Сохраняем трубы с красивым форматированием
    file << "PIPES [" << pipes.size() << " items]:" << std::endl;
    file << std::string(50, '-') << std::endl;
    file << std::left << std::setw(6) << "ID"
        << std::setw(20) << "Name"
        << std::setw(10) << "Length"
        << std::setw(12) << "Diameter"
        << std::setw(10) << "Repair" << std::endl;
    file << std::string(50, '-') << std::endl;

    for (const auto& pipe : pipes) {
        file << std::left << std::setw(6) << pipe.getId()
            << std::setw(20) << (pipe.getName().length() > 18 ? pipe.getName().substr(0, 15) + "..." : pipe.getName())
            << std::setw(10) << std::fixed << std::setprecision(2) << pipe.getLength()
            << std::setw(12) << pipe.getDiametr()
            << std::setw(10) << (pipe.getRepair() ? "Yes" : "No") << std::endl;
    }

    file << std::endl << std::endl;

    // Сохраняем КС с красивым форматированием
    file << "COMPRESS STATIONS [" << stations.size() << " items]:" << std::endl;
    file << std::string(70, '-') << std::endl;
    file << std::left << std::setw(6) << "ID"
        << std::setw(20) << "Name"
        << std::setw(10) << "Total"
        << std::setw(10) << "Working"
        << std::setw(15) << "Unused %"
        << std::setw(15) << "Classification"
        << std::setw(10) << "Working" << std::endl;
    file << std::string(70, '-') << std::endl;

    for (const auto& station : stations) {
        file << std::left << std::setw(6) << station.getId()
            << std::setw(20) << (station.getName().length() > 18 ? station.getName().substr(0, 15) + "..." : station.getName())
            << std::setw(10) << station.getCount()
            << std::setw(10) << station.getCountWorking()
            << std::setw(15) << std::fixed << std::setprecision(1) << station.getUnusedPercentage()
            << std::setw(15) << (station.getClassification().length() > 12 ? station.getClassification().substr(0, 9) + "..." : station.getClassification())
            << std::setw(10) << (station.getWorking() ? "Yes" : "No") << std::endl;
    }

    file << std::endl << "=== END OF DATA ===" << std::endl;

    file.close();
    logAction("SAVE: Successfully saved " + std::to_string(pipes.size()) + " pipes and " +
        std::to_string(stations.size()) + " stations to file: '" + filename + "'");
    std::cout << "Data saved successfully to '" << filename << "'!" << std::endl;
}

// Функция для загрузки данных - УПРОЩЕННАЯ ВЕРСИЯ
void loadData(std::vector<Pipe>& pipes, std::vector<Compress>& stations) {
    std::string filename = inputString("Enter filename for loading: ");
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file for reading!" << std::endl;
        logAction("LOAD ERROR: Cannot open file '" + filename + "' for reading");
        return;
    }

    pipes.clear();
    stations.clear();

    std::string line;
    bool readingPipes = false;
    bool readingStations = false;
    int pipesLoaded = 0;
    int stationsLoaded = 0;

    // Пропускаем заголовок
    for (int i = 0; i < 5; i++) {
        std::getline(file, line);
    }

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Если нашли разделитель станций, переключаемся
        if (line.find("COMPRESS STATIONS") != std::string::npos) {
            readingPipes = false;
            readingStations = true;
            // Пропускаем еще 2 строки (разделители)
            std::getline(file, line);
            std::getline(file, line);
            continue;
        }

        // Если нашли конец данных, выходим
        if (line.find("END OF DATA") != std::string::npos) {
            break;
        }

        if (!readingStations && !line.empty() && line[0] != '=') {
            // Загружаем трубы - простой парсинг
            std::istringstream ss(line);
            int id;
            std::string name;
            float length;
            int diameter;
            std::string repairStr;

            if (ss >> id >> name >> length >> diameter >> repairStr) {
                Pipe pipe;
                pipe.setName(name);
                pipe.setLength(length);
                pipe.setDiametr(diameter);
                pipe.setRepair(repairStr == "Yes");
                pipes.push_back(pipe);
                pipesLoaded++;
            }
        }
        else if (readingStations && !line.empty() && line[0] != '=') {
            // Загружаем станции - простой парсинг
            std::istringstream ss(line);
            int id;
            std::string name;
            int count, count_working;
            double unusedPercent;
            std::string classification, workingStr;

            if (ss >> id >> name >> count >> count_working >> unusedPercent >> classification >> workingStr) {
                Compress station;
                station.setName(name);
                station.setCount(count);
                station.setCountWorking(count_working);
                station.setClassification(classification);
                station.setWorking(workingStr == "Yes");
                stations.push_back(station);
                stationsLoaded++;
            }
        }
    }

    file.close();
    logAction("LOAD: Successfully loaded " + std::to_string(pipesLoaded) + " pipes and " +
        std::to_string(stationsLoaded) + " stations from file: '" + filename + "'");
    std::cout << "Data loaded successfully! Loaded " << pipesLoaded << " pipes and "
        << stationsLoaded << " stations." << std::endl;
}

// Основная функция меню
void Menu() {
    std::vector<Pipe> pipes;
    std::vector<Compress> stations;

    logAction("PROGRAM STARTED");

    while (true) {
        std::cout << "\n=== MAIN MENU ===" << std::endl;
        std::cout << "1. Add Pipe" << std::endl;
        std::cout << "2. Add Compress Station" << std::endl;
        std::cout << "3. View All Objects" << std::endl;
        std::cout << "4. Edit Pipe" << std::endl;
        std::cout << "5. Edit Compress Station" << std::endl;
        std::cout << "6. Search Pipes" << std::endl;
        std::cout << "7. Search Stations" << std::endl;
        std::cout << "8. Batch Edit Pipes" << std::endl;
        std::cout << "9. Save Data" << std::endl;
        std::cout << "10. Load Data" << std::endl;
        std::cout << "0. Exit" << std::endl;

        int choice = inputInt("Enter your choice: ", 0, 10);
        logAction("MENU: User selected option " + std::to_string(choice));

        switch (choice) {
        case 1: {
            pipes.push_back(inputPipeData());
            logAction("ACTION: Added new pipe - Total pipes: " + std::to_string(pipes.size()));
            break;
        }
        case 2: {
            stations.push_back(inputCompressData());
            logAction("ACTION: Added new station - Total stations: " + std::to_string(stations.size()));
            break;
        }
        case 3: {
            logAction("ACTION: Displaying all objects");
            std::cout << "\n=== PIPES ===" << std::endl;
            displayAllPipes(pipes);
            std::cout << "\n=== COMPRESS STATIONS ===" << std::endl;
            displayAllCompressStations(stations);
            break;
        }
        case 4: {
            if (pipes.empty()) {
                std::cout << "No pipes available for editing." << std::endl;
                logAction("ACTION: No pipes available for editing");
                break;
            }

            displayAllPipes(pipes);
            int pipeId = inputInt("Enter pipe ID to edit: ");

            auto it = std::find_if(pipes.begin(), pipes.end(),
                [pipeId](const Pipe& pipe) { return pipe.getId() == pipeId; });

            if (it != pipes.end()) {
                std::cout << "Editing pipe ID: " << pipeId << std::endl;
                *it = inputPipeData();
                logAction("ACTION: Edited pipe with ID: " + std::to_string(pipeId));
            }
            else {
                std::cout << "Pipe with ID " << pipeId << " not found." << std::endl;
                logAction("ACTION ERROR: Pipe with ID " + std::to_string(pipeId) + " not found for editing");
            }
            break;
        }
        case 5: {
            if (stations.empty()) {
                std::cout << "No stations available for editing." << std::endl;
                logAction("ACTION: No stations available for editing");
                break;
            }

            displayAllCompressStations(stations);
            int stationId = inputInt("Enter station ID to edit: ");

            auto it = std::find_if(stations.begin(), stations.end(),
                [stationId](const Compress& station) { return station.getId() == stationId; });

            if (it != stations.end()) {
                std::cout << "Editing station ID: " << stationId << std::endl;
                *it = inputCompressData();
                logAction("ACTION: Edited station with ID: " + std::to_string(stationId));
            }
            else {
                std::cout << "Station with ID " << stationId << " not found." << std::endl;
                logAction("ACTION ERROR: Station with ID " + std::to_string(stationId) + " not found for editing");
            }
            break;
        }
        case 6: {
            logAction("ACTION: Starting pipe search");
            std::cout << "Search pipes by:\n1. Name\n2. Repair status\n";
            int searchChoice = inputInt("Enter choice: ", 1, 2);

            std::vector<int> foundIds;
            if (searchChoice == 1) {
                std::string name = inputString("Enter name to search: ");
                foundIds = findPipesByName(pipes, name);
            }
            else {
                bool repairStatus = inputBool("Search pipes in repair?");
                foundIds = findPipesByRepairStatus(pipes, repairStatus);
            }

            std::cout << "Found " << foundIds.size() << " pipes:" << std::endl;
            for (int id : foundIds) {
                auto it = std::find_if(pipes.begin(), pipes.end(),
                    [id](const Pipe& pipe) { return pipe.getId() == id; });
                if (it != pipes.end()) {
                    it->display();
                    std::cout << std::endl;
                }
            }
            break;
        }
        case 7: {
            logAction("ACTION: Starting station search");
            std::cout << "Search stations by:\n1. Name\n2. Unused percentage\n";
            int searchChoice = inputInt("Enter choice: ", 1, 2);

            std::vector<int> foundIds;
            if (searchChoice == 1) {
                std::string name = inputString("Enter name to search: ");
                foundIds = findStationsByName(stations, name);
            }
            else {
                double minPercentage = inputFloat("Enter minimum unused percentage: ", 0.0, 100.0);
                foundIds = findStationsByUnusedPercentage(stations, minPercentage);
            }

            std::cout << "Found " << foundIds.size() << " stations:" << std::endl;
            for (int id : foundIds) {
                auto it = std::find_if(stations.begin(), stations.end(),
                    [id](const Compress& station) { return station.getId() == id; });
                if (it != stations.end()) {
                    it->display();
                    std::cout << std::endl;
                }
            }
            break;
        }
        case 8: {
            logAction("ACTION: Starting batch pipe edit");
            std::cout << "Batch edit pipes - select pipes to edit:\n";
            std::cout << "1. Select by search\n2. Enter IDs manually\n";
            int selectChoice = inputInt("Enter choice: ", 1, 2);

            std::unordered_set<int> selectedIds;

            if (selectChoice == 1) {
                std::cout << "Search pipes by:\n1. Name\n2. Repair status\n";
                int searchChoice = inputInt("Enter choice: ", 1, 2);

                if (searchChoice == 1) {
                    std::string name = inputString("Enter name to search: ");
                    auto foundIds = findPipesByName(pipes, name);
                    selectedIds.insert(foundIds.begin(), foundIds.end());
                }
                else {
                    bool repairStatus = inputBool("Search pipes in repair?");
                    auto foundIds = findPipesByRepairStatus(pipes, repairStatus);
                    selectedIds.insert(foundIds.begin(), foundIds.end());
                }
            }
            else {
                std::cout << "Enter pipe IDs (0 to finish):" << std::endl;
                while (true) {
                    int id = inputInt("Enter ID: ", 0);
                    if (id == 0) break;
                    selectedIds.insert(id);
                }
            }

            batchEditPipes(pipes, selectedIds);
            break;
        }
        case 9: {
            logAction("ACTION: User initiated data save");
            saveData(pipes, stations);
            break;
        }
        case 10: {
            logAction("ACTION: User initiated data load");
            loadData(pipes, stations);
            break;
        }
        case 0: {
            logAction("PROGRAM EXIT - Final state: " + std::to_string(pipes.size()) +
                " pipes, " + std::to_string(stations.size()) + " stations");
            std::cout << "Goodbye!" << std::endl;
            return;
        }
        }
    }
}