#include <iostream>
#include <time.h>
#include <string>

using namespace std;

// !SubSystems
class IntGenerator{
public:
    IntGenerator(){
        srand(time(NULL));
    }

    int generate(){
        return rand()%100;
    }
};

class Printer{
public:
    Printer(){}
    void printInt(const int& val){
        cout << "Int value = " << val << endl;
    }
    void printStr(const string& str){
        cout << "String value = " << str << endl;
    }
};
// !Facade to work with int values
class UserFacade{
    IntGenerator* generator;
    Printer* printer;
public:
    UserFacade():generator(new IntGenerator),printer(new Printer){}
    ~UserFacade(){
        delete generator;
        delete printer;
    }
    void printGen(){
        printer->printInt(generator->generate());
    }
    void printSqrInt(int val){
        printer->printInt(val*val);
    }
    double getNormalizedValue(){
        double value = generator->generate();
        return value / 100.0;
    }
};

int main(){
    UserFacade facade;
    facade.printGen();
    facade.printGen();
    facade.printSqrInt(-2);
    facade.printSqrInt(13);
    cout << facade.getNormalizedValue() << endl;
    return 0;
}