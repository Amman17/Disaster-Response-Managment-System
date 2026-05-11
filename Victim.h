//models/Disaster.h
#pragma once
#include <iostream>
#include <string>
using namespace std;

// ============================================================
// MACROS - Injury severity levels
// ============================================================
#define CRITICAL "Critical"
#define MODERATE "Moderate"
#define MINOR    "Minor"

// ============================================================
// MACROS - Responder specializations
// ============================================================
#define MEDICAL      "Medical Aid"
#define SAR          "Search and Rescue"
#define FIREFIGHTER  "Fire Fighting"

// ============================================================
// MACROS - Disaster types
// ============================================================
#define FLOOD      "Flood"
#define EARTHQUAKE "Earthquake"
#define CYCLONE    "Cyclone"
#define WILDFIRE   "Wildfire"

// ============================================================
// MACROS - Resource types
// ============================================================
#define RES_AMBULANCE  "Ambulance"
#define RES_FOOD       "Food Packets"
#define RES_WATER      "Water Bottles"
#define RES_TENT       "Tents"
#define RES_MEDICAL    "Medical Supplies"

// ============================================================
// ALERT THRESHOLDS
// ============================================================
#define ALERT_SEVERITY_THRESHOLD  4
#define ALERT_RESOURCE_LOW        20

// ============================================================
// DISASTER BASE CLASS
// ============================================================
class DisasterEvent {
protected:
    int id;
    string name;
    string location;
    string date;
    int severity;

public:
    DisasterEvent(int i, string n, string loc, string d, int sev) {
        id = i; name = n; location = loc; date = d; severity = sev;
    }

    virtual ~DisasterEvent() {}

    virtual void getDescription() = 0;
    virtual int getSeverityScore() = 0;

    int getId() const { return id; }
    string getName() const { return name; }
    string getLocation() const { return location; }
    int getSeverity() const { return severity; }

    virtual void display() {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Location: " << location
             << " | Severity: " << severity << "/5" << endl;
    }
};

// ============================================================
// EARTHQUAKE
// ============================================================
class Earthquake : public DisasterEvent {
    float magnitude;
    int depth;

public:
    Earthquake(int i, string loc, string d, int sev, float mag, int dep)
        : DisasterEvent(i, EARTHQUAKE, loc, d, sev) {
        magnitude = mag; depth = dep;
    }

    void getDescription() {
        cout << "Earthquake M" << magnitude << " depth " << depth << "km\n";
    }

    int getSeverityScore() {
        return (int)(magnitude * severity);
    }
};

// ============================================================
// FLOOD
// ============================================================
class Flood : public DisasterEvent {
    float waterLevel;
    float affectedArea;

public:
    Flood(int i, string loc, string d, int sev, float wl, float area)
        : DisasterEvent(i, FLOOD, loc, d, sev) {
        waterLevel = wl; affectedArea = area;
    }

    void getDescription() {
        cout << "Flood water level " << waterLevel << "m\n";
    }

    int getSeverityScore() {
        return (int)(waterLevel * severity);
    }
};

// ============================================================
// WILDFIRE
// ============================================================
class Wildfire : public DisasterEvent {
    float spreadRate;
    float burnedArea;

public:
    Wildfire(int i, string loc, string d, int sev, float sr, float ba)
        : DisasterEvent(i, WILDFIRE, loc, d, sev) {
        spreadRate = sr; burnedArea = ba;
    }

    void getDescription() {
        cout << "Wildfire spread " << spreadRate << " km/h\n";
    }

    int getSeverityScore() {
        return (int)(spreadRate * severity);
    }
};

// ============================================================
// CYCLONE
// ============================================================
class Cyclone : public DisasterEvent {
    float windSpeed;
    float rainfall;

public:
    Cyclone(int i, string loc, string d, int sev, float ws, float rf)
        : DisasterEvent(i, CYCLONE, loc, d, sev) {
        windSpeed = ws; rainfall = rf;
    }

    void getDescription() {
        cout << "Cyclone wind " << windSpeed << " km/h\n";
    }

    int getSeverityScore() {
        return (int)(windSpeed / 10 * severity);
    }
};