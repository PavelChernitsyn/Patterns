#include <iostream>
#include <string>

using namespace std;

//!Receiver interface
class IReceiver{
public:
    virtual int doTask(int a, int b) = 0;
};

// !Concrete receivers
class Summator: public IReceiver{
public:
    int doTask(int a, int b){
        return a + b;
    }
};

class Producer: public IReceiver{
public:
    int doTask(int a, int b){
        return a * b;
    }
};

// !Comand interface
class ICommand{
public:
    virtual void execute() = 0;
};

// !Simple command
class Notifier: public ICommand{
    string msg;
public:
    Notifier(string msg):msg(msg){}
    void execute(){
        cout << msg << endl;
    }
};

// !Complex command
class ComplexTask: public ICommand{
    IReceiver* tasker;
    int a,b;
public:
    ComplexTask(IReceiver* r, int a, int b):tasker(r),a(a),b(b){}
    void execute(){
        cout << "Operation on " << a << " and " << b << " is " << tasker->doTask(a,b) << endl;
    }
};

class Invoker{
    ICommand* on_start;
    ICommand* on_finish;
    ICommand* main_com;
public:
    Invoker():on_start(nullptr),on_finish(nullptr),main_com(nullptr){}
    void setOnStart(ICommand* c){
        on_start = c;
    };
    void setOnFinish(ICommand* c){
        on_finish = c;
    }
    void setMain(ICommand* c){
        main_com = c;
    }

    void doSmth(){
        if(on_start){
            on_start->execute();
        }
        if(main_com){
            cout << "Doing main task:\n";
            main_com->execute();
        }
        if(on_finish){
            on_finish->execute();
        }
    }
};

int main(){
    Invoker me;
    cout << "--Empty Invoker--\n";
    me.doSmth();
    cout << "--Set start and finish command--\n";
    me.setOnStart(new Notifier("Hello!"));
    me.setOnFinish(new Notifier("Goodbye!"));
    me.doSmth();
    cout << "--Set summator as main--\n";
    me.setMain(new ComplexTask(new Summator(), 3, 4));
    me.doSmth();
    cout << "--Change finish to producer--\n";
    me.setOnFinish(new ComplexTask(new Producer(), 3,4));
    me.doSmth();
    cout << "--Delete start--\n";
    me.setOnStart(nullptr);
    me.doSmth();

    return 0;
}