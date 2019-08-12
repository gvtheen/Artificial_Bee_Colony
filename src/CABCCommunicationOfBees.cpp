#include <iostream>
#include "CABCCommunicationOfBees.h"
#include "Bitset.h"
#include "CABCParameter.h"
#include "CRandomgenerator.h"
#include "CBeebase.h"
#include "CABCEvaluator.h"
#include "CABCEngine.h"
#include "CBeecolony.h"
#include "CHoney.h"

using util::CRandomgenerator;
using util::Bitset;

namespace ABCZJUT{

CABCCommunicationOfBees::CABCCommunicationOfBees(CABCEngine* pmb)
:m_pABCEngine(pmb)
{
    //ctor
}

CABCCommunicationOfBees::~CABCCommunicationOfBees()
{
    //dtor
}

void CABCCommunicationOfBees::run()
{
    this->EmployedBeeProcess();
   // std::cout << "CABCCommunicationOfBees::run()-1!" << std::endl;
    this->LookerBeeProcess();
  //  std::cout << "CABCCommunicationOfBees::run()-2!" << std::endl;
    this->ScoutBeeProcess();
  //  std::cout << "CABCCommunicationOfBees::run()-3!" << std::endl;
   // for(size_t i=0;i<m_pABCEngine->m_Bees.size();i++)
   //     m_pABCEngine->m_Bees[i]->GreedySelection();

}
void CABCCommunicationOfBees::EmployedBeeProcess()
{
    for(size_t i=0;i<m_pABCEngine->m_Bees.size();i++)
        if(m_pABCEngine->m_Bees[i]->position()==CBeebase::Employed)
        {
            if(m_pABCEngine->m_Bees[i]->HoneyOfBeecolony()->JudgeUpdateHoney()==false){
               m_pABCEngine->m_Bees[i]->SendBees();
               m_pABCEngine->m_pEvaluator->evaluate(m_pABCEngine->m_Bees[i]);
               m_pABCEngine->m_Bees[i]->GreedySelection();
            }else{
               m_pABCEngine->m_pEvaluator->evaluate(m_pABCEngine->m_Bees[i],true);
            }
        }

}
void CABCCommunicationOfBees::LookerBeeProcess()
{
   //Bitset pos_emp(m_pABCEngine->m_pABCParameter->EmployedBeesNum());

   size_t Emp_Bee_index=0;

   //CRandomgenerator* rndNumber=new CRandomgenerator();
   //double rnd,prob;
   for(size_t i=0;i<m_pABCEngine->m_Bees.size();i++)
        if(m_pABCEngine->m_Bees[i]->position()==CBeebase::Looker)
        {
           if(m_pABCEngine->m_Bees[i]->HoneyOfBeecolony()->JudgeUpdateHoney()==false){
              m_pABCEngine->m_Bees[i]->setIndexOfLooker(Emp_Bee_index);
              m_pABCEngine->m_Bees[i]->SendBees();

              m_pABCEngine->m_pEvaluator->evaluate(m_pABCEngine->m_Bees[i]);
              m_pABCEngine->m_Bees[i]->GreedySelection();
           }else
              m_pABCEngine->m_pEvaluator->evaluate(m_pABCEngine->m_Bees[i],true);

            Emp_Bee_index++;
            if(Emp_Bee_index==m_pABCEngine->m_pABCParameter->EmployedBeesNum())
                            Emp_Bee_index=0;
        }
   //delete rndNumber;
}
void CABCCommunicationOfBees::ScoutBeeProcess()
{
   for(size_t i=0;i<m_pABCEngine->m_Bees.size();i++)
        if(m_pABCEngine->m_Bees[i]->position()==CBeebase::Scout)
        {
            if(m_pABCEngine->m_Bees[i]->HoneyOfBeecolony()->JudgeUpdateHoney()==false){
               m_pABCEngine->m_Bees[i]->SendBees();
               m_pABCEngine->m_pEvaluator->evaluate(m_pABCEngine->m_Bees[i]);
               m_pABCEngine->m_Bees[i]->GreedySelection();
            }else
               m_pABCEngine->m_pEvaluator->evaluate(m_pABCEngine->m_Bees[i],true);
        }
}




}
