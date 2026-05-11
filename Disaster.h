// ============================================================
// main.cpp  –  Disaster Management System
// ============================================================

#include <iostream>
#include <string>

// Utils first (UI helpers used everywhere)
#include "utils/utils.h"

// Models
#include "models/Disaster.h"   // DisasterEvent + Earthquake/Flood/Wildfire/Cyclone
#include "models/Responder.h"  // Responder + FireFighter/Medic/Rescuer
#include "models/Victim.h"     // Victim
#include "models/Resource.h"   // Resource
#include "models/Zone.h"       // Zone

// Core
#include "core/OperationCenter.h"
#include "core/ReportGenerator.h"

using namespace std;

// ============================================================
// MENU DISPLAY HELPERS
// ============================================================

void showMainMenu() {
    cout << "\n";
    printHeader("DISASTER MANAGEMENT SYSTEM");
    cout << "  [1]  Register Disaster Event\n";
    cout << "  [2]  Add Responder\n";
    cout << "  [3]  Register Victim\n";
    cout << "  [4]  Add Resource\n";
    cout << "  [5]  Create Zone\n";
    cout << "  [6]  Check Alerts\n";
    cout << "  [7]  Deploy to Zone\n";
    cout << "  [8]  Rescue a Victim\n";
    cout << "  [9]  View All Events\n";
    cout << "  [10] View All Responders\n";
    cout << "  [11] View All Victims\n";
    cout << "  [12] View All Resources\n";
    cout << "  [13] View All Zones\n";
    cout << "  [14] Quick Summary Report\n";
    cout << "  [15] Full Detailed Report\n";
    cout << "  [0]  Exit\n";
    printLine();
    cout << "  Enter your choice: ";
}

// ============================================================
// REGISTER DISASTER EVENT
// ============================================================

void handleRegisterEvent(OperationCenter& center) {
    printSubHeader("REGISTER DISASTER EVENT");

    cout << "  Select disaster type:\n";
    cout << "  [1] Earthquake\n";
    cout << "  [2] Flood\n";
    cout << "  [3] Wildfire\n";
    cout << "  [4] Cyclone\n";
    cout << "  Choice: ";

    int type = readMenuChoice();

    cout << "  Enter ID: ";
    int id; cin >> id;

    cout << "  Enter Location: ";
    string loc; cin.ignore(); getline(cin, loc);

    cout << "  Enter Date (DD/MM/YYYY): ";
    string date; getline(cin, date);

    cout << "  Enter Severity (1-5): ";
    int sev; cin >> sev;

    DisasterEvent* e = nullptr;

    if (type == 1) {
        float mag; int dep;
        cout << "  Magnitude: "; cin >> mag;
        cout << "  Depth (km): "; cin >> dep;
        e = new Earthquake(id, loc, date, sev, mag, dep);
    } else if (type == 2) {
        float wl, area;
        cout << "  Water Level (m): "; cin >> wl;
        cout << "  Affected Area (km2): "; cin >> area;
        e = new Flood(id, loc, date, sev, wl, area);
    } else if (type == 3) {
        float sr, ba;
        cout << "  Spread Rate (km/h): "; cin >> sr;
        cout << "  Burned Area (km2): "; cin >> ba;
        e = new Wildfire(id, loc, date, sev, sr, ba);
    } else if (type == 4) {
        float ws, rf;
        cout << "  Wind Speed (km/h): "; cin >> ws;
        cout << "  Rainfall (mm): "; cin >> rf;
        e = new Cyclone(id, loc, date, sev, ws, rf);
    } else {
        printWarning("Invalid type.");
        return;
    }

    center.registerEvent(e);
    printSuccess("Disaster event registered.");
}

// ============================================================
// ADD RESPONDER
// ============================================================

void handleAddResponder(OperationCenter& center) {
    printSubHeader("ADD RESPONDER");

    cout << "  Select type:\n";
    cout << "  [1] FireFighter\n";
    cout << "  [2] Medic\n";
    cout << "  [3] Rescuer\n";
    cout << "  Choice: ";
    int type = readMenuChoice();

    cout << "  Enter ID: ";
    int id; cin >> id;

    cout << "  Enter Name: ";
    string name; cin.ignore(); getline(cin, name);

    Responder* r = nullptr;

    if (type == 1) {
        cout << "  Equipment type: ";
        string eq; getline(cin, eq);
        r = new FireFighter(id, name, eq);
    } else if (type == 2) {
        cout << "  Medical unit: ";
        string unit; getline(cin, unit);
        r = new Medic(id, name, unit);
    } else if (type == 3) {
        cout << "  Rescue method: ";
        string method; getline(cin, method);
        r = new Rescuer(id, name, method);
    } else {
        printWarning("Invalid type.");
        return;
    }

    center.addResponder(r);
    printSuccess("Responder added.");
}

// ============================================================
// REGISTER VICTIM
// ============================================================

void handleAddVictim(OperationCenter& center) {
    printSubHeader("REGISTER VICTIM");

    cout << "  Enter ID: ";
    int id; cin >> id;

    cout << "  Enter Name: ";
    string name; cin.ignore(); getline(cin, name);

    cout << "  Enter Age: ";
    int age; cin >> age;

    cout << "  Injury severity:\n";
    cout << "  [1] Critical\n";
    cout << "  [2] Moderate\n";
    cout << "  [3] Minor\n";
    cout << "  Choice: ";
    int inj = readMenuChoice();

    string injury = (inj == 1) ? CRITICAL : (inj == 2) ? MODERATE : MINOR;

    center.addVictim(new Victim(id, name, age, injury));
    printSuccess("Victim registered.");
}

// ============================================================
// ADD RESOURCE
// ============================================================

void handleAddResource(OperationCenter& center) {
    printSubHeader("ADD RESOURCE");

    cout << "  Select resource type:\n";
    cout << "  [1] Ambulance\n";
    cout << "  [2] Food Packets\n";
    cout << "  [3] Water Bottles\n";
    cout << "  [4] Tents\n";
    cout << "  [5] Medical Supplies\n";
    cout << "  Choice: ";
    int type = readMenuChoice();

    string rtype;
    if      (type == 1) rtype = RES_AMBULANCE;
    else if (type == 2) rtype = RES_FOOD;
    else if (type == 3) rtype = RES_WATER;
    else if (type == 4) rtype = RES_TENT;
    else if (type == 5) rtype = RES_MEDICAL;
    else { printWarning("Invalid choice."); return; }

    cout << "  Enter ID: ";
    int id; cin >> id;

    cout << "  Enter Quantity: ";
    int qty; cin >> qty;

    center.addResource(new Resource(id, rtype, qty));
    printSuccess("Resource added.");
}

// ============================================================
// CREATE ZONE
// ============================================================

void handleCreateZone(OperationCenter& center) {
    printSubHeader("CREATE ZONE");

    cout << "  Enter ID: ";
    int id; cin >> id;

    cout << "  Enter Zone Name: ";
    string zname; cin.ignore(); getline(cin, zname);

    cout << "  Enter Location: ";
    string loc; getline(cin, loc);

    cout << "  Enter Severity (1-5): ";
    int sev; cin >> sev;

    cout << "  Disaster Type:\n";
    cout << "  [1] Earthquake  [2] Flood  [3] Wildfire  [4] Cyclone\n";
    cout << "  Choice: ";
    int dt = readMenuChoice();

    string dtype;
    if      (dt == 1) dtype = EARTHQUAKE;
    else if (dt == 2) dtype = FLOOD;
    else if (dt == 3) dtype = WILDFIRE;
    else if (dt == 4) dtype = CYCLONE;
    else { printWarning("Invalid type."); return; }

    center.createZone(new Zone(id, zname, loc, sev, dtype));
    printSuccess("Zone created.");
}

// ============================================================
// MAIN
// ============================================================

int main() {
    printHeader("WELCOME TO DISASTER MANAGEMENT SYSTEM");

    OperationCenter center("National Emergency HQ");
    ReportGenerator reporter;

    printSuccess("System Initialized.");

    int choice = -1;

    while (true) {
        showMainMenu();
        choice = readMenuChoice();

        if (choice == 0) {
            printHeader("SYSTEM SHUTTING DOWN");
            printSuccess("Goodbye!");
            break;
        }

        switch (choice) {
            case 1:  handleRegisterEvent(center);       break;
            case 2:  handleAddResponder(center);        break;
            case 3:  handleAddVictim(center);           break;
            case 4:  handleAddResource(center);         break;
            case 5:  handleCreateZone(center);          break;
            case 6:  center.checkAlerts();              break;
            case 7:  center.deployToZone();             break;
            case 8:  center.rescueVictim();             break;
            case 9:  center.showAllEvents();            break;
            case 10: center.showAllResponders();        break;
            case 11: center.showAllVictims();           break;
            case 12: center.showAllResources();         break;
            case 13: center.showAllZones();             break;
            case 14: center.showFullReport();           break;
            case 15: reporter.generateDetailedReport(center); break;
            default: printWarning("Invalid choice. Try again."); break;
        }
    }

    return 0;
}