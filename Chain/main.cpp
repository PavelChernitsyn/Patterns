#include <iostream>
#include <string>

using namespace std;

// !Chain
class IHandler{
public:
    virtual IHandler* setNextHandler(IHandler* handler) = 0;
    virtual IHandler* handle(string request) = 0;
};

class BaseHandler: public IHandler{
protected:
    IHandler* next;
public:
    IHandler* setNextHandler(IHandler* handler){
        next = handler;
        return next;
    }
    IHandler* handle(string request){
        if(!request.empty() && next != nullptr){
            return next->handle(request);
        }
        else{
            return nullptr;
        }
    }
};

class AdminHandler: public BaseHandler{
public:
    IHandler* handle(string request){
        if(request == "Admin"){
            cout << "Hello admin\n";
            return this;
        }
        else{
            return BaseHandler::handle(request);
        }
    }
};

class SUDOHandler: public BaseHandler{
public:
    IHandler* handle(string request){
        if(request == "SUDO"){
            cout << "You are SUDO\n";
            return this;
        }
        else{
            return BaseHandler::handle(request);
        }
    }
};

class RestrictHandler: public BaseHandler{
public:
    IHandler* handle(string request){
        if(request != "Agent"){
            cout << "Welcome user\n";
            return BaseHandler::handle(request);
        }
        else{
            return this;
        }
    }
};

int main(){
    AdminHandler* ah = new AdminHandler();
    SUDOHandler* sh = new SUDOHandler();
    RestrictHandler* rh = new RestrictHandler();

    ah->setNextHandler(rh)->setNextHandler(sh);

    cout << "--Agent--\n";
    ah->handle("Agent");
    cout << "--User--\n";
    ah->handle("User");
    cout << "--Admin--\n";
    ah->handle("Admin");
    cout << "--SUDO--\n";
    ah->handle("SUDO");

    return 0;
}
