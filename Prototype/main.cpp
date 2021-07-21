#include <iostream>
#include <typeinfo>

using namespace std;

class BaseInfo{
    int a;
public:
    BaseInfo(int val):a(val){}
    virtual BaseInfo* makeCopy(){
        return new BaseInfo(*this);
    }
};

class ExtendedInfo: public BaseInfo{
    char c;
public:
    ExtendedInfo(char sym, int val):BaseInfo(val),c(sym){}
    virtual BaseInfo* makeCopy(){
        return new ExtendedInfo(*this);
    }
};

class FullInfo:public ExtendedInfo{
    bool e;
public:
    FullInfo(bool flag, char sym, int val):ExtendedInfo(sym, val){}
    virtual BaseInfo* makeCopy(){
        return new FullInfo(*this);
    }
};

void f(BaseInfo* info){
    auto copy = info->makeCopy();
    cout << typeid(*copy).name() << endl;
}

int main(){
    f(new BaseInfo(3));
    f(new FullInfo(true, 'a', 4));
    return 0;
}
