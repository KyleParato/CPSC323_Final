#include <iostream>
using namespace std;
int main(){
    int pr;
    int p1;
    int p2q;
    p1=33;
    p2q=412;
    pr=p1/p2q;
    std::cout << pr << "\n";
    pr=p1*(p2q+2*pr);
    std::cout << "value=" << pr << "\n";
    return 0;
}
