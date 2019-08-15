
#include "CABCEvaluator.h"
#include "CBeebase.h"
#include "CHoney.h"

namespace ABCZJUT{

CABCEvaluator::CABCEvaluator(EVALUATOR_FUN _fun)
:m_evalFun(_fun)
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

   honey->setOrigValue((*m_evalFun)(honey->code()));
}

}
