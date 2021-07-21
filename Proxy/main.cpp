#include <iostream>

using namespace std;


// !Service interface
class IService{
public:
    virtual void printNum(int num) = 0;
};
// !Standart interface
class Service: public IService{
public:
    void printNum(int num){
        cout <<  num << endl;
    }
};

// !Proxies for service
class CountService: public IService{
    Service service;
    static int count;
public:
    void printNum(int num){
        cout << ++count << ' ';
        service.printNum(num);
    }
};

int CountService::count = 0;

class EvenService: public IService{
    Service service;
public:
    void printNum(int num){
        if(num%2 == 0)
            service.printNum(num);
    }
};

void f(IService* service){
    for(int i = 0; i <= 4; i++)
        service->printNum(i);
}

int main(){
    cout << "Count Service\n";
    f(new CountService());
    cout << "Standart Service\n";
    f(new Service());
    cout << "Count Service\n";
    f(new CountService());
    cout << "Even check Service\n";
    f(new EvenService());
    return 0;
}
