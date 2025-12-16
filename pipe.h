#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <iostream>
#include <limits>
#include <map>

class Pipe {
private:
    int id;
    static int nextId;
    std::string name;
    float length;
    int diametr;
    bool repair;

public:
    // Конструкторы
    Pipe();
    Pipe(const std::string& name, float length, int diametr, bool repair);

    // Установка значений
    void setName(const std::string& newName);
    void setLength(float newLength);
    void setDiametr(int newDiametr);
    void setRepair(bool newRepair);

    // Получение значений
    int getId() const;
    std::string getName() const;
    float getLength() const;
    int getDiametr() const;
    bool getRepair() const;

    // Новые методы для расчета
    double getCapacity() const;  // Производительность (млн. м³/сут)
    double getWeight() const;    // Вес для алгоритма Дейкстры

    // Вывод информации
    void display() const;

    // ID
    static int getNextId();
};

#endif // PIPE_H