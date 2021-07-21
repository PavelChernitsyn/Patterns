#include <iostream>
#include <vector>

using namespace std;

//!Strategy
class IStrategy{
public:
    virtual void print(vector<int> v) = 0;
};

class EvenPrinter: public IStrategy{
public:
    void print(vector<int> v){
        for(auto x: v){
            if(x % 2 == 0)
                cout << x;
            cout << ' ';
        }
        cout << endl;
    }
};

class NewLinePrinter: public IStrategy{
public:
    void print(vector<int> v){
        for(auto x: v){
            cout << x << endl;
        }
    }
};

// !Context
class Fibonachi{
    IStrategy* strat;
public:
    Fibonachi(IStrategy* strat = new NewLinePrinter):strat(strat){}
    void setStrategy(IStrategy* strat){
        this->strat = strat;
    }
    void calc(int n){
        vector<int> row = {0,1};
        for(int i = 1; i <= n; i++){
            int temp = row[i-1] + row[i];
            row.push_back(temp);
        }
        strat->print(row);
    }
};

int main(){
    Fibonachi f;
    f.calc(10);
    f.setStrategy(new EvenPrinter());
    f.calc(10);
    return 0;
}