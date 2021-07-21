#include <iostream>
#include <typeinfo>

using namespace std;

// ! Prototype Interface
class Clonable{
public:
    virtual Clonable* makeCopy() = 0;
};

// ! What we want to clone
class ObjTypeA: public Clonable{
    Clonable* makeCopy(){
        return new ObjTypeA();
    }
};

class ObjTypeB: public Clonable{
    Clonable* makeCopy(){
        return new ObjTypeB();
    }
};


void f(Clonable* info){
    auto copy = info->makeCopy();
    cout << typeid(*copy).name() << endl;
}

int main(){
    f(new ObjTypeA());
    f(new ObjTypeB());
    return 0;
}
