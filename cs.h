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
    // ����������� �� ���������
    Compress();

    // ����������� � �����������
    Compress(const std::string& name, int count, int count_working,
        const std::string& classification, bool working = false);

    // ������ ��� ��������� ��������
    void setName(const std::string& newName);
    void setCount(int newCount);
    void setCountWorking(int newCountWorking);
    void setClassification(const std::string& newClassification);
    void setWorking(bool newWorking);

    // ������ ��� ��������� ��������
    int getId() const;
    std::string getName() const;
    int getCount() const;
    int getCountWorking() const;
    std::string getClassification() const;
    bool getWorking() const;

    // ����� ��� ������� �������� ����������������� �����
    double getUnusedPercentage() const;

    // ����� ��� ������ ���������� � ������������� �������
    void display() const;
};

#endif // CS_H