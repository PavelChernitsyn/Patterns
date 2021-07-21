#include <iostream>

using namespace std;

class Resource{
    static Resource* r; 
    Resource(){
        cout << "Resource created\n";
    }
public:
    static Resource* getResource(){
        if(r == nullptr){
            cout << "Resource not exist... Creating\n";
            r = new Resource();
        }
        cout << "Return resource\n";
        return r;
    }
    static void reset(){
        delete r;
        r = nullptr;
    }
    ~Resource(){
        cout << "Resource destroyed";
        // ! optional
        //r = nullptr;
    }
};

Resource* Resource::r = nullptr;

void f(){
    auto r = Resource::getResource();
}

int main(){
    f();
    auto r = Resource::getResource();
    //auto another_r = *r;
    return 0;
}