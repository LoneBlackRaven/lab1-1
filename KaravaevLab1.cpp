#include <iostream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    float length;
    int diametr;
    bool repair;
};

struct Compress {
    string name;
    int count;
    int count_working;
    string classification;
    bool working;
};

void Menu(Pipe t, Compress c) {
    while (true)
    {
        cout << "\nChoose type:\n 1. Pipe \n 2. Compress\n 3. Show All\n";
        int type;
        cin >> type;
        switch (type)
        {
        case 1:
            cout << "Choose option:\n 1. Add pipe \n 2. Pipe lenght\n 3. Pipe diametr\n 4. Repairing\n";
            int option;
            cin >> option;
            switch (option)
            {
            case 1:
                cout << "Enter pipe name:";
                cin >> t.name;
                break;
            case 2:
                cout << "Enter pipe lenght (km): ";
                cin >> t.length;
                break;
            case 3:
                cout << "Enter pipe diametr (mm): ";
                cin >> t.diametr;
                break;
            case 4:
                cout << "Is pipe on repair? (0 - no, 1 - yes)";
                cin >> t.repair;
                break;
            }
            break;
        case 2:
            cout << "Choose option:\n 1. Add CS \n 2. Quantity of CS \n 3. Quantity working\n 4. Classification 5. Working\n";
            int option2;
            cin >> option2;
            switch (option2)
            {
            case 1:
                cout << "Enter CS name: ";
                cin >> c.name;
                break;
            case 2:
                cout << "Enter quantity of enterprises: ";
                cin >> c.count;
                break;
            case 3:
                cout << "Enter quantity of working enterprises: ";
                cin >> c.count_working;
                break;
            case 4:
                cout << "Enter classification: ";
                cin >> c.classification;
                break;
            case 5:
                cout << "Is CS working? (0 - no, 1 - yes) ";
                cin >> c.working;
                break;
            }
            break;
        case 3:
            cout << "\nPipe parameters: \n" << "Name: " << t.name << "\nLength: " << t.length << "\nDiametr: " << t.diametr << "\nOn repair: " << t.repair;
            cout << "\nCS parameters: \n" << "Name: " << c.name << "\nQuantity: " << c.count << "\nOn working: " << c.count_working << "\nClassification: " << c.classification << "\nWorking : " << c.working;
            break;
        }
    };
};

int main()
{
    Pipe truba;
    Compress ceh;
    Menu(truba, ceh);
}
