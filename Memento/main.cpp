#include <iostream>
#include <vector>

using namespace std;

class Originator;

class IMemento{
public:
    virtual void restore() = 0;
    virtual void print() = 0;
};

class MyMemento: public IMemento{
    Originator* origin;
    int v,dv;
public:
    MyMemento(int v, int dv, Originator* o):origin(o),v(v),dv(dv){}
    void print(){
        cout << "v = " << v << " - dv = " << dv << endl;
    }
    void restore();
};

class Originator{
    int v;
    int dv;
    void setState(int v, int dv){
        this->v = v;
        this->dv = dv;
    }
public:
    Originator(int val = 0):v(val),dv(1){}
    int getV() const{
        return v;
    }
    void setDV(int val){
        dv = val;
    }
    void doTask(){
        v += dv;
    }

    IMemento* save(){
        return new MyMemento(v,dv,this);
    }
    
    friend class MyMemento;
};

void MyMemento::restore(){
    origin->setState(v,dv);
}

class Caretaker{
    vector<IMemento*> saves;
public:
    void save(IMemento* m){
        saves.push_back(m);
    }
    void  undo(size_t n){
        size_t len = saves.size();
        if(len-1-n >= 0){
            saves.at(len-1-n)->restore();
        }
    }
    void print(){
        for(auto x: saves){
            x->print();
        }
    }
};

int main(){
    Originator origin;
    Caretaker saver;
    saver.save(origin.save());
    for(int i = 0; i < 5; i++){
        origin.doTask();
        saver.save(origin.save());
    }
    origin.setDV(3);
    for(int i = 0; i < 5; i++){
        origin.doTask();
        saver.save(origin.save());
    }
    saver.undo(7);
    origin.setDV(2);
    saver.save(origin.save());
    for(int i = 0; i < 5; i++){
        origin.doTask();
        saver.save(origin.save());
    }
    saver.print();
    return 0;
}