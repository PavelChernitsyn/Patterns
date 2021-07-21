#include <iostream>
#include <string>

using namespace std;
// !Mediator interface
class IMediator{
public:
    virtual void notify(string com) = 0;
};

// !Components
class BaseComponent{
protected:
    IMediator* mediator;
public:
    BaseComponent(IMediator* m = nullptr):mediator(m){}
    void setMediator(IMediator* m){
        mediator = m;
    }
};

class Component1: public BaseComponent{
public:
    Component1():BaseComponent(){}
    void doA(){
        cout << "Component 1 do A\n";
        if(mediator){
            mediator->notify("A");
        }
    }
    void doB(){
        cout << "Component 1 do B\n";
        if(mediator){
            mediator->notify("B");
        }
    }
};

class Component2: public BaseComponent{
public:
    Component2():BaseComponent(){}
    void doC(){
        cout << "Component 2 do C\n";
        if(mediator){
            mediator->notify("C");
        }
    }
    void doD(){
        cout << "Component 2 do D\n";
        if(mediator){
            mediator->notify("D");
        }
    }
};

// !Mediator
class ConcreteMediator: public IMediator{
    Component1* component1;
    Component2* component2;
public:
    ConcreteMediator(Component1* component1, Component2* component2):component1(component1),component2(component2){;
        component1->setMediator(this);
        component2->setMediator(this);
    }
    void notify(string what){
        if (what == "A"){
            cout << "Mediator react on A and trigger C\n";
            component2->doC();
        }

        if (what == "D")
        {
            cout << "Mediator react on D and trigger B & C\n";
            component1->doB();
            component2->doC();
        }
    }
};

int main(){
    Component1* c1 = new Component1();
    Component2* c2 = new Component2();

    ConcreteMediator* m = new ConcreteMediator(c1,c2);
    cout << "--Call Component 1 A--\n";
    c1->doA();

    cout << "--Call Component 2 D--\n";
    c2->doD();
}