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
    // ����������� �� ���������
    Pipe();

    // ����������� � �����������
    Pipe(const std::string& name, float length, int diametr, bool repair = false);

    // ������ ��� ��������� ��������
    void setName(const std::string& newName);
    void setLength(float newLength);
    void setDiametr(int newDiametr);
    void setRepair(bool newRepair);

    // ������ ��� ��������� ��������
    int getId() const;
    std::string getName() const;
    float getLength() const;
    int getDiametr() const;
    bool getRepair() const;

    // ����� ��� ������ ���������� � �����
    void display() const;

    // ����������� ����� ��� ��������� ���������� ID
    static int getNextId();
};

#endif // PIPE_H