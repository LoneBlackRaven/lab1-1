#include "cs.h"

int Compress::nextId = 1;

// Конструктор по умолчанию
Compress::Compress() : id(nextId++), name("Not set"), count(0), count_working(0),
classification("Not set"), working(false) {
}

// Конструктор с параметрами
Compress::Compress(const std::string& name, int count, int count_working,
    const std::string& classification, bool working)
    : id(nextId++), name(name), count(count), count_working(count_working),
    classification(classification), working(working) {
}

// Методы для установки значений
void Compress::setName(const std::string& newName) { name = newName; }
void Compress::setCount(int newCount) { count = newCount; }
void Compress::setCountWorking(int newCountWorking) { count_working = newCountWorking; }
void Compress::setClassification(const std::string& newClassification) { classification = newClassification; }
void Compress::setWorking(bool newWorking) { working = newWorking; }

// Методы для получения значений
int Compress::getId() const { return id; }
std::string Compress::getName() const { return name; }
int Compress::getCount() const { return count; }
int Compress::getCountWorking() const { return count_working; }
std::string Compress::getClassification() const { return classification; }
bool Compress::getWorking() const { return working; }

// Метод для расчета процента незадействованных цехов
double Compress::getUnusedPercentage() const {
    if (count == 0) return 0.0;
    return ((count - count_working) * 100.0) / count;
}

// Метод для вывода информации о компрессорной станции
void Compress::display() const {
    std::cout << "=== CS parameters ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Quantity: " << count << std::endl;
    std::cout << "Working: " << count_working << std::endl;
    std::cout << "Unused percentage: " << getUnusedPercentage() << "%" << std::endl;
    std::cout << "Classification: " << classification << std::endl;
    std::cout << "CS is working: " << (working ? "yes" : "no") << std::endl;
}