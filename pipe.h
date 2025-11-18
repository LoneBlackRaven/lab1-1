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
    //по умолчанию
    Pipe();

    //с параметрами
    Pipe(const std::string& name, float length, int diametr, bool repair = false);

    //установка значений
    void setName(const std::string& newName);
    void setLength(float newLength);
    void setDiametr(int newDiametr);
    void setRepair(bool newRepair);

    //получение значений
    int getId() const;
    std::string getName() const;
    float getLength() const;
    int getDiametr() const;
    bool getRepair() const;

    //вывод инфы
    void display() const;

    //айди
    static int getNextId();
};

#endif // PIPE_H