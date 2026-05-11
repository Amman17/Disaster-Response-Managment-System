//models/Responder.h
#ifndef RESPONDER_H
#define RESPONDER_H

#include <iostream>
#include <string>

using namespace std;

// ============================================================
// MACROS - Responder specializations
// ============================================================
#define MEDICAL      "Medical Aid"
#define SAR          "Search and Rescue"
#define FIREFIGHTER  "Fire Fighting"

// ============================================================
// MACROS - Disaster types (needed for matching logic)
// ============================================================
#define FLOOD      "Flood"
#define EARTHQUAKE "Earthquake"
#define CYCLONE    "Cyclone"
#define WILDFIRE   "Wildfire"

// ============================================================
// ABSTRACT BASE CLASS - Responder
// ============================================================

class Responder {
protected:
    int id;
    string name;
    string specialization;
    bool isAvailable;

public:
    Responder(int i, string n, string spec) {
        id = i;
        name = n;
        specialization = spec;
        isAvailable = true;
    }

    virtual ~Responder() {
        cout << "  Responder " << name << " removed." << endl;
    }

    virtual void respond() = 0;

    int getId() const { return id; }
    string getName() const { return name; }
    bool getAvailability() const { return isAvailable; }

    string getSpecialization() const {
        return specialization;
    }

    void setAvailability(bool status) {
        isAvailable = status;
    }

    bool matchesDisaster(string disasterType) {
        if (specialization == FIREFIGHTER) {
            return (disasterType == WILDFIRE);
        }
        if (specialization == MEDICAL) {
            return (disasterType == EARTHQUAKE ||
                    disasterType == FLOOD ||
                    disasterType == CYCLONE);
        }
        if (specialization == SAR) {
            return true;
        }
        return false;
    }

    virtual void display() {
        cout << endl;
        cout<<"-------------------------------------"<<endl;
        cout << "  ID             : " << id << endl;
        cout << "  Name           : " << name << endl;
        cout << "  Specialization : " << specialization << endl;
        cout << "  Available      : " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// ============================================================
// SUBCLASS 1 - FireFighter
// ============================================================

class FireFighter : public Responder {
private:
    string equipmentType;

public:
    FireFighter(int i, string n, string equip)
        : Responder(i, n, FIREFIGHTER) {
        equipmentType = equip;
    }

    ~FireFighter() {
        cout << "  FireFighter " << name << " removed." << endl;
    }

    void respond() {
        cout << "  " << name << " is fighting the fire using " 
             << equipmentType << endl;
        isAvailable = false;
    }

    void display() {
        Responder::display();
        cout << "  Equipment : " << equipmentType << endl;
    }
};

// ============================================================
// SUBCLASS 2 - Medic
// ============================================================

class Medic : public Responder {
private:
    string medicalUnit;

public:
    Medic(int i, string n, string unit)
        : Responder(i, n, MEDICAL) {
        medicalUnit = unit;
    }

    ~Medic() {
        cout << "  Medic " << name << " removed." << endl;
    }

    void respond() {
        cout << "  " << name << " is providing medical aid from " 
             << medicalUnit << endl;
        isAvailable = false;
    }

    void display() {
        Responder::display();
        cout << "  Medical Unit : " << medicalUnit << endl;
    }
};

// ============================================================
// SUBCLASS 3 - Rescuer
// ============================================================

class Rescuer : public Responder {
private:
    string rescueMethod;

public:
    Rescuer(int i, string n, string method)
        : Responder(i, n, SAR) {
        rescueMethod = method;
    }

    ~Rescuer() {
        cout << "  Rescuer " << name << " removed." << endl;
    }

    void respond() {
        cout << "  " << name << " is rescuing victims using " 
             << rescueMethod << endl;
        isAvailable = false;
    }

    void display() {
        Responder::display();
        cout << "  Rescue Method : " << rescueMethod << endl;
    }
};

#endif