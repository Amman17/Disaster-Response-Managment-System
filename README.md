# 🛡️ Disaster Response Management System (DRMS)

A robust, object-oriented C++ command-line application designed to streamline emergency logistics, victim rescue, and resource allocation during catastrophic events. This system acts as a centralized **Operation Center** to manage real-time disaster data and responder deployment.

## 🚀 Overview

The **Disaster Response Management System** is built to handle the complexities of emergency situations like Earthquakes, Floods, Wildfires, and Cyclones. It allows administrators to register disaster events, track victims, manage specialized responders (Medics, Firefighters, Rescuers), and monitor resource levels with an integrated **Alert System**.

## ✨ Key Features

*   **Polymorphic Disaster Handling:** Specialized classes for different disaster types, calculating unique severity scores based on magnitude, water levels, or wind speeds.
*   **Dynamic Responder Deployment:** A recommendation engine that suggests the best responder type (e.g., Medics for Critical injuries, Firefighters for Wildfires).
*   **Intelligent Alert System:** Real-time monitoring for high-severity disasters, life-threatening victim status, and critical resource shortages.
*   **Zone-Based Operations:** Organize response efforts into specific geographic "Zones" for granular control.
*   **Automated Reporting:** Generate detailed system summaries including rescue success rates and inventory tracking.

## 🏗️ Technical Architecture

This project demonstrates advanced **Object-Oriented Programming (OOP)** concepts:

| Concept | Implementation |
| :--- | :--- |
| **Inheritance** | Base classes `DisasterEvent` and `Responder` with specialized subclasses. |
| **Abstraction** | Pure virtual functions for descriptions and response actions. |
| **Encapsulation** | Private data members with public getters/setters for system security. |
| **Friend Classes** | `ReportGenerator` acts as a friend to `OperationCenter` for deep data access. |
| **Memory Management** | Custom destructors for clean cleanup of dynamic objects. |

## 🛠️ Installation & Usage

### Prerequisites
*   A C++ compiler (GCC/G++, Clang, or MSVC).

### Steps
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/YourUsername/Disaster-Management-System.git](https://github.com/YourUsername/Disaster-Management-System.git)
