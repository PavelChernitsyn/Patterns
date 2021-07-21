#include <iostream>
#include <math.h>

using namespace std;

class IVisitor;
class Point2D;
class Point3D;

class IComponent{
public:
    virtual void Accept(IVisitor* visitor) = 0;
};

class IVisitor{
public:
    virtual void visitPoint2D(Point2D* element) = 0;
    virtual void visitPoint3D(Point3D* element) = 0;
};

class Point2D: public IComponent{
    int x,y;
public:
    Point2D(int x = 0, int y = 0):x(x),y(y){}
    void Accept(IVisitor* visitor){
        visitor->visitPoint2D(this);
    }
    int getX() const{
        return x;
    }
    int getY() const{
        return y;
    }
    void setX(int val){
        x = val;
    }
    void setY(int val){
        y = val;
    }
};

class Point3D: public IComponent{
    int x,y,z;
public:
    Point3D(int x = 0, int y = 0, int z = 0):x(x),y(y),z(z){}
    void Accept(IVisitor* visitor){
        visitor->visitPoint3D(this);
    }
    int getX() const{
        return x;
    }
    int getY() const{
        return y;
    }
    int getZ() const{
        return z;
    }
    void setX(int val){
        x = val;
    }
    void setY(int val){
        y = val;
    }
    void setZ(int val){
        z = val;
    }
}; 

class Distance: public IVisitor{
    void visitPoint2D(Point2D* element){
        int x = element->getX();
        int y = element->getY();
        cout << sqrt(x*x + y*y) << endl;
    }
    void visitPoint3D(Point3D* element){
        int x = element->getX();
        int y = element->getY();
        int z = element->getZ();
        cout << sqrt(x*x + y*y + z*z) << endl; 
    }
};

class Reverse: public IVisitor{
    void visitPoint2D(Point2D* element){
        element->setX(-element->getX());
        element->setY(-element->getY());
    }
    void visitPoint3D(Point3D* element){
        element->setX(-element->getX());
        element->setY(-element->getY());
        element->setZ(-element->getZ());
    }
};

class Printer: public IVisitor{
    void visitPoint2D(Point2D* element){
        cout << "{" << element->getX() << ";" << element->getY() << "}\n";
    }
    void visitPoint3D(Point3D* element){
        cout << "{" << element->getX() << ";" << element->getY() << ";" << element->getZ() << "}\n";
    }
};

void f(IComponent* component){
    component->Accept(new Printer);
    component->Accept(new Distance);
    component->Accept(new Reverse);
    component->Accept(new Printer);
}

int main(){
    cout << "--Point2D--\n";
    f(new Point2D(2,3));
    cout << "--Point3D--\n";
    f(new Point3D(-1,2,4));
    return 0;
}
