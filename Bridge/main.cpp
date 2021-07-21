#include <iostream>

using namespace std;
// !Logic 
class Device{
protected:
    string name;
    bool flag;
public:
    Device(string name):name(name),flag(true){}
    virtual void turn(bool flag){
        this->flag = flag;
    }
    virtual bool isWork(){
        return flag;
    }
    virtual string getName(){
        return name;
    }

    virtual int getPower() = 0;
    virtual void setPower(int val) = 0;
    
};

class Radio: public Device{
    int power;
public:
    Radio(string name = "Radio", int power = 0):Device(name),power(power){}
    int getPower(){
        return power;
    }
    void setPower(int val){
        if(val < 0){
            power = 0;
            return;
        }
        if(val > 10){
            power = 10;
            return;
        }
        power = val;
    }
};

class Fridge: public Device{
    int power;
public:
    Fridge(string name = "Fridge", int power = 0):Device(name),power(power){}
    int getPower(){
        return power;
    }
    void setPower(int val){
        if(val < 1){
            power = 1;
            return;
        }
        if(val > 100){
            power = 100;
            return;
        }
        power = val;
    }
};

// !Interface
class DeviceController{
    Device* d;
public:
    DeviceController(Device* device):d(device){}
    void printInfo(){
        cout << "Device " << d->getName() << " turned ";
        if(d->isWork())
            cout << "on at power " << d->getPower() << endl;
        else
            cout << "off\n";
    }

    void setPower(int power){
        d->setPower(power);
    }

    void doublePower(){
        d->setPower(d->getPower() * 2);
    }

    void turn(){
        d->turn(!d->isWork());
    }
};

void f(Device* d){
    DeviceController ctrl(d);
    cout << "Step 1\n";
    ctrl.printInfo();
    ctrl.setPower(15);
    ctrl.doublePower();
    cout << "Step 2\n";
    ctrl.printInfo();
    ctrl.turn();
    cout << "Step 3\n";
    ctrl.printInfo();
}


int main(){
    Radio* radio = new Radio("My Radio", 3);
    Fridge* fridge = new Fridge();

    cout << "Radio control\n";
    f(radio);

    cout << "Fridge control\n";
    f(fridge);


    delete radio;
    delete fridge;
    return 0;
}