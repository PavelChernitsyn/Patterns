#include <iostream>
#include <vector>

using namespace std;

class Context;

class State{
protected:
    Context* context;
public:
    void setContext(Context* c){
        context = c;
    }
    virtual bool check(int val) = 0;
};

class Context{
protected:
    State* current_state;
public:
    Context(State* state):current_state(state){
        state->setContext(this);
    }
    void goToState(State* state){
        current_state = state;
        state->setContext(this);
    }
    
    vector<int> calc(vector<int> v){
        vector<int> result;
        for(auto x: v){
            if(current_state->check(x)){
                result.push_back(x);
            }
        }
        return result;
    }
};

class OddState: public State{
public:
    bool check(int val); 
};

class EvenState: public State{
public:
    bool check(int val);
};

bool OddState::check(int val){
    if(val % 2 != 0){
        context->goToState(new EvenState);
        return true;
    }
    else{
        return false;
    }
}

bool EvenState::check(int val){
    if(val % 2 == 0){
        context->goToState(new OddState);
        return true;
    }
    else{
        return false;
    }
}

int main(){
    vector<int> input = {1,2,4,-3,5,7,6,6,1,8,9,10,12,13,15};
    Context c(new EvenState);
    for(auto x: c.calc(input)){
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}