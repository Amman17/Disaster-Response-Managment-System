//models/Resource.h
#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>
#include <string>

using namespace std;

class Resource {
private:
    int id;
    string type;
    int quantity;
    bool isAvailable;

public:
    Resource(int i, string t, int qty) {
        id = i;
        type = t;
        quantity = qty;
        isAvailable = true;
    }

    ~Resource() {
        cout << "  Resource " << type << " record removed." << endl;
    }

    void allocate(int qty) {
        if (qty <= quantity) {
            quantity -= qty;
            cout << "  [+] " << qty << " units of " << type << " allocated." << endl;

            if (quantity == 0)
                isAvailable = false;
        } else {
            cout << "  [!] Not enough " << type << " available!" << endl;
        }
    }

    int getId() const { return id; }
    string getType() const { return type; }
    int getQuantity() const { return quantity; }
    bool getAvailability() const { return isAvailable; }

    void display() {
        cout << endl;
        cout << "------------------------" << endl;
        cout << "  ID        : " << id << endl;
        cout << "  Type      : " << type << endl;
        cout << "  Quantity  : " << quantity << endl;
        cout << "  Available : " << (isAvailable ? "Yes" : "No") << endl;
    }
};

#endif