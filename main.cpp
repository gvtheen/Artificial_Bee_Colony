#include <iostream>
#include "CABCParameter.h"
#include "CABCEngine.h"
using namespace std;
using namespace ABCZJUT;
int main()
{
    CABCParameter *abcpara=new CABCParameter();
    //abcpara->defaultInit();
    CABCEngine* newABC=new CABCEngine(abcpara);
   // cout << "Hello world-1!" << endl;
    newABC->init();
   // cout << "Hello world-2!" << endl;
    newABC->evolve();
    //cout << "Hello world-3!" << endl;
    delete newABC;
   // cout << "Hello world-4!" << endl;
    delete abcpara;
    cout << "Hello world!" << endl;
    return 0;
}
