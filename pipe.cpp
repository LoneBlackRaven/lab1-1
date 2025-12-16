#include "pipe.h"
#include <cmath>
#include <map>

int Pipe::nextId = 1;

// Конструктор по умолчанию
Pipe::Pipe() : id(nextId++), name("Not set"), length(0.0f), diametr(0), repair(false) {}

// Конструктор с параметрами
Pipe::Pipe(const std::string& name, float length, int diametr, bool repair)
    : id(nextId++), name(name), length(length), diametr(diametr), repair(repair) {
}

// Методы для установки значений
void Pipe::setName(const std::string& newName) { name = newName; }
void Pipe::setLength(float newLength) { length = newLength; }
void Pipe::setDiametr(int newDiametr) { diametr = newDiametr; }
void Pipe::setRepair(bool newRepair) { repair = newRepair; }

// Методы для получения значений
int Pipe::getId() const { return id; }
std::string Pipe::getName() const { return name; }
float Pipe::getLength() const { return length; }
int Pipe::getDiametr() const { return diametr; }
bool Pipe::getRepair() const { return repair; }

// Метод для расчета производительности по таблице 1.1
double Pipe::getCapacity() const {
    if (repair) {
        return 0.0;  // Труба в ремонте - производительность 0
    }

    // Таблица соответствия диаметра и производительности (млн. м³/сут)
    static const std::map<int, std::pair<double, double>> diameterCapacityMap = {
        {530,  {4.0, 6.0}},   // 530 мм: 4-6 млн. м³/сут
        {720,  {11.0, 13.0}}, // 720 мм: 11-13 млн. м³/сут
        {1020, {25.0, 35.0}}, // 1020 мм: 25-35 млн. м³/сут
        {1220, {50.0, 60.0}}, // 1220 мм: 50-60 млн. м³/сут
        {1420, {90.0, 100.0}} // 1420 мм: 90-100 млн. м³/сут
    };

    auto it = diameterCapacityMap.find(diametr);
    if (it != diameterCapacityMap.end()) {
        // Возвращаем среднее значение из диапазона
        return (it->second.first + it->second.second) / 2.0;
    }

    // Для нестандартных диаметров используем аппроксимацию
    // Q ≈ k * D^2.5 (примерная зависимость из формулы)
    return 0.0001 * pow(diametr, 2.5);
}

// Метод для расчета веса для алгоритма Дейкстры
double Pipe::getWeight() const {
    if (repair) {
        return std::numeric_limits<double>::infinity();  // Труба в ремонте - бесконечный вес
    }

    // Вес = длина трубы (можно добавить другие факторы)
    // Меньший диаметр = большее сопротивление = больший "вес"
    double baseWeight = length;  // базовый вес = длина в км

    // Учет диаметра: меньший диаметр = больший вес
    if (diametr > 0) {
        baseWeight *= (1420.0 / diametr);  // нормализуем относительно максимального диаметра
    }

    return baseWeight;
}

// Метод для вывода информации о трубе
void Pipe::display() const {
    std::cout << "Pipe parameters" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Length: " << length << " km" << std::endl;
    std::cout << "Diametr: " << diametr << " mm" << std::endl;
    std::cout << "Capacity: " << getCapacity() << " mln. m³/day" << std::endl;
    std::cout << "Weight: " << getWeight() << " points" << std::endl;
    std::cout << "On repair: " << (repair ? "yes" : "no") << std::endl;
}

// метод для получения следующего ID
int Pipe::getNextId() {
    return nextId;
}