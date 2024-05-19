#include <iostream>
#include <string>
#include <variant>
class A{
    public:
    int &v;
    A(int &v):v(v){}
};
struct Rec
{
    const char *name;
    int cilCnt;
    int power;
    Rec(const char *name, int cilCnt, int power):name(name),cilCnt(cilCnt),power(power){}
    /* data */
};

class Car {
    Rec *r;
public:
    Car() {}
    Car& operator<<(int i){
        
    }
    Car& operator<<(Rec *c) {
        r = c;
        return *this;
    }
};

int main() {

    int x = 10;
    double y = 20.5;
    std::string z = "Hello";
    int i = 7;
    A a(i);
    Car f;
    Rec c("hhhh", 4, 6);
    f << 0 << c;
    return 0;
}
