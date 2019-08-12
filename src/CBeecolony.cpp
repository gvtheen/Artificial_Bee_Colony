#include<cmath>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include "CBeecolony.h"


namespace ABCZJUT{

CBeecolony::CBeecolony(CABCParameter* mbf)
:m_ABCParameter(mbf)
{
    this->init();
    this->m_pBestHoney=nullptr;
}

CBeecolony::~CBeecolony()
{
    for(size_t i=0;i<this->m_NectarSource.size();i++)
        delete this->m_NectarSource[i];
    this->m_NectarSource.clear();

    if(this->m_pBestHoney!=nullptr)
        delete this->m_pBestHoney;
}
////
void CBeecolony::init()
{
    size_t num=this->m_ABCParameter->PopulationNum();
    CHoney* newHoney=nullptr;

    for(size_t i=0;i<num;i++){
        newHoney=new CHoney(m_ABCParameter);
        newHoney->init();
        this->m_NectarSource.push_back(newHoney);
    }
}
////
CHoney* CBeecolony::Honey(const size_t index)
{
    assert(index<this->m_NectarSource.size());

    return m_NectarSource[index];
}
CHoney& CBeecolony::operator[](const size_t index)
{
    assert(index<this->m_NectarSource.size());

    return *(m_NectarSource[index]);
}
double  CBeecolony::operator[](std::string mystr)
{
     std::string indexName = boost::to_lower_copy<std::string>(mystr);

	 if (indexName=="minraw")
	     return this->m_MinRawScore;
	 else if(indexName=="minfit")
	     return this->m_MinFitness;
	 else if(indexName=="maxfit")
	     return this->m_MaxFitness;
	 else if(indexName=="maxraw")
	     return this->m_MaxRawScore;
	 else if(indexName=="avgraw")
	     return this->m_AvgRawScore;
	 else if(indexName=="avgfit")
	     return this->m_AvgFitness;
     else if(indexName=="rawdev")
         return this->m_DevrawScore;
     else if(indexName=="minori")
         return this->m_MinOriValue;
     else if(indexName=="maxori")
         return this->m_MaxOriValue;
	 else{
		 //util::Log::Error<<"IndexStr cannot match with them! CBeecolony_operator[]!\n";
         boost::throw_exception(std::runtime_error("IndexStr cannot match with them! CBeecolony_operator[]!"));
	 }
}
CABCParameter* CBeecolony::ABCParameter()
{
    return this->m_ABCParameter;
}

size_t CBeecolony::Count()
{
   return this->m_NectarSource.size();
}
void CBeecolony::convertOriToRaw()
{
/*   for(size_t i=0;i<this->m_NectarSource.size();i++)
 *       if(this->calc((*this)[i][0],(*this)[i][1]) != (*this)[i].origValue())
 *          std::cout<<" CBeecolony::convertOriToRaw():ERROR:"<<i<<" value:"<<(*this)[i].origValue()\
 *                     <<" "<<calc((*this)[i][0],(*this)[i][1])<<std::endl;
 */
   this->ori_statistic();

   for(size_t i=0;i<this->m_NectarSource.size();i++)
     m_NectarSource[i]->setRawScore( 100.00- m_NectarSource[i]->origValue() );

}
void CBeecolony::ori_statistic()
{
   std::vector<CHoney*>::iterator it;

   it= std::max_element(m_NectarSource.begin(),m_NectarSource.end(),\
                        [](CHoney* A, CHoney* B){return (*A)["origvalue"] < (*B)["origvalue"];});
   this->m_pMaxOriCHoney = *it;
     this->m_MaxOriValue = (*it)->origValue();

   it = std::min_element(m_NectarSource.begin(),m_NectarSource.end(),\
                        [](CHoney* A, CHoney* B){return (*A)["origvalue"] < (*B)["origvalue"];});
   this->m_pMinOriCHoney = *it;
   this->m_MinOriValue = (*it)->origValue();

/*    std::cout<<"**********it:  "<<(*it)->origValue()<<std::endl;
 *    std::cout<<"        calc:  "<< this->calc((*(*it))[0],(*(*it))[1])<<std::endl;
 *    std::cout<<"size:"<<(*it)->code().size()<<"  it x1= "<<(*(*it))[0] << ";   x2=  "<<(*(*it))[1]<<std::endl;
 */

}
void CBeecolony::raw_statistic()
{
   assert(this->Count()>0);

   std::vector<CHoney*>::iterator it;

   double sumRawScore=0.0,ss=0.0;
   for(it=m_NectarSource.begin();it!=m_NectarSource.end();it++)
      sumRawScore += (*it)->rawScore();

   this->m_AvgRawScore=sumRawScore/m_NectarSource.size();

   for(it=m_NectarSource.begin();it!=m_NectarSource.end();it++)
      ss += ((*it)->rawScore()-this->m_AvgRawScore)*((*it)->rawScore()-this->m_AvgRawScore);

   this->m_DevrawScore=sqrt(ss);

   it= std::max_element(m_NectarSource.begin(),m_NectarSource.end(),\
                        [](CHoney* A, CHoney* B){return (*A)["rawScore"] < (*B)["rawScore"];});
   this->m_pMaxRawCHoney = *it;
     this->m_MaxRawScore =(*it)->rawScore();

   it = std::min_element(m_NectarSource.begin(),m_NectarSource.end(),\
                        [](CHoney* A, CHoney* B){return (*A)["rawScore"] < (*B)["rawScore"];});
   this->m_pMinRawCHoney = *it;
     this->m_MinRawScore = (*it)->rawScore();

}

void CBeecolony::fitness_statistic()
{
   assert(this->Count()>0);

   std::vector<CHoney*>::iterator it;

   double sumFitScore=0.0;
   for(it=m_NectarSource.begin();it!=m_NectarSource.end();it++)
      sumFitScore += (*it)->fitness();
   this->m_AvgFitness=sumFitScore/this->Count();

   for(it=m_NectarSource.begin();it!=m_NectarSource.end();it++)
      (*it)->setRfitness((*it)->fitness()/sumFitScore);

   it = std::min_element(m_NectarSource.begin(),m_NectarSource.end(),\
                         [](CHoney* A,CHoney* B){ return (*A)["fitness"] < (*B)["fitness"];});
   this->m_pMinFitCHoney = *it;
   this->m_MinFitness = this->m_pMinFitCHoney->fitness();

   it = std::max_element(m_NectarSource.begin(),m_NectarSource.end(),\
                         [](CHoney* A,CHoney* B){ return (*A)["fitness"] < (*B)["fitness"];});
   this->m_pMaxFitCHoney=m_NectarSource[0];
   for(size_t i=0;i<m_NectarSource.size();i++)
       if( (*(m_NectarSource[i]))["fitness"] > (*m_pMaxFitCHoney)["fitness"] )
          m_pMaxFitCHoney = m_NectarSource[i];
   //this->m_pMaxFitCHoney =*it;
   this->m_MaxFitness = m_pMaxFitCHoney->fitness();


//   std::cout<<"m_pMaxFitCHoney x1= "<<(*m_pMaxFitCHoney)[0] << ";   x2=  "<<(*m_pMaxFitCHoney)[1]<<std::endl;
//   std::cout<<"m_pMaxFitCHoney orivalue=  "<<m_pMaxFitCHoney->origValue()<<std::endl;
//   std::cout<<"m_pMaxFitCHoney     calc=  "<<this->calc((*m_pMaxFitCHoney)[0],(*m_pMaxFitCHoney)[1])<<std::endl;

   if(this->m_pBestHoney==nullptr){
     this->m_pBestHoney=m_pMaxFitCHoney->clone();
     std::cout<<"1st set best honey "<<std::endl;
   }
   if( m_pBestHoney->origValue() > m_pMaxFitCHoney->origValue() ){
      std::cout<<"update best honey "<<std::endl;
      *m_pBestHoney=*m_pMaxFitCHoney;
   }
/*     std::cout<<"address of m_pBestHoney   "<<m_pBestHoney<<std::endl;
 *     std::cout<<"address of m_pMaxFitCHoney: "<<m_pMaxFitCHoney<<std::endl;
 *     std::cout<<"address of it:               "<<*it<<std::endl;
 *     std::cout<<"size:"<<m_pBestHoney->code().size()<<"; x1= "<<(*m_pBestHoney)[0] << ";   x2=  "<<(*m_pBestHoney)[1]<<std::endl;
 *     std::cout<<"*********this->m_pBestHoney: "<<m_pBestHoney->origValue()<<std::endl;
 *     std::cout<<"*********m_pBestHoney calc:  "<<this->calc((*m_pBestHoney)[0],(*m_pBestHoney)[1])<<std::endl<<std::endl;
 *    std::cout<<"*********CBeecolony::fitness_statistic()-3"<<std::endl;
 */
}

void CBeecolony::sort_fitness()    // be used in the first run.
{
   std::sort(m_NectarSource.begin(),m_NectarSource.end(),\
      [](CHoney* A,CHoney* B){ return A->fitness() > B->fitness();});

 //  for(size_t i=0;i<this->m_NectarSource.size();i++)
  //    if(this->calc((*this)[i][0],(*this)[i][1]) != m_NectarSource[i]->origValue())
  //       std::cout<<"*********ERROR ERROR"<<std::endl;
}
void CBeecolony::standardOutput()
{
    assert(this->m_pBestHoney!=nullptr);

    std::cout<<"Best fitness: "<<m_pBestHoney->fitness()<<std::endl;
    std::cout<<"Best Original Value: "<<m_pBestHoney->origValue()<<std::endl;

    const std::vector<double>& codeV = m_pBestHoney->code();

    std::cout<<"*********Output best variable"<<std::endl;
    for(size_t i=0;i<codeV.size();i++)
        std::cout<<codeV[i]<<std::endl;
    std::cout<<"*********End output best variable"<<std::endl;

}
double CBeecolony::calc(double x1,double x2)
 {
      //return x1*100+x2*2;
      return 0.5 + (sin(x1*x1-x2*x2)*sin(x1*x1-x2*x2) - 0.5) \
                /((1.0+0.001*(x1*x1+x2*x2))*(1.0+0.001*(x1*x1+x2*x2)));
 }



}
