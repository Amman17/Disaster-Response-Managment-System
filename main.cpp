#pragma once
#include <iostream>
#include <string>
#include"models/Disaster.h"
#include "models/Victim.h"
#include "models/Resource.h"
#include "models/Responder.h"
#include"models/Zone.h"
using namespace std;

// ============================================================
// OPERATION CENTER (HEADER-ONLY VERSION)
// ============================================================

class OperationCenter {
private:
    friend class ReportGenerator;

    string centerName;

    DisasterEvent* events[10];
    Responder* responders[10];
    Victim* victims[50];
    Resource* resources[10];
    Zone* zones[10];

    int eventCount;
    int responderCount;
    int victimCount;
    int resourceCount;
    int zoneCount;

    // ---------------- INTERNAL HELPERS ----------------
    string recommendResponderType(string disasterType);
    string recommendResource(int severity);
    Responder* findBestResponder(string injury);

public:
    OperationCenter(string name) {
        centerName = name;

        eventCount = 0;
        responderCount = 0;
        victimCount = 0;
        resourceCount = 0;
        zoneCount = 0;

        for (int i = 0; i < 10; i++) {
            events[i] = NULL;
            responders[i] = NULL;
            resources[i] = NULL;
            zones[i] = NULL;
        }
        for (int i = 0; i < 50; i++) {
            victims[i] = NULL;
        }
    }

    ~OperationCenter() {
        for (int i = 0; i < eventCount; i++) delete events[i];
        for (int i = 0; i < responderCount; i++) delete responders[i];
        for (int i = 0; i < victimCount; i++) delete victims[i];
        for (int i = 0; i < resourceCount; i++) delete resources[i];
        for (int i = 0; i < zoneCount; i++) delete zones[i];
    }

    // ========================================================
    // ADD / REGISTER FUNCTIONS
    // ========================================================

    void registerEvent(DisasterEvent* e) {
        if (eventCount < 10) events[eventCount++] = e;
    }

    void addResponder(Responder* r) {
        if (responderCount < 10) responders[responderCount++] = r;
    }

    void addVictim(Victim* v) {
        if (victimCount < 50) victims[victimCount++] = v;
    }

    void addResource(Resource* r) {
        if (resourceCount < 10) resources[resourceCount++] = r;
    }

    void createZone(Zone* z) {
        if (zoneCount < 10) zones[zoneCount++] = z;
    }

    // ========================================================
    // ALERT SYSTEM
    // ========================================================

    void checkAlerts() {
        for (int i = 0; i < eventCount; i++) {
            if (events[i] && events[i]->getSeverity() >= 4) {
                cout << "\n[ALERT] High severity disaster detected!\n";
            }
        }

        for (int i = 0; i < victimCount; i++) {
            if (victims[i] && victims[i]->getInjury() == "Critical" && !victims[i]->getRescued()) {
                cout << "\n[ALERT] Critical victim detected!\n";
            }
        }

        for (int i = 0; i < resourceCount; i++) {
            if (resources[i] && resources[i]->getQuantity() < 20) {
                cout << "\n[WARNING] Low resource stock!\n";
            }
        }
    }

    // ========================================================
    // DEPLOYMENT SYSTEM
    // ========================================================

    void deployToZone() {
        if (zoneCount == 0) return;

        Zone* z = zones[0]; // simplified default deployment

        for (int i = 0; i < responderCount; i++) {
            if (responders[i]) {
                z->deployResponder(responders[i]);
                responders[i]->respond();
                break;
            }
        }

        for (int i = 0; i < resourceCount; i++) {
            if (resources[i]) {
                z->allocateResource(resources[i], 5);
                break;
            }
        }
    }

    // ========================================================
    // RESCUE SYSTEM
    // ========================================================

    void rescueVictim() {
        for (int i = 0; i < victimCount; i++) {
            if (victims[i] && !victims[i]->getRescued()) {

                Responder* r = findBestResponder(victims[i]->getInjury());

                if (r) {
                    r->respond();
                    victims[i]->rescue();
                    break;
                }
            }
        }
    }

    // ========================================================
    // VIEW FUNCTIONS
    // ========================================================

    void showAllEvents() {
        for (int i = 0; i < eventCount; i++)
            if (events[i]) events[i]->display();
    }

    void showAllResponders() {
        for (int i = 0; i < responderCount; i++)
            if (responders[i]) responders[i]->display();
    }

    void showAllVictims() {
        for (int i = 0; i < victimCount; i++)
            if (victims[i]) victims[i]->display();
    }

    void showAllResources() {
        for (int i = 0; i < resourceCount; i++)
            if (resources[i]) resources[i]->display();
    }

    void showAllZones() {
        for (int i = 0; i < zoneCount; i++)
            if (zones[i]) zones[i]->display();
    }

    void showFullReport() {
        cout << "\n===== SYSTEM REPORT =====\n";
        cout << "Events: " << eventCount << endl;
        cout << "Responders: " << responderCount << endl;
        cout << "Victims: " << victimCount << endl;
        cout << "Resources: " << resourceCount << endl;
        cout << "Zones: " << zoneCount << endl;
    }

    // ========================================================
    // FRIEND ACCESS HELPERS
    // ========================================================

    int getEventCount() { return eventCount; }
    int getResponderCount() { return responderCount; }
    int getVictimCount() { return victimCount; }
    int getResourceCount() { return resourceCount; }
    int getZoneCount() { return zoneCount; }

    DisasterEvent* getEvent(int i) { return events[i]; }
    Responder* getResponder(int i) { return responders[i]; }
    Victim* getVictim(int i) { return victims[i]; }
    Resource* getResource(int i) { return resources[i]; }
    Zone* getZone(int i) { return zones[i]; }

    string getCenterName() { return centerName; }
};

// ============================================================
// INTERNAL HELPERS (IMPLEMENTED INLINE)
// ============================================================

inline string OperationCenter::recommendResponderType(string disasterType) {
    if (disasterType == "Wildfire") return "FireFighter";
    if (disasterType == "Flood") return "Rescuer";
    if (disasterType == "Earthquake") return "Rescuer";
    if (disasterType == "Cyclone") return "Medic";
    return "Rescuer";
}

inline string OperationCenter::recommendResource(int severity) {
    if (severity >= 4) return "Ambulance";
    if (severity == 3) return "Medical Supplies";
    return "Food Packets";
}

inline Responder* OperationCenter::findBestResponder(string injury) {
    for (int i = 0; i < responderCount; i++) {
        if (responders[i]) return responders[i];
    }
    return NULL;
}