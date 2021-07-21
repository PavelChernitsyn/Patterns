#include <iostream>

using namespace std;

// !Interface
class IDecorator{
public:
    virtual void execute() = 0;
};

// !Basic services
class HelloW: public IDecorator{
public:
    void execute(){
        cout << "Hello, World!";
    }
};

class GoodbyeW: public IDecorator{
public:
    void execute(){
        cout << "Goodbye, World!";
    }
};

// !Decorators
class BracketDeco: public IDecorator{
    IDecorator* obj;
public:
    BracketDeco(IDecorator* obj):obj(obj){}
    void execute(){
        cout << "[";
        obj->execute();
        cout << "]";
    }
};

class EndLineDeco: public IDecorator{
    IDecorator* obj;
public:
    EndLineDeco(IDecorator* obj):obj(obj){}
    void execute(){
        obj->execute();
        cout << endl;
    }
};

int main(){
    HelloW* f1 = new HelloW;
    f1->execute();
    IDecorator* dec1 = new EndLineDeco(new BracketDeco(f1));
    dec1->execute();
    IDecorator* dec2 = new BracketDeco(new GoodbyeW());
    dec2->execute();
    IDecorator* dec3 = new BracketDeco(new EndLineDeco(dec2));
    dec3->execute();
    return 0;
}