#include "pipe.h"

int Pipe::nextId = 1;

// ����������� �� ���������
Pipe::Pipe() : id(nextId++), name("Not set"), length(0.0f), diametr(0), repair(false) {}

// ����������� � �����������
Pipe::Pipe(const std::string& name, float length, int diametr, bool repair)
    : id(nextId++), name(name), length(length), diametr(diametr), repair(repair) {
}

// ������ ��� ��������� ��������
void Pipe::setName(const std::string& newName) { name = newName; }
void Pipe::setLength(float newLength) { length = newLength; }
void Pipe::setDiametr(int newDiametr) { diametr = newDiametr; }
void Pipe::setRepair(bool newRepair) { repair = newRepair; }

// ������ ��� ��������� ��������
int Pipe::getId() const { return id; }
std::string Pipe::getName() const { return name; }
float Pipe::getLength() const { return length; }
int Pipe::getDiametr() const { return diametr; }
bool Pipe::getRepair() const { return repair; }

// ����� ��� ������ ���������� � �����
void Pipe::display() const {
    std::cout << "=== Pipe parameters ===" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Length: " << length << " km" << std::endl;
    std::cout << "Diametr: " << diametr << " mm" << std::endl;
    std::cout << "On repair: " << (repair ? "yes" : "no") << std::endl;
}

// ����������� ����� ��� ��������� ���������� ID
int Pipe::getNextId() {
    return nextId;
}