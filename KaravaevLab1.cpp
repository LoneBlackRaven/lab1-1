#include <iostream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    float length;
    int diametr;
    bool repair;
};

void check() {
    cout << "Error!" << endl;
    cout << "Write correct data" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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
        if (cin.fail() || type>3 || type < 1) {
            check();
        }
        switch (type)
        {
        case 1:
            cout << "Choose option:\n 1. Add pipe \n 2. Pipe lenght\n 3. Pipe diametr\n 4. Repairing\n 5. Edit\n";
            int option;
            cin >> option;
            if (cin.fail() || option > 4 || option < 1) {
                check();
            }
            switch (option)
            {
            case 1:
                cout << "Enter pipe name:";
                cin >> t.name;
            case 2:
                cout << "Enter pipe lenght (km): ";
                cin >> t.length;
                if (cin.fail() || t.length <=0) {
                    check();
                }
            case 3:
                cout << "Enter pipe diametr (mm): ";
                cin >> t.diametr;
                if (cin.fail() || t.diametr <= 0) {
                    check();
                }
            case 4:
                cout << "Is pipe on repair? (0 - no, 1 - yes)";
                int trig;
                cin >> trig;
                if (cin.fail() || (trig != 1 && trig != 0)) {
                    check();
                }
                t.repair = trig;
            }
            break;
        case 2:
            cout << "Choose option:\n 1. Add CS \n 2. Quantity of CS \n 3. Quantity working\n 4. Classification\n 5. Working\n";
            int option2;
            cin >> option2;
            if (cin.fail() || option2 > 5 || option2 < 1) {
                check();
            }
            switch (option2)
            {
            case 1:
                cout << "Enter CS name: ";
                cin >> c.name;
            case 2:
                cout << "Enter quantity of enterprises: ";
                cin >> c.count;
                if (cin.fail() || c.count <= 0) {
                    check();
                }
            case 3:
                cout << "Enter quantity of working enterprises: ";
                cin >> c.count_working;
                if (cin.fail() || c.count_working < 0 || c.count_working > c.count) {
                    check();
                }
            case 4:
                cout << "Enter classification: ";
                cin >> c.classification;
            case 5:
                cout << "Is CS working? (0 - no, 1 - yes) ";
                int trig1;
                cin >> trig1;
                if (cin.fail() || (trig1 != 0 && trig1 !=1)) {
                    check();
                }
            }
            break;
        case 3:
            cout << "\nPipe parameters: \n" << "Name: " << t.name << "\nLength: " << t.length << "\nDiametr: " << t.diametr << "\nOn repair: " << t.repair;
            cout << "\n\nCS parameters: \n" << "Name: " << c.name << "\nQuantity: " << c.count << "\nOn working: " << c.count_working << "\nClassification: " << c.classification << "\nWorking : " << c.working;
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
