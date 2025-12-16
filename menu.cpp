#include "utils.h"
#include "graph.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <map>
#include <queue>
#include <limits>
#include <cmath>
#include <vector>
#include <unordered_set>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <limits>
#include <cmath>
#include "menu.h"

// Input pipe
Pipe inputPipeData() {
    std::cout << "Enter pipe data" << std::endl;
    std::string name = inputString("Enter pipe name: ");
    float length = inputFloat("Enter pipe length (km): ", 0.0f);

    // Проверяем стандартные диаметры
    std::cout << "Available diameters: 500, 700, 1000, 1400 mm" << std::endl;
    int diametr = inputInt("Enter pipe diameter (mm): ", 500);

    // Проверяем, что диаметр стандартный
    if (diametr != 500 && diametr != 700 && diametr != 1000 && diametr != 1400) {
        std::cout << "Warning: Non-standard diameter! Standard diameters are: 500, 700, 1000, 1400 mm" << std::endl;
    }

    bool repair = inputBool("Is pipe under repair?");

    Pipe pipe(name, length, diametr, repair);
    logAction("PIPE CREATED - ID: " + std::to_string(pipe.getId()) +
        ", Name: '" + name + "', Length: " + std::to_string(length) +
        "km, Diameter: " + std::to_string(diametr) + "mm, Repair: " +
        (repair ? "yes" : "no"));
    return pipe;
}

// Input CS
Compress inputCompressData() {
    std::cout << "Enter CS data" << std::endl;
    std::string name = inputString("Enter CS name: ");
    int count = inputInt("Enter number of workshops: ", 1);
    int count_working = inputInt("Enter number of working workshops: ", 0, count);
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

// Display pipes
void displayAllPipes(const std::map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        std::cout << "No pipes available." << std::endl;
        logAction("DISPLAY: No pipes to display");
        return;
    }

    logAction("DISPLAY: Showing " + std::to_string(pipes.size()) + " pipes");
    for (const auto& pipe : pipes) {
        std::cout << "ID: " << pipe.first << std::endl;
        pipe.second.display();
        std::cout << std::endl;
    }
}

// Search by name
std::vector<int> findPipesByName(const std::map<int, Pipe>& pipes, const std::string& name) {
    std::vector<int> result;
    for (const auto& pipe : pipes) {
        if (pipe.second.getName().find(name) != std::string::npos) {
            result.push_back(pipe.first);
        }
    }
    logAction("SEARCH PIPES BY NAME: '" + name + "' - Found " + std::to_string(result.size()) + " pipes");
    return result;
}

// Search by repair status
std::vector<int> findPipesByRepairStatus(const std::map<int, Pipe>& pipes, bool repairStatus) {
    std::vector<int> result;
    for (const auto& pipe : pipes) {
        if (pipe.second.getRepair() == repairStatus) {
            result.push_back(pipe.first);
        }
    }
    logAction("SEARCH PIPES BY REPAIR STATUS: " + std::string(repairStatus ? "in repair" : "not in repair") +
        " - Found " + std::to_string(result.size()) + " pipes");
    return result;
}

// Batch editing
void batchEditPipes(std::map<int, Pipe>& pipes, const std::unordered_set<int>& pipeIds) {
    if (pipeIds.empty()) {
        std::cout << "No pipes selected for editing." << std::endl;
        logAction("BATCH EDIT: No pipes selected");
        return;
    }

    logAction("BATCH EDIT: Starting batch edit for " + std::to_string(pipeIds.size()) + " pipes");
    std::cout << "Batch editing " << pipeIds.size() << " pipes." << std::endl;

    // Options
    std::cout << "Choose what to edit:\n";
    std::cout << "1. Change repair status\n";
    std::cout << "2. Change diameter\n";
    std::cout << "3. Delete pipes\n";

    int choice = inputInt("Enter your choice: ", 1, 3);

    for (auto& pipe : pipes) {
        if (pipeIds.count(pipe.first)) {
            switch (choice) {
            case 1: {
                bool newStatus = !pipe.second.getRepair();
                pipe.second.setRepair(newStatus);
                logAction("BATCH EDIT - Pipe ID: " + std::to_string(pipe.first) +
                    " - Repair status changed to: " + (newStatus ? "yes" : "no"));
                break;
            }
            case 2: {
                int newDiameter = inputInt("Enter new diameter for pipe ID " +
                    std::to_string(pipe.first) + ": ", 1);
                pipe.second.setDiametr(newDiameter);
                logAction("BATCH EDIT - Pipe ID: " + std::to_string(pipe.first) +
                    " - Diameter changed to: " + std::to_string(newDiameter) + "mm");
                break;
            }
            case 3: {
                logAction("BATCH EDIT - Pipe ID: " + std::to_string(pipe.first) + " marked for deletion");
                break;
            }
            }
        }
    }

    // Delete pipes
    if (choice == 3) {
        for (auto it = pipes.begin(); it != pipes.end(); ) {
            if (pipeIds.count(it->first)) {
                it = pipes.erase(it);
            }
            else {
                ++it;
            }
        }
        logAction("BATCH EDIT - Deleted " + std::to_string(pipeIds.size()) + " pipes");
        std::cout << "Pipes successfully deleted." << std::endl;
    }
}

// Display CS
void displayAllCompressStations(const std::map<int, Compress>& stations) {
    if (stations.empty()) {
        std::cout << "No compressor stations available." << std::endl;
        logAction("DISPLAY: No stations to display");
        return;
    }

    logAction("DISPLAY: Showing " + std::to_string(stations.size()) + " stations");
    for (const auto& station : stations) {
        std::cout << "ID: " << station.first << std::endl;
        station.second.display();
        std::cout << std::endl;
    }
}

// Search CS by name
std::vector<int> findStationsByName(const std::map<int, Compress>& stations, const std::string& name) {
    std::vector<int> result;
    for (const auto& station : stations) {
        if (station.second.getName().find(name) != std::string::npos) {
            result.push_back(station.first);
        }
    }
    logAction("SEARCH STATIONS BY NAME: '" + name + "' - Found " + std::to_string(result.size()) + " stations");
    return result;
}

// Search CS by workshops
std::vector<int> findStationsByUnusedPercentage(const std::map<int, Compress>& stations, double minPercentage) {
    std::vector<int> result;
    for (const auto& station : stations) {
        if (station.second.getUnusedPercentage() >= minPercentage) {
            result.push_back(station.first);
        }
    }
    logAction("SEARCH STATIONS BY UNUSED PERCENTAGE: >=" + std::to_string(minPercentage) +
        "% - Found " + std::to_string(result.size()) + " stations");
    return result;
}

// Function to create connection
void createConnection(std::map<int, Pipe>& pipes, std::map<int, Compress>& stations, std::vector<Connection>& connections, int& nextPipeId) {
    if (stations.size() < 2) {
        std::cout << "Not enough compressor stations to create connection (minimum 2 required)." << std::endl;
        return;
    }

    std::cout << "Creating connection between CS:" << std::endl;

    // Show available CS
    std::cout << "Available compressor stations:" << std::endl;
    for (const auto& station : stations) {
        std::cout << "ID: " << station.first << " - " << station.second.getName() << std::endl;
    }

    // Select start CS
    int start_id = inputInt("Enter start CS ID: ");
    if (stations.find(start_id) == stations.end()) {
        std::cout << "CS with ID " << start_id << " not found." << std::endl;
        return;
    }

    // Select end CS
    int stop_id = inputInt("Enter end CS ID: ");
    if (stations.find(stop_id) == stations.end()) {
        std::cout << "CS with ID " << stop_id << " not found." << std::endl;
        return;
    }

    if (start_id == stop_id) {
        std::cout << "Start and end CS cannot be the same." << std::endl;
        return;
    }

    // Check for existing connection
    for (const auto& conn : connections) {
        if ((conn.start_id == start_id && conn.stop_id == stop_id) ||
            (conn.start_id == stop_id && conn.stop_id == start_id)) {
            std::cout << "Connection between these CS already exists." << std::endl;
            return;
        }
    }

    // Request pipe diameter
    std::cout << "\nEnter pipe diameter for connection (500, 700, 1000, 1400 mm): ";
    int requiredDiameter = inputInt("Diameter: ");

    // Check valid diameters
    if (requiredDiameter != 500 && requiredDiameter != 700 && requiredDiameter != 1000 && requiredDiameter != 1400) {
        std::cout << "Invalid diameter! Use: 500, 700, 1000 or 1400 mm." << std::endl;
        return;
    }

    // Search for available pipes with required diameter
    std::vector<int> availablePipes;
    std::cout << "\nSearching for pipes with diameter " << requiredDiameter << " mm..." << std::endl;

    for (const auto& pipe : pipes) {
        if (!pipe.second.getRepair() && pipe.second.getDiametr() == requiredDiameter) {
            availablePipes.push_back(pipe.first);
        }
    }

    int pipe_id = -1;

    if (availablePipes.empty()) {
        // No pipe with required diameter - create new one
        std::cout << "No pipes with diameter " << requiredDiameter << " mm found." << std::endl;
        std::cout << "Proceeding to create new pipe..." << std::endl;

        // Create new pipe with required diameter
        std::cout << "\nCreating new pipe with diameter " << requiredDiameter << " mm:" << std::endl;
        std::string name = inputString("Enter pipe name: ");
        float length = inputFloat("Enter pipe length (km): ", 0.0f);

        // Create pipe with automatically set diameter
        Pipe newPipe(name, length, requiredDiameter, false);
        pipe_id = nextPipeId;
        pipes[pipe_id] = newPipe;
        nextPipeId++;

        logAction("PIPE CREATED FOR CONNECTION - ID: " + std::to_string(pipe_id) +
            ", Name: '" + name + "', Length: " + std::to_string(length) +
            "km, Diameter: " + std::to_string(requiredDiameter) + "mm");

        std::cout << "Created new pipe with ID: " << pipe_id << std::endl;
    }
    else {
        // Show available pipes and select one
        std::cout << "\nFound following pipes with diameter " << requiredDiameter << " mm:" << std::endl;
        for (int pipeId : availablePipes) {
            auto pipeIt = pipes.find(pipeId);
            if (pipeIt != pipes.end()) {
                std::cout << "ID: " << pipeId << " - " << pipeIt->second.getName()
                    << " (length: " << pipeIt->second.getLength() << " km)" << std::endl;
            }
        }

        // Select pipe
        while (true) {
            pipe_id = inputInt("\nEnter pipe ID for connection: ");
            if (std::find(availablePipes.begin(), availablePipes.end(), pipe_id) != availablePipes.end()) {
                break;
            }
            std::cout << "Pipe with ID " << pipe_id << " not available or not found. Please try again." << std::endl;
        }

        std::cout << "Selected pipe ID: " << pipe_id << std::endl;
    }

    // Create connection
    Connection newConnection(start_id, stop_id, pipe_id);
    connections.push_back(newConnection);

    logAction("CONNECTION CREATED - From CS " + std::to_string(start_id) +
        " to CS " + std::to_string(stop_id) + " via Pipe " + std::to_string(pipe_id));
    std::cout << "\nConnection successfully created!" << std::endl;
    std::cout << "CS " << start_id << " -> CS " << stop_id << " via pipe " << pipe_id << std::endl;
}

// Function to display connections
void displayConnections(const std::vector<Connection>& connections, const std::map<int, Pipe>& pipes, const std::map<int, Compress>& stations) {
    if (connections.empty()) {
        std::cout << "No connections." << std::endl;
        return;
    }

    std::cout << "CONNECTIONS:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& conn : connections) {
        auto start_station = stations.find(conn.start_id);
        auto stop_station = stations.find(conn.stop_id);
        auto pipe = pipes.find(conn.pipe_id);

        if (start_station != stations.end() && stop_station != stations.end() && pipe != pipes.end()) {
            std::cout << "CS \"" << start_station->second.getName() << "\" (ID: " << conn.start_id << ")"
                << " -> CS \"" << stop_station->second.getName() << "\" (ID: " << conn.stop_id << ")"
                << " via pipe \"" << pipe->second.getName() << "\" (ID: " << conn.pipe_id << ")" << std::endl;
        }
    }
}

// Function to delete connection
void deleteConnection(std::vector<Connection>& connections) {
    if (connections.empty()) {
        std::cout << "No connections to delete." << std::endl;
        return;
    }

    std::cout << "Connection list:" << std::endl;
    for (size_t i = 0; i < connections.size(); ++i) {
        std::cout << (i + 1) << ". CS " << connections[i].start_id << " -> CS " << connections[i].stop_id
            << " (Pipe " << connections[i].pipe_id << ")" << std::endl;
    }

    int connection_index = inputInt("Enter connection number to delete (0 to cancel): ", 0, connections.size());
    if (connection_index == 0) {
        return;
    }

    if (connection_index > 0 && connection_index <= connections.size()) {
        Connection removed = connections[connection_index - 1];
        connections.erase(connections.begin() + connection_index - 1);

        logAction("CONNECTION DELETED - From CS " + std::to_string(removed.start_id) +
            " to CS " + std::to_string(removed.stop_id) + " via Pipe " + std::to_string(removed.pipe_id));
        std::cout << "Connection deleted!" << std::endl;
    }
}

// Function for topological sort
void topologicalSort(const std::vector<Connection>& connections, const std::map<int, Compress>& stations) {
    if (stations.empty()) {
        std::cout << "No compressor stations for sorting." << std::endl;
        return;
    }

    if (connections.empty()) {
        std::cout << "No connections between stations." << std::endl;
        return;
    }

    // Create in-degree map
    std::map<int, int> inDegree;
    for (const auto& station : stations) {
        inDegree[station.first] = 0;
    }

    // Calculate in-degrees
    for (const auto& conn : connections) {
        inDegree[conn.stop_id]++;
    }

    // Topological sort
    std::vector<std::vector<int>> result;
    std::vector<int> currentLevel;

    while (!inDegree.empty()) {
        currentLevel.clear();

        // Find stations with zero in-degree
        for (auto it = inDegree.begin(); it != inDegree.end(); ) {
            if (it->second == 0) {
                currentLevel.push_back(it->first);
                it = inDegree.erase(it);
            }
            else {
                ++it;
            }
        }

        if (currentLevel.empty()) {
            // Cycle detected
            std::cout << "Cycle detected in graph! Topological sorting impossible." << std::endl;
            logAction("TOPOLOGICAL SORT: Cycle detected - sorting impossible");
            return;
        }

        // Decrease in-degrees for stations connected to current level
        for (int stationId : currentLevel) {
            for (const auto& conn : connections) {
                if (conn.start_id == stationId) {
                    auto it = inDegree.find(conn.stop_id);
                    if (it != inDegree.end()) {
                        it->second--;
                    }
                }
            }
        }

        result.push_back(currentLevel);
    }

    // Output result
    std::cout << "TOPOLOGICAL SORT:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "Level " << (i + 1) << ": [ ";
        for (int stationId : result[i]) {
            auto station = stations.find(stationId);
            if (station != stations.end()) {
                std::cout << station->second.getName() << " (ID: " << stationId << ") ";
            }
        }
        std::cout << "]" << std::endl;
    }

    logAction("TOPOLOGICAL SORT: Completed successfully - " + std::to_string(result.size()) + " levels");
}

// Save data
void saveData(const std::map<int, Pipe>& pipes, const std::map<int, Compress>& stations, const std::vector<Connection>& connections) {
    std::string filename = inputString("Enter filename for saving: ");
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file for writing!" << std::endl;
        logAction("SAVE ERROR: Cannot open file '" + filename + "' for writing");
        return;
    }

    // Header
    file << "PIPELINE SYSTEM DATA" << std::endl;
    file << "Saved: " << getCurrentTime() << std::endl;
    file << "" << std::endl << std::endl;

    // Pipes saving
    file << "PIPES [" << pipes.size() << " items]:" << std::endl;
    file << std::string(50, '-') << std::endl;
    file << std::left << std::setw(6) << "ID"
        << std::setw(20) << "Name"
        << std::setw(10) << "Length"
        << std::setw(12) << "Diameter"
        << std::setw(10) << "Repair" << std::endl;
    file << std::string(50, '-') << std::endl;

    for (const auto& pipe : pipes) {
        file << std::left << std::setw(6) << pipe.first
            << std::setw(20) << (pipe.second.getName().length() > 18 ? pipe.second.getName().substr(0, 15) + "..." : pipe.second.getName())
            << std::setw(10) << std::fixed << std::setprecision(2) << pipe.second.getLength()
            << std::setw(12) << pipe.second.getDiametr()
            << std::setw(10) << (pipe.second.getRepair() ? "Yes" : "No") << std::endl;
    }

    file << std::endl << std::endl;

    // Stations saving
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
        file << std::left << std::setw(6) << station.first
            << std::setw(20) << (station.second.getName().length() > 18 ? station.second.getName().substr(0, 15) + "..." : station.second.getName())
            << std::setw(10) << station.second.getCount()
            << std::setw(10) << station.second.getCountWorking()
            << std::setw(15) << std::fixed << std::setprecision(1) << station.second.getUnusedPercentage()
            << std::setw(15) << (station.second.getClassification().length() > 12 ? station.second.getClassification().substr(0, 9) + "..." : station.second.getClassification())
            << std::setw(10) << (station.second.getWorking() ? "Yes" : "No") << std::endl;
    }

    file << std::endl << std::endl;

    // Connections saving
    file << "CONNECTIONS [" << connections.size() << " items]:" << std::endl;
    file << std::string(40, '-') << std::endl;
    file << std::left << std::setw(8) << "StartID"
        << std::setw(8) << "StopID"
        << std::setw(8) << "PipeID" << std::endl;
    file << std::string(40, '-') << std::endl;

    for (const auto& conn : connections) {
        file << std::left << std::setw(8) << conn.start_id
            << std::setw(8) << conn.stop_id
            << std::setw(8) << conn.pipe_id << std::endl;
    }

    file << std::endl << "END OF DATA" << std::endl;

    file.close();
    logAction("SAVE: Successfully saved " + std::to_string(pipes.size()) + " pipes, " +
        std::to_string(stations.size()) + " stations and " + std::to_string(connections.size()) +
        " connections to file: '" + filename + "'");
    std::cout << "Data successfully saved to '" << filename << "'!" << std::endl;
}

// Load from file
void loadData(std::map<int, Pipe>& pipes, std::map<int, Compress>& stations, std::vector<Connection>& connections, int& nextPipeId, int& nextStationId) {
    std::string filename = inputString("Enter filename for loading: ");
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file for reading!" << std::endl;
        logAction("LOAD ERROR: Cannot open file '" + filename + "' for reading");
        return;
    }

    pipes.clear();
    stations.clear();
    connections.clear();
    nextPipeId = 1;
    nextStationId = 1;

    std::string line;
    bool readingPipes = false;
    bool readingStations = false;
    bool readingConnections = false;
    int pipesLoaded = 0;
    int stationsLoaded = 0;
    int connectionsLoaded = 0;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line.find("PIPES [") != std::string::npos) {
            readingPipes = true;
            readingStations = false;
            readingConnections = false;
            // Skip separators
            std::getline(file, line);
            std::getline(file, line);
            continue;
        }

        if (line.find("COMPRESS STATIONS [") != std::string::npos) {
            readingPipes = false;
            readingStations = true;
            readingConnections = false;
            // Skip separators
            std::getline(file, line);
            std::getline(file, line);
            continue;
        }

        if (line.find("CONNECTIONS [") != std::string::npos) {
            readingPipes = false;
            readingStations = false;
            readingConnections = true;
            // Skip separators
            std::getline(file, line);
            std::getline(file, line);
            continue;
        }

        // Exit at end of data
        if (line.find("END OF DATA") != std::string::npos) {
            break;
        }

        if (readingPipes && !line.empty() && line[0] != '=') {
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
                pipes[id] = pipe;
                pipesLoaded++;
                if (id >= nextPipeId) nextPipeId = id + 1;
            }
        }
        else if (readingStations && !line.empty() && line[0] != '=') {
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
                stations[id] = station;
                stationsLoaded++;
                if (id >= nextStationId) nextStationId = id + 1;
            }
        }
        else if (readingConnections && !line.empty() && line[0] != '=') {
            std::istringstream ss(line);
            int start_id, stop_id, pipe_id;

            if (ss >> start_id >> stop_id >> pipe_id) {
                Connection conn(start_id, stop_id, pipe_id);
                connections.push_back(conn);
                connectionsLoaded++;
            }
        }
    }

    file.close();
    logAction("LOAD: Successfully loaded " + std::to_string(pipesLoaded) + " pipes, " +
        std::to_string(stationsLoaded) + " stations and " + std::to_string(connectionsLoaded) +
        " connections from file: '" + filename + "'");
    std::cout << "Data successfully loaded! Loaded " << pipesLoaded << " pipes, "
        << stationsLoaded << " stations and " << connectionsLoaded << " connections." << std::endl;
}

// Функция для расчета максимального потока
double calculateMaxFlow(const std::vector<Connection>& connections,
    const std::map<int, Pipe>& pipes,
    const std::map<int, Compress>& stations,
    int sourceId, int sinkId) {

    if (stations.find(sourceId) == stations.end() ||
        stations.find(sinkId) == stations.end()) {
        std::cout << "Ошибка: указанные КС не существуют!" << std::endl;
        return 0.0;
    }

    // Создаем граф
    Graph graph;

    // Добавляем ребра
    for (const auto& conn : connections) {
        auto pipeIt = pipes.find(conn.pipe_id);
        if (pipeIt != pipes.end()) {
            double capacity = pipeIt->second.getCapacity();
            graph.addEdge(conn.start_id, conn.stop_id, conn.pipe_id, capacity, true);
        }
    }

    // Вычисляем максимальный поток
    double maxFlow = graph.maxFlow(sourceId, sinkId);

    std::cout << "\n=== Max FLOW ===" << std::endl;
    std::cout << "Start CS:  ID " << sourceId;
    auto sourceIt = stations.find(sourceId);
    if (sourceIt != stations.end()) {
        std::cout << " (\"" << sourceIt->second.getName() << "\")";
    }

    std::cout << "\nFinish CS: ID " << sinkId;
    auto sinkIt = stations.find(sinkId);
    if (sinkIt != stations.end()) {
        std::cout << " (\"" << sinkIt->second.getName() << "\")";
    }

    std::cout << "\nMax Flow: " << maxFlow << " mln. l³/day" << std::endl;
    std::cout << "===============================\n" << std::endl;

    logAction("MAX FLOW CALCULATION: Source=" + std::to_string(sourceId) +
        ", Sink=" + std::to_string(sinkId) +
        ", Flow=" + std::to_string(maxFlow) + " mln. m³/day");

    return maxFlow;
}

// Функция для поиска кратчайшего пути
std::vector<int> findShortestPath(const std::vector<Connection>& connections,
    const std::map<int, Pipe>& pipes,
    const std::map<int, Compress>& stations,
    int startId, int endId) {

    std::vector<int> path;

    if (stations.find(startId) == stations.end() ||
        stations.find(endId) == stations.end()) {
        std::cout << "Error! CS not found" << std::endl;
        return path;
    }

    if (startId == endId) {
        std::cout << "Start and finish CS is equal!" << std::endl;
        path.push_back(startId);
        return path;
    }

    // Создаем граф
    Graph graph;

    // Добавляем ребра с весами
    for (const auto& conn : connections) {
        auto pipeIt = pipes.find(conn.pipe_id);
        if (pipeIt != pipes.end()) {
            double weight = pipeIt->second.getWeight();
            if (weight < std::numeric_limits<double>::infinity()) {
                graph.addEdge(conn.start_id, conn.stop_id, conn.pipe_id, weight, true);
            }
        }
    }

    // Ищем кратчайший путь
    path = graph.shortestPath(startId, endId);

    std::cout << "\n=== Min Path ===" << std::endl;

    if (path.empty() || path.size() == 1) {
        std::cout << "Path between CS with ID " << startId << " and CS ID " << endId
            << " not found!" << std::endl;
    }
    else {
        std::cout << "Path between CS with ID " << startId << " and CS ID " << endId
            << " (" << path.size() - 1 << " paths):" << std::endl;

        double totalWeight = 0.0;
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            auto stationIt = stations.find(path[i]);
            if (stationIt != stations.end()) {
                std::cout << " (\"" << stationIt->second.getName() << "\")";
            }

            if (i < path.size() - 1) {
                std::cout << " -> ";
                // Находим трубу между этими КС для отображения длины
                for (const auto& conn : connections) {
                    if ((conn.start_id == path[i] && conn.stop_id == path[i + 1]) ||
                        (conn.start_id == path[i + 1] && conn.stop_id == path[i])) {
                        auto pipeIt = pipes.find(conn.pipe_id);
                        if (pipeIt != pipes.end()) {
                            totalWeight += pipeIt->second.getWeight();
                        }
                        break;
                    }
                }
            }
        }
        std::cout << "\nPath weight: " << totalWeight << " points" << std::endl;
    }

    std::cout << "====================\n" << std::endl;

    logAction("SHORTEST PATH: From=" + std::to_string(startId) +
        ", To=" + std::to_string(endId) +
        ", Path length=" + std::to_string(path.size()));

    return path;
}

// Menu
void Menu() {
    std::map<int, Pipe> pipes;
    std::map<int, Compress> stations;
    std::vector<Connection> connections;

    int nextPipeId = 1;
    int nextStationId = 1;

    logAction("PROGRAM STARTED");

    while (true) {
        std::cout << "\nMAIN MENU" << std::endl;
        std::cout << "1. Add Pipe" << std::endl;
        std::cout << "2. Add Compressor Station" << std::endl;
        std::cout << "3. View All Objects" << std::endl;
        std::cout << "4. Edit Pipe" << std::endl;
        std::cout << "5. Edit Compressor Station" << std::endl;
        std::cout << "6. Search Pipes" << std::endl;
        std::cout << "7. Search Stations" << std::endl;
        std::cout << "8. Batch Edit Pipes" << std::endl;
        std::cout << "9. Create Connection" << std::endl;
        std::cout << "10. Show Connections" << std::endl;
        std::cout << "11. Delete Connection" << std::endl;
        std::cout << "12. Topological Sort" << std::endl;
        std::cout << "13. Calculate Maximum Flow" << std::endl;      // НОВЫЙ ПУНКТ
        std::cout << "14. Find Shortest Path" << std::endl;          // НОВЫЙ ПУНКТ
        std::cout << "15. Save Data" << std::endl;                   // СМЕЩЕНО
        std::cout << "16. Load Data" << std::endl;                   // СМЕЩЕНО
        std::cout << "0. Exit" << std::endl;

        int choice = inputInt("Select option: ", 0, 16);
        logAction("MENU: User selected option " + std::to_string(choice));

        switch (choice) {
        case 1: {
            Pipe newPipe = inputPipeData();
            pipes[nextPipeId] = newPipe;
            logAction("ACTION: Added new pipe ID " + std::to_string(nextPipeId));
            nextPipeId++;
            break;
        }
        case 2: {
            Compress newStation = inputCompressData();
            stations[nextStationId] = newStation;
            logAction("ACTION: Added new station ID " + std::to_string(nextStationId));
            nextStationId++;
            break;
        }
        case 3: {
            logAction("ACTION: Displaying all objects");
            std::cout << "\nPIPES:" << std::endl;
            displayAllPipes(pipes);
            std::cout << "\nCOMPRESSOR STATIONS:" << std::endl;
            displayAllCompressStations(stations);
            std::cout << "\n";
            displayConnections(connections, pipes, stations);
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

            auto it = pipes.find(pipeId);
            if (it != pipes.end()) {
                std::cout << "Editing pipe ID: " << pipeId << std::endl;
                it->second = inputPipeData();
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

            auto it = stations.find(stationId);
            if (it != stations.end()) {
                std::cout << "Editing station ID: " << stationId << std::endl;
                it->second = inputCompressData();
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
                bool repairStatus = inputBool("Search pipes under repair?");
                foundIds = findPipesByRepairStatus(pipes, repairStatus);
            }

            std::cout << "Found " << foundIds.size() << " pipes:" << std::endl;
            for (int id : foundIds) {
                auto it = pipes.find(id);
                if (it != pipes.end()) {
                    std::cout << "ID: " << id << std::endl;
                    it->second.display();
                    std::cout << std::endl;
                }
            }
            break;
        }
        case 7: {
            logAction("ACTION: Starting station search");
            std::cout << "Search stations by:\n1. Name\n2. Unused workshops percentage\n";
            int searchChoice = inputInt("Enter choice: ", 1, 2);

            std::vector<int> foundIds;
            if (searchChoice == 1) {
                std::string name = inputString("Enter name to search: ");
                foundIds = findStationsByName(stations, name);
            }
            else {
                double minPercentage = inputFloat("Enter minimum unused workshops percentage: ", 0.0, 100.0);
                foundIds = findStationsByUnusedPercentage(stations, minPercentage);
            }

            std::cout << "Found " << foundIds.size() << " stations:" << std::endl;
            for (int id : foundIds) {
                auto it = stations.find(id);
                if (it != stations.end()) {
                    std::cout << "ID: " << id << std::endl;
                    it->second.display();
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
                    bool repairStatus = inputBool("Search pipes under repair?");
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
            createConnection(pipes, stations, connections, nextPipeId);
            break;
        }
        case 10: {
            displayConnections(connections, pipes, stations);
            break;
        }
        case 11: {
            deleteConnection(connections);
            break;
        }
        case 12: {
            topologicalSort(connections, stations);
            break;
        }
        case 13: {  // Расчет максимального потока
            if (stations.size() < 2) {
                std::cout << "Not enough CS to flow." << std::endl;
                break;
            }

            if (connections.empty()) {
                std::cout << "Not connections." << std::endl;
                break;
            }

            std::cout << "Available CS:" << std::endl;
            for (const auto& station : stations) {
                std::cout << "ID: " << station.first << " - \""
                    << station.second.getName() << "\"" << std::endl;
            }

            int sourceId = inputInt("Enter start ID: ");
            int sinkId = inputInt("Enter finish ID: ");

            if (sourceId == sinkId) {
                std::cout << "Please enter different IDs!" << std::endl;
                break;
            }

            calculateMaxFlow(connections, pipes, stations, sourceId, sinkId);
            break;
        }
        case 14: {  // Поиск кратчайшего пути
            if (stations.size() < 2) {
                std::cout << "Not enough CS for flow." << std::endl;
                break;
            }

            if (connections.empty()) {
                std::cout << "Not connections." << std::endl;
                break;
            }

            std::cout << "Available CS:" << std::endl;
            for (const auto& station : stations) {
                std::cout << "ID: " << station.first << " - \""
                    << station.second.getName() << "\"" << std::endl;
            }

            int startId = inputInt("Enter start ID: ");
            int endId = inputInt("Enter dinish ID: ");

            findShortestPath(connections, pipes, stations, startId, endId);
            break;
        }
        case 15: {  // Было 13, стало 15
            logAction("ACTION: User initiated data save");
            saveData(pipes, stations, connections);
            break;
        }
        case 16: {  // Было 14, стало 16
            logAction("ACTION: User initiated data load");
            loadData(pipes, stations, connections, nextPipeId, nextStationId);
            break;
        }
        case 0: {
            logAction("PROGRAM EXIT");
            std::cout << "Goodbye!" << std::endl;
            return;
        }
        }
    }
}