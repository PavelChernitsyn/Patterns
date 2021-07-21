#include <iostream>

using namespace std;

// * Object logic

class IOperation{
public:
    virtual double op1(double a, double b) = 0;
    virtual double op2(double a, double b) = 0;
};

class MathOperation: public IOperation{
public:
    double op1(double a, double b){
        return a + b;
    }
    double op2(double a, double b){
        return a * b;
    }
};

class CompOperation: public IOperation{
public:
    double op1(double a, double b){
        return a > b ? a : b;
    }
    double op2(double a, double b){
        return a > b ? b : a;
    } 
};

// * Fabric logic
class OperationExecuter{
public:
    virtual void proceed(double a, double b){
        auto op = createOperation();
        cout << op->op1(a,b) << " " << op->op2(a,b) << endl;
    }
    virtual IOperation* createOperation() = 0;
};

class MathExecuter: public OperationExecuter{
public:
    IOperation* createOperation(){
        return new MathOperation();
    }
};

class CompExecuter: public OperationExecuter{
public:
    IOperation* createOperation(){
        return new CompOperation();
    }
};


// * Fabric caller
void calc(OperationExecuter* exec){
    exec->proceed(2.5, 4);
}

int main(){
    calc(new MathExecuter());
    calc(new CompExecuter());
    return 0;
}