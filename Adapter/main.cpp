#include <iostream>

#include<vector>
#include<list>

using namespace std;

class MaxFinder1{
public:
    int find(int* mas, int len){
        int max = mas[0];
        for(int i = 1; i < len; i++){
            if(mas[i] > max)
                max = mas[i];
        }
        return max;
    }
};

class MaxFinder2{
public:
    int find(list<int> mas){
        mas.sort();
        return mas.back();
    }
};

class IAdapter{
public:
    virtual int operate(vector<int> mas) = 0;
};

class Adapter1: public IAdapter{
    MaxFinder1 service;
public:
    int operate(vector<int> mas){
        int len = mas.size();
        int* _mas = new int[len];
        for(int i = 0; i < len; i++){
            _mas[i] = mas.at(i);
        }
        int result = service.find(_mas, len);
        delete[] _mas;
        return result;
    }
};

class Adapter2: public IAdapter{
    MaxFinder2 service;
public:
    int operate(vector<int> mas){
        list<int> _mas;
        for(auto x: mas){
            _mas.push_back(x);
        }
        return service.find(_mas);
    }
};

void f(IAdapter* service){
    vector<int> vec = {3,1,-4,2,12,2};

    cout << service->operate(vec) << endl;
}

int main(){    

    IAdapter* service = new Adapter1;
    f(service);
    delete service;

    service = new Adapter2;
    f(service);
    delete service;

    return 0;
}
