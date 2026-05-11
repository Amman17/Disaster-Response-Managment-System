//models/Victim.h
#pragma once
#include <iostream>
#include <string>

using namespace std;

// ============================================================
// CLASS - Victim
// ============================================================

class Victim {
private:
    int id;
    string name;
    int age;
    string injurySeverity;
    bool isRescued;

public:
    Victim(int i, string n, int a, string injury) {
        id = i;
        name = n;
        age = a;
        injurySeverity = injury;
        isRescued = false;
    }

    ~Victim() {
        cout << "  Victim " << name << " record removed." << endl;
    }

    void rescue() {
        isRescued = true;
        cout << "  " << name << " has been rescued!" << endl;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    bool getRescued() const { return isRescued; }
    string getInjury() const { return injurySeverity; }

    void display() {
        cout << endl;
        printLine('-');
        cout << "  ID       : " << id << endl;
        cout << "  Name     : " << name << endl;
        cout << "  Age      : " << age << endl;
        cout << "  Injury   : " << injurySeverity << endl;
        cout << "  Rescued  : " << (isRescued ? "Yes" : "No") << endl;
    }
};