#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <iostream>

class Pipe {
private:
    int id;
    static int nextId;
    std::string name;
    float length;
    int diametr;
    bool repair;

public:
    // Конструктор по умолчанию
    Pipe();

    // Конструктор с параметрами
    Pipe(const std::string& name, float length, int diametr, bool repair = false);

    // Методы для установки значений
    void setName(const std::string& newName);
    void setLength(float newLength);
    void setDiametr(int newDiametr);
    void setRepair(bool newRepair);

    // Методы для получения значений
    int getId() const;
    std::string getName() const;
    float getLength() const;
    int getDiametr() const;
    bool getRepair() const;

    // Метод для вывода информации о трубе
    void display() const;

    // Статический метод для получения следующего ID
    static int getNextId();
};

#endif // PIPE_H