# Flight Simulator – Object Adapter Pattern
**Language:** C++11 / C++14  
**Design Pattern:** Structural – Object Adapter (Wrapper)

---

## 1. Executive Summary

This project demonstrates a textbook implementation of the structural **Adapter Design Pattern** (Object-oriented variant) in C++. The primary objective of this codebase is to showcase how an existing system can seamlessly integrate incompatible third-party or legacy classes without modifying their original source code.

By utilizing polymorphism and composition, the system unifies a modern drone class (`ModernDrone`) and a traditional kite class (`Latawiec`) under a single control interface (`AirPlane`), managed by a centralized controller (`Operator`).

---

## 2. Architecture & Design Pattern Anatomy

The architecture resolves a common software engineering problem: **Interface Mismatch**. The `Operator` client class is designed to process objects that strictly adhere to the `AirPlane` interface. The introduction of the `Latawiec` class introduces a conflict, as its control methods do not match the expected signatures.

The **Adapter Pattern** bridges this gap by introducing an intermediary wrapper.

### Component Roles

| Pattern Component | Class Name | Responsibility |
| :--- | :--- | :--- |
| **Target** | `AirPlane` | Defines the domain-specific interface that the `Operator` uses. |
| **Client** | `Operator` | Manages a polymorphic collection (`std::vector<AirPlane*>`) and triggers mass operations. |
| **Adaptee** | `Latawiec` | The incompatible class that contains the required behavior but has a different interface. |
| **Adapter** | `AdapterLatawiec` | Adapts the interface of `Latawiec` to the `AirPlane` target interface via composition. |

### Structural Blueprint

```text
       ┌──────────────┐
       │   AirPlane   │◄────────────────────────┐
       └──────┬───────┘                         │
              ▲                                 │
              │ (Inherits)                      │ (Inherits)
              │                                 │
     ┌────────┴────────┐               ┌────────┴────────┐
     │   ModernDrone   │               │ AdapterLatawiec │
     └─────────────────┘               └────────┬────────┘
                                                │
                                                │ (Composes / Wraps)
                                                ▼
                                       ┌─────────────────┐
                                       │    Latawiec     │
                                       └─────────────────┘


```
## 3. Core Source Code


```text
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ==========================================
// TARGET INTERFACE
// ==========================================
class AirPlane {
public:
    // Virtual destructor ensures safe polymorphic deletion
    virtual ~AirPlane() = default;
    
    virtual void moveFront() = 0; 
    virtual void moveBack() = 0;
};

// ==========================================
// COMPATIBLE PRODUCT
// ==========================================
class ModernDrone : public AirPlane {
private:
    int xPosition;
    int yPosition;
    int zPosition;
    string id;

public:
    ModernDrone(int xPosition, int yPosition, int zPosition, string id) {
        this->xPosition = xPosition;
        this->yPosition = yPosition;
        this->zPosition = zPosition;
        this->id = id;
    }

    string getid()      { return id; }
    int getxPosition()  { return xPosition; }
    int getyPosition()  { return yPosition; }
    int getzPosition()  { return zPosition; }

    bool testPosition(int newPosition) {
        return (newPosition >= 1) && (newPosition <= 100);
    }

    void setZPosition(int zPosition) {
        if(testPosition(zPosition)) this->zPosition = zPosition;    
    }
    void setXPosition(int xPosition) {
        if(testPosition(xPosition)) this->xPosition = xPosition;
    }
    void setYPosition(int yPosition) {
        if(testPosition(yPosition)) this->yPosition = yPosition;
    }

    void moveFront() override {
        if(testPosition(yPosition + 1)) {
            yPosition++;
            cout << "Drone " << id << " leci " << yPosition << endl;
        }
    }
    void moveBack() override {
        if(testPosition(yPosition - 1)) {
            yPosition--;
        }
    }
};

// ==========================================
// INCOMPATIBLE ADAPTEE
// ==========================================
class Latawiec {
private:
    int xPosition;
    int yPosition;
    int zPosition;
    string id;
public:
    Latawiec(int xPosition, int yPosition, int zPosition, string id) {
        this->xPosition = xPosition;
        this->yPosition = yPosition;
        this->zPosition = zPosition;
        this->id = id;
    }

    void biegnij() {
        cout << id << " Latawiec leci" << endl;
        zPosition++;
        yPosition++;
    }

    void stop() {
        cout << "Latawiec zatrzymuje sie" << endl;
        zPosition = 0;
        yPosition--;
    }
};

// ==========================================
// THE ADAPTER (Object Variant)
// ==========================================
class AdapterLatawiec : public AirPlane {
private:
    Latawiec *latawiec; // Composition over inheritance
public:
    AdapterLatawiec(Latawiec *latawiec) {
        this->latawiec = latawiec;
    }
    
    void moveFront() override {
        latawiec->biegnij(); // Translation logic
    } 
    void moveBack() override {
        latawiec->stop();    // Translation logic
    }
};

// ==========================================
// CLIENT CONTEXT
// ==========================================
class Operator {
private:
    vector<AirPlane*> airPlane;
public:
    void addAirPlane(AirPlane *airPlane) {
        this->airPlane.push_back(airPlane);
    }

    void moveFront() {
        for(size_t i = 0; i < airPlane.size(); i++) {
            airPlane[i]->moveFront();
        }
    }

    void moveBack() {
        for(size_t i = 0; i < airPlane.size(); i++) {
            airPlane[i]->moveBack();
        }
    }
};

// ==========================================
// EXECUTION ENTRY POINT
// ==========================================
int main(int argc, char const *argv[]) {
    ModernDrone *modernDrone1 = new ModernDrone(0, 0, 0, "1");
    ModernDrone *modernDrone2 = new ModernDrone(0, 0, 0, "2");
    ModernDrone *modernDrone3 = new ModernDrone(0, 0, 0, "3");
    
    Latawiec *latawiec1 = new Latawiec(0, 0, 0, "2");
    Latawiec *latawiec2 = new Latawiec(0, 0, 0, "3");
    
    AdapterLatawiec *adapterLatawiec1 = new AdapterLatawiec(latawiec1);
    AdapterLatawiec *adapterLatawiec2 = new AdapterLatawiec(latawiec2);
    
    Operator *operator1 = new Operator();
    operator1->addAirPlane(modernDrone1);
    operator1->addAirPlane(modernDrone2);
    operator1->addAirPlane(modernDrone3);
    operator1->addAirPlane(adapterLatawiec1);
    operator1->addAirPlane(adapterLatawiec2);
    
    cout << "--- Execution Cycle 1 ---" << endl;
    operator1->moveFront();
    
    cout << "\n--- Execution Cycle 2 ---" << endl;
    operator1->moveFront();

    // Memory Cleanup Block
    delete modernDrone1; delete modernDrone2; delete modernDrone3;
    delete latawiec1; delete latawiec2;
    delete adapterLatawiec1; delete adapterLatawiec2;
    delete operator1;

    return 0;
}

```

## 4. Key Improvements Applied

The codebase was optimized to meet rigorous C++ development standards, eliminating bugs present in the initial draft:

Polymorphic Safety: Added virtual ~AirPlane() = default; to prevent undefined behavior and heap memory allocation leaks during deletion.

Scope Encapsulation: Fixed missing brace blocks {} in ModernDrone::moveFront(). This ensures terminal logging hooks execute conditionally upon validation success rather than systematically.

Parameter Scope Resolution: Resolved a bug in setYPosition() where a semantic typo caused the method to re-evaluate local state instead of incoming arguments.

Modern Keywords: Integrated the explicit override specifier to enlist compiler assistance in verifying virtual table bindings.

### Compilation
```bash

g++ -o adapter adapter.cpp

```


