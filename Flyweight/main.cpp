#include <iostream>
#include <vector>

using namespace std;
// !Common state
struct RGBA{
    double r;
    double g;
    double b;
};

// !State factory
class RGBAFactory{
    static vector<RGBA*> colors;
    static RGBAFactory* factory;
    RGBAFactory(){}
public:
    static RGBAFactory* getFactory(){
        if(!factory){
            factory = new RGBAFactory();
        }
        return factory;
    }

    RGBA* getColor(double r, double g, double b){
        for(auto x: colors){
            if(x->r == r && x->g == g && x->b == b){
                cout << "Color (" << r << "," << g << "," << b << ") exist\n";
                return x;
            }
        }

        cout << "Creating color (" << r << "," << g << "," << b << ")\n";
        RGBA* new_color = new RGBA{r,g,b};
        colors.push_back(new_color);
        return new_color;
    }

    static void reset(){
        for(auto x: colors){
            delete x;
        }
        colors.clear();
    }
    
};

vector<RGBA*> RGBAFactory::colors = vector<RGBA*>();
RGBAFactory* RGBAFactory::factory = nullptr;
// !Context
class Figure{
    int x;
    int y;
    RGBA* color;
public:
    Figure(double x, double y, double r = 0, double g = 0, double b = 0)
        :x(x),y(y),color(RGBAFactory::getFactory()->getColor(r,g,b))
    {
    }
};

// !Bad Context
class BadFigure{
    double x;
    double y;
    double r;
    double g;
    double b;
public:
    BadFigure(double x, double y, double r = 0, double g = 0, double b = 0)
        :x(x),y(y),r(r),g(g),b(b){}
};

int main(){
    
    for(int i = 0; i < 5; i++){
        auto f = Figure(i,i,0,128,255);
    }

    for(int i = 0; i < 5; i++){
        auto f = Figure(i,i,0,128,0);
    }

    for(int i = 0; i < 5; i++){
        auto f = Figure(i,i,0,128,255);
    }

    cout << "Size of BadFigure " << sizeof(BadFigure) << endl;
    cout << "Size of Figure " << sizeof(Figure) << endl;

    RGBAFactory::getFactory()->reset();
    return 0;
}
