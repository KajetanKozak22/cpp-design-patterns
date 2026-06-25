#include <iostream>
#include <string>
#include <vector>

using namespace std;

class AirPlane {
public:

    virtual ~AirPlane() = default;
    
    virtual void moveFront() = 0; 
    virtual void moveBack() = 0;
};


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

    string getid() {
        return id;
    }
    int getxPosition() {
        return xPosition;
    }
    int getyPosition() {
        return yPosition;
    }
    int getzPosition() {
        return zPosition;
    }

    bool testPosition(int newPosition) {
        if((newPosition >= 1) && (newPosition <= 100)) 
            return true;
        else
            return false;
    }

    void setZPosition(int zPosition) {
        if(testPosition(zPosition)) 
            this->zPosition = zPosition;    
    }
    
    void setXPosition(int xPosition) {
        if(testPosition(xPosition)) 
            this->xPosition = xPosition;
    }
    

    void setYPosition(int yPosition) {
        if(testPosition(yPosition)) 
            this->yPosition = yPosition;
    }

    void moveFront() {
        if(testPosition(yPosition + 1)) {
            yPosition++;
            cout << "Drone " << id << " leci " << yPosition << endl;
        }
    }
    
    void moveBack() {
        if(testPosition(yPosition - 1)) {
            yPosition--;
        }
    }
};

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


class AdapterLatawiec : public AirPlane {
private:
    Latawiec *latawiec;
    
public:
    AdapterLatawiec(Latawiec *latawiec) {
        this->latawiec = latawiec;
    }
    
    void moveFront() override {
        latawiec->biegnij();
    }
    
    void moveBack() override {
        latawiec->stop();
    }
};

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


int main(int argc, char const *argv[])
{

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
    
    cout << "--- Pierwsze wywolanie moveFront ---" << endl;
    operator1->moveFront();
    
    cout << "\n--- Drugie wywolanie moveFront ---" << endl;
    operator1->moveFront();


    delete modernDrone1;
    delete modernDrone2;
    delete modernDrone3;
    delete latawiec1;
    delete latawiec2;
    delete adapterLatawiec1;
    delete adapterLatawiec2;
    delete operator1;

    return 0;
}