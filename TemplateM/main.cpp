#include <iostream>

using namespace std;

class AbstractMethod{
protected:
    int base1(int val){
        return val * 2;
    }
    int base2(int val){
        return val / 3;
    }
    virtual int hook1(int val){return val;}
    virtual int hook2(int val){return val;}
    virtual int req1(int val) = 0;
    virtual int req2(int val) = 0;
public:
    int calculate(int val){
        val = base1(val);
        val = req1(val);
        val = hook1(val);
        val = base2(val);
        val = req2(val);
        val = hook2(val);
        return val;
    };
};

class Method1: public AbstractMethod{
protected:
    int req1(int val){
        return val - 1;
    }
    int req2(int val){
        return val * 3;
    }
};

class Method2: public AbstractMethod{
protected:
    int req1(int val){
        return val + 1;
    }
    int req2(int val){
        return val + 2;
    }
    int hook2(int val){
        return --val;
    }
};

void f(AbstractMethod* m){
    cout << m->calculate(10) << endl;
}

int main(){
    f(new Method1);
    f(new Method2);
    return 0;
}