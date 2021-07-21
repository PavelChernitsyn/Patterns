#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// !Common interface
class DepartmentInterface{
public:
    virtual void who(int n = 0) = 0;
};

// !Leaf element
class BaseDepartment: public DepartmentInterface{
    string name;
public:
    BaseDepartment(string name):name(name){}
    void who(int n = 0){
        for(int i = 0; i < n; i++)
            cout << "  ";
        cout << "Base Department - " << name << endl;
    }
};

// !Composite element
class HeadDepartment: public DepartmentInterface{
    string name;
    vector<DepartmentInterface*> childs;
public:
    HeadDepartment(string name):name(name){}
    void who(int n = 0){
        for(int i = 0; i < n; i++)
            cout << "  ";
        cout << "Head Department - " << name << " have " << childs.size() << " departments\n";
        for(auto x: childs){
            x->who(n+1);
        }
    }
    void add(DepartmentInterface* dep){
        childs.push_back(dep);
    }
    void remove(DepartmentInterface* dep){
        auto pos = find(childs.begin(), childs.end(), dep);
        if(pos != childs.end()){
            delete *pos;
            childs.erase(pos);
        }
    }

    ~HeadDepartment(){
        for(auto x: childs){
            delete x;
        }
        childs.clear();
    }
};

int main(){
    HeadDepartment* h_dep1 = new HeadDepartment("Hello");
    h_dep1->add(new BaseDepartment("World"));
    h_dep1->add(new BaseDepartment("C++"));

    HeadDepartment* h_dep2 = new HeadDepartment("Goodbye");

    HeadDepartment* hh_dep = new HeadDepartment("MAIN");
    hh_dep->add(h_dep1);
    hh_dep->add(h_dep2);
    hh_dep->add(new BaseDepartment("NOT MAIN"));

    hh_dep->who();
    cout << "------\n";
    h_dep1->who();
    delete hh_dep;
    return 0;
}