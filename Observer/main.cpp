#include <iostream>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

class ISubject;
// !Observer interface
class IObserver{
public:
    virtual void update(ISubject* sub) = 0;
};

// !Subject interface
class ISubject{
public:
    virtual void attach(IObserver* obs) = 0;
    virtual void detach(IObserver* obs) = 0;
    virtual void notify() = 0;
};

class StateMachine: public ISubject{
    set<IObserver*> obses;
public:
    int state;
    void attach(IObserver* obs){
        obses.insert(obs);
    }
    void detach(IObserver* obs){
        obses.erase(obs);
    }
    void notify(){
        for(auto x: obses){
            x->update(this);
        }
    }

    void setState(int val){
        cout << "State changed to " << val << endl;
        state = val;
        notify();
    }
};

// !Concrete observers
class Obs1: public IObserver{
    string name;
public:
    Obs1(string name):name(name){}
    void update(ISubject* sub){
        if(dynamic_cast<StateMachine*>(sub)->state % 2 == 0){
            cout << name << " reacted and said Hello\n";
        }
    }
};

class Obs2: public IObserver{
    string name;
public:
    Obs2(string name):name(name){}
    void update(ISubject* sub){
        if(dynamic_cast<StateMachine*>(sub)->state > 0 ){
            cout << name << " reacted and said Goodbye\n";
        }
    }
};

int main(){
    StateMachine* sm = new StateMachine;

    Obs1* o1_1 = new Obs1("Vasya");
    Obs1* o1_2 = new Obs1("Petya");
    Obs2* o2_1 = new Obs2("Kolya");

    sm->attach(o1_1);
    sm->attach(o1_2);
    sm->attach(o2_1);

    sm->setState(-2);
    sm->setState(3);
    sm->setState(4);
    cout << "--Remove Kolya--\n";
    sm->detach(o2_1);

    sm->setState(2);
}
