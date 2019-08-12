#include<time.h>
#include <cmath>
#include <iostream>
#include "assert.h"
#include "CBeebase.h"
#include "CBeecolony.h"
#include "CHoney.h"
#include "CABCParameter.h"
#include "CRandomgenerator.h"
using util::CRandomgenerator;
namespace ABCZJUT{

CBeebase::CBeebase(CBeecolony* colony,size_t index,BEE_POSITION pos)
{
    this->m_Beecolony=colony;
    this->m_index=index;
    this->m_index_empBee=index;
    this->m_position=pos;
    this->m_honey = new CHoney(m_Beecolony->ABCParameter());
}

CBeebase::~CBeebase()
{
    if(this->m_honey!=nullptr)
        delete m_honey;
    //Nothing is needed.
}
CBeebase::BEE_POSITION CBeebase::position()
{
    return this->m_position;
}
void CBeebase::setPosition(BEE_POSITION tmp)
{
    this->m_position=tmp;
}
size_t CBeebase::index()
{
    return this->m_index;
}
void CBeebase::setIndex(size_t tmp)
{
    this->m_index=tmp;
}
void CBeebase::setIndexOfLooker(size_t tmp)
{
    this->m_index_empBee=tmp;
}
CHoney* CBeebase::privateHoney()
{
    assert(this->m_honey!=nullptr);

    return this->m_honey;
}
CHoney* CBeebase::HoneyOfBeecolony()
{
    assert (this->m_index < m_Beecolony->Count());

    return m_Beecolony->Honey(this->m_index);
}
void CBeebase::SendBees()
{
    switch ((int)this->m_position){
       case CBeebase::Employed:
           this->SendEmployedBees();
           break;
       case CBeebase::Looker:
           this->SendLookerBees();
           break;
       case CBeebase::Scout:
           this->SendScoutBees();
           break;
       default:
           break;
    }
}
void CBeebase::SendEmployedBees()
{
    assert(this->m_honey!=nullptr);

    CRandomgenerator* random_generator=new CRandomgenerator();
    size_t param2change;
    double Rij;
    size_t neighbor;
    double set_value;

    *m_honey=(*m_Beecolony)[this->m_index];

    param2change=random_generator->uniformRandomRandge(0,this->m_Beecolony->m_ABCParameter->varibleNum()-1);

    Rij=random_generator->uniformRandom01(this->index());

    while(1){
       neighbor=random_generator->uniformRandomRandge(0,this->m_Beecolony->m_ABCParameter->EmployedBeesNum()-1);
       if(neighbor!=this->m_index)
          break;
    }

    set_value=(*m_Beecolony)[this->m_index][param2change] + m_Beecolony->m_ABCParameter->elpha*  \
              (Rij-0.5)*( (*m_Beecolony)[this->m_index][param2change]-(*m_Beecolony)[neighbor][param2change] );


    if(Rij < this->m_Beecolony->m_ABCParameter->cr ){
        double m_best = (*(m_Beecolony->m_pBestHoney))[param2change];
        set_value = m_best + (Rij-0.5)*(m_Beecolony->m_ABCParameter->bestLoc)* \
                    ( m_best - (*m_Beecolony)[this->m_index][param2change] );
    }

    if(set_value < this->m_Beecolony->m_ABCParameter->lowerValueAt(param2change))
      (*m_honey)[param2change] = this->m_Beecolony->m_ABCParameter->lowerValueAt(param2change);
    else if(set_value > this->m_Beecolony->m_ABCParameter->upperValueAt(param2change))
      (*m_honey)[param2change] = this->m_Beecolony->m_ABCParameter->upperValueAt(param2change);
    else
      (*m_honey)[param2change] = set_value;

}
void CBeebase::SendLookerBees()
{
    assert(this->m_honey!=nullptr);

    CRandomgenerator* random_generator=new CRandomgenerator();
    size_t param2change;
    double Rij;
    size_t neighbor;
    double set_value;

    *m_honey= (*m_Beecolony)[this->m_index];

    param2change=random_generator->uniformRandomRandge(0,this->m_Beecolony->m_ABCParameter->varibleNum()-1);

    Rij=random_generator->uniformRandom01(this->index());

    while(1){
       neighbor=random_generator->uniformRandomRandge(0,this->m_Beecolony->m_ABCParameter->LookerBeesNum()-1);
       // attention!!!!!
       neighbor += this->m_Beecolony->m_ABCParameter->EmployedBeesNum();
       if(neighbor!=this->m_index)
          break;
    }
    set_value=(*m_Beecolony)[m_index_empBee][param2change]+ m_Beecolony->m_ABCParameter->elpha*
              (Rij-0.5)*( (*m_Beecolony)[m_index_empBee][param2change]-(*m_Beecolony)[neighbor][param2change] );

     if(Rij < this->m_Beecolony->m_ABCParameter->cr ){
        double m_best = (*(m_Beecolony->m_pBestHoney))[param2change];

        set_value = m_best + (Rij-0.5)*(m_Beecolony->m_ABCParameter->bestLoc)* \
                    (m_best - (*m_Beecolony)[m_index_empBee][param2change] );
    }

    if(set_value < this->m_Beecolony->m_ABCParameter->lowerValueAt(param2change))
      (*m_honey)[param2change] = this->m_Beecolony->m_ABCParameter->lowerValueAt(param2change);
    else if(set_value > this->m_Beecolony->m_ABCParameter->upperValueAt(param2change))
      (*m_honey)[param2change] = this->m_Beecolony->m_ABCParameter->upperValueAt(param2change);
    else
      (*m_honey)[param2change] = set_value;
}
void CBeebase::SendScoutBees()
{
    assert(this->m_honey!=nullptr);

    this->m_honey->init();
}
void CBeebase::GreedySelection()
{

//    if( std::fabs((*m_honey).origValue() - calc((*m_honey)[0],(*m_honey)[1])) > 1.0e-10)
//           std::cout<<" CBeebase::GreedySelection():ERROR-22222:"<<this->m_index<<" value:"<<(*m_honey).origValue()\
//                    <<" "<<calc((*m_honey)[0],(*m_honey)[1])<<std::endl;

    if(this->m_honey->origValue() < (*m_Beecolony)[this->m_index].origValue()){
       (*m_Beecolony)[this->m_index]=(*m_honey);

//       if((*m_Beecolony)[this->m_index].origValue() != m_honey->origValue())
//           std::cout<<" ERROR,ERROR,ERROR!!!!\n";

       (*m_Beecolony)[this->m_index].setTrail(0);
    }else
       (*m_Beecolony)[this->m_index].addTrail();
}
double CBeebase::calc(double x1,double x2)
 {
      return 0.5 + (sin(x1*x1-x2*x2)*sin(x1*x1-x2*x2) - 0.5) \
                /((1+0.001*(x1*x1+x2*x2))*(1+0.001*(x1*x1+x2*x2)));
      //return x1*100+x2*2;
 }


}
