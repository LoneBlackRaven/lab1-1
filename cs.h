#ifndef CS_H
#define CS_H

#include <string>
#include <iostream>

class Compress {
private:
    int id;
    static int nextId;
    std::string name;
    int count;
    int count_working;
    std::string classification;
    bool working;

public:
    // Конструктор по умолчанию
    Compress();

    // Конструктор с параметрами
    Compress(const std::string& name, int count, int count_working,
        const std::string& classification, bool working = false);

    // Методы для установки значений
    void setName(const std::string& newName);
    void setCount(int newCount);
    void setCountWorking(int newCountWorking);
    void setClassification(const std::string& newClassification);
    void setWorking(bool newWorking);

    // Методы для получения значений
    int getId() const;
    std::string getName() const;
    int getCount() const;
    int getCountWorking() const;
    std::string getClassification() const;
    bool getWorking() const;

    // Метод для расчета процента незадействованных цехов
    double getUnusedPercentage() const;

    // Метод для вывода информации о компрессорной станции
    void display() const;
};

#endif // CS_H