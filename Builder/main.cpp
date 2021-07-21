#include <iostream>

using namespace std;

// * Our complex object
class CubicEq{
    double a,b,c,d;
public:
    CubicEq(double a = 0, double b = 0, double c = 0, double d = 0):a(a),b(b),c(c),d(d){}
    double operator()(double x){
        return a * x * x * x + b * x * x + c * x + d;
    }
    void setA(double val){ a = val;}
    void setB(double val){ b = val;}
    void setC(double val){ c = val;}
    void setD(double val){ d = val;}
};

// ! Builders
class CommonBuilder{
protected:
    CubicEq* eq;
public:
    CommonBuilder():eq(new CubicEq){}
    virtual void setA(double val) = 0;
    virtual void setB(double val) = 0;
    virtual void setC(double val) = 0;
    virtual void setD(double val) = 0;
    CubicEq* result(){
        return eq;
    }
    void reset(){
        delete eq;
        eq = new CubicEq();
    }
    ~CommonBuilder(){
        delete eq;
    }
};

class SquareBuilder: public CommonBuilder{
public:
    virtual void setA(double val){}
    virtual void setB(double val){eq->setB(val);}
    virtual void setC(double val){eq->setC(val);}
    virtual void setD(double val){eq->setD(val);}
};

class CubicSumBuilder: public CommonBuilder{
    virtual void setA(double val){eq->setA(val);}
    virtual void setB(double val){}
    virtual void setC(double val){}
    virtual void setD(double val){eq->setD(val);}
};

// ! Director
class Director{
    CommonBuilder* build_type;
public:
    Director(CommonBuilder* type): build_type(type){}
    void changeBuilderType(CommonBuilder* type){
        build_type = type;
    }
    CubicEq make(bool free_coeff){
        build_type->reset();
        build_type->setA(1);
        build_type->setB(2);
        build_type->setC(3);
        if(free_coeff)
            build_type->setD(4);
        return *build_type->result();
    }
};

int main(){
    SquareBuilder sqr;
    CubicSumBuilder cube;
    Director d(&sqr);
    auto f = d.make(true);
    cout << f(0) << " " << f(2) << endl;
    f = d.make(false);
    cout << f(0) << " " << f(2) << endl;
    d.changeBuilderType(&cube);
    f = d.make(true);
    cout << f(0) << " " << f(2) << endl;
    return 0;
}
