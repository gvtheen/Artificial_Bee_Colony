/******************************************************************************
**
** Copyright (C) 2019-2031 Dr.Gui-lin Zhuang <glzhuang@zjut.edu.cn>
** All rights reserved.
**
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/
#include <iostream>
#include <cmath>
#include "CABCParameter.h"
#include "CABCEngine.h"
using namespace std;
using namespace ABCZJUT;
double test_function(const std::vector<double>& _value)
{
    double x1 =_value[0];
    double x2 =_value[1];
    return 0.5 + (sin(x1*x1-x2*x2)*sin(x1*x1-x2*x2) - 0.5)/((1+0.001*(x1*x1+x2*x2))*(1+0.001*(x1*x1+x2*x2)));
 }
int main()
{
    CABCParameter *abcpara=new CABCParameter();
    //abcpara->defaultInit();
    CABCEngine* newABC=new CABCEngine(abcpara,&test_function);
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
