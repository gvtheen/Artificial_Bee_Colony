#include <cmath>
#include "CABCEvaluator.h"
#include "CBeebase.h"
#include "CHoney.h"

namespace ABCZJUT{

CABCEvaluator::CABCEvaluator()
{
    //ctor
}

CABCEvaluator::~CABCEvaluator()
{
    //dtor
}

//void CABCEvaluator::run()
//{
//
//}
void CABCEvaluator::evaluate(CBeebase* pBee,bool is_1st_run)
{
   CHoney* honey=nullptr;

   if(is_1st_run==true)
       honey = pBee->HoneyOfBeecolony();  // for 1st run
   else
       honey = pBee->privateHoney();      //  for other run

   double x1,x2;
   x1=(*honey)[0];
   x2=(*honey)[1];

   double result;
   //result = x1*100+x2*2;
   result=0.5 + (sin(x1*x1-x2*x2)*sin(x1*x1-x2*x2) - 0.5) \
                /((1.0+0.001*(x1*x1+x2*x2))*(1.0+0.001*(x1*x1+x2*x2)));
   honey->setOrigValue(result);
}
 double CABCEvaluator::calc(double x1,double x2)
 {
     return 0.5 + (sin(x1*x1-x2*x2)*sin(x1*x1-x2*x2) - 0.5)/((1+0.001*(x1*x1+x2*x2))*(1+0.001*(x1*x1+x2*x2)));
     //return x1*100+x2*2;
 }

}
