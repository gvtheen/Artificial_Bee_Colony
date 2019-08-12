#include <iostream>

#include "CABCEngine.h"
#include "CBeecolony.h"
#include "CBeebase.h"
#include "CABCParameter.h"
#include "CABCFitnessScaling.h"
#include "CABCEvaluator.h"
#include "CABCCommunicationOfBees.h"


namespace ABCZJUT{

CABCEngine::CABCEngine(CABCParameter* mbf)
:m_pABCParameter(mbf)
{
    m_pBeeColony=nullptr;
}

CABCEngine::~CABCEngine()
{
    delete this->m_pEvaluator;
    delete this->m_pCommunicationOfBees;
    delete this->m_pFitnessScaling;
   // std::cout << "CABCEngine::~CABCEngine()-1!" << std::endl;

    for(size_t i=0;i<m_Bees.size();i++)
        delete m_Bees[i];
    this->m_Bees.clear();
   // std::cout << "CABCEngine::~CABCEngine()-2!" << std::endl;
    delete this->m_pBeeColony;

}

void CABCEngine::init()
{
   this->m_pBeeColony=new CBeecolony(this->m_pABCParameter);
   //std::cout << "CABCEngine::init-1!" << std::endl;

   for(size_t i=0;i<this->m_pABCParameter->PopulationNum();i++)
       this->m_Bees.push_back(new CBeebase(this->m_pBeeColony,i,CBeebase::Scout));

  // std::cout << "CABCEngine::init-2!" << std::endl;

   this->m_pEvaluator=new CABCEvaluator();
   this->m_pFitnessScaling=new CABCFitnessScaling(this->m_pBeeColony);

  // std::cout << "CABCEngine::init-3!" << std::endl;

   this->m_pCommunicationOfBees= new CABCCommunicationOfBees(this);

}
void CABCEngine::evolve()
{
   std::cout <<"Current Cycles: "<<this->m_pABCParameter->currentGenerationNum()<<std::endl;
   for(size_t i=0;i<m_Bees.size();i++)
     this->m_pEvaluator->evaluate(m_Bees[i],true);
  // std::cout << "CABCEngine::evolve()-1!" << std::endl;
   this->m_pBeeColony->convertOriToRaw();

   this->m_pFitnessScaling->run();
   // std::cout << "CABCEngine::evolve()-2!" << std::endl;
   this->m_pBeeColony->fitness_statistic();
  // std::cout << "CABCEngine::evolve()-21!" << std::endl;
   this->IdentifyBeeRole();     // // Attention: only it is used in the 1st run
  // std::cout << "CABCEngine::evolve()-3!" << std::endl;
   this->m_pABCParameter->add_Curr_Generation();

   while(1){
       std::cout <<"Current Cycles: "<<this->m_pABCParameter->currentGenerationNum()<<std::endl;

       this->m_pCommunicationOfBees->run();          // Communicate with other bees, and perform fitness calculations.

       this->m_pBeeColony->convertOriToRaw();

       this->m_pFitnessScaling->run();

       this->m_pBeeColony->fitness_statistic();

       this->m_pABCParameter->add_Curr_Generation();

       if(this->m_pABCParameter->IsStop())
          break;
   }
   this->m_pBeeColony->standardOutput();
}
void CABCEngine::IdentifyBeeRole()
{

    this->m_pBeeColony->sort_fitness();   //sort ascend

    size_t emp_num=this->m_pABCParameter->EmployedBeesNum();
    size_t Lok_num=this->m_pABCParameter->LookerBeesNum();

    //size_t Sco_num=this->m_pABCParameter->LookerBeesNum();
    for(size_t i=0;i<emp_num;i++)
        this->m_Bees[i]->setPosition(CBeebase::Employed);

    for(size_t i=emp_num;i<emp_num+Lok_num;i++)
        this->m_Bees[i]->setPosition(CBeebase::Looker);

    for(size_t i=emp_num+Lok_num;i<m_pABCParameter->PopulationNum();i++)
        this->m_Bees[i]->setPosition(CBeebase::Scout);
}


}
