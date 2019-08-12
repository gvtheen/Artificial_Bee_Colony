#include <stdexcept>
#include <iostream>
#include <boost/throw_exception.hpp>
#include "CHoney.h"
#include "assert.h"
#include "CRandomgenerator.h"
using util::CRandomgenerator;

namespace ABCZJUT{

CHoney::CHoney()
:m_Parameter(nullptr)
{
    this->m_trail=0; //ctor
    this->m_origValue=0.0;
    this->m_fitness=0.0;
    this->m_rawscore=0.0;
    this->m_rfitness=0.0;
}
CHoney::CHoney(CABCParameter* mth)
:m_Parameter(mth)
{
    this->m_trail=0;
    this->m_origValue=0.0;
    this->m_fitness=0.0;
    this->m_rawscore=0.0;
    this->m_rfitness=0.0;
}
CHoney::CHoney(const CHoney& td)
{
    this->m_fitness   = td.fitness();
    this->m_rfitness  = td.rfitness();
    this->m_origValue = td.origValue();
    this->m_rawscore  = td.rawScore();
        this->m_trail = td.trail();
    this->m_Parameter = td.m_Parameter;

    const std::vector<double>& tmp = td.code();
    m_code.clear();
    for(size_t i=0;i<tmp.size();i++)
           m_code.push_back(tmp[i]);
}
CHoney::~CHoney()
{
    this->m_code.clear();
}
//return critical value of honey.
CHoney* CHoney::clone()
{
    return new CHoney(*this);
}
double CHoney::origValue()const
{
    return this->m_origValue;
}
double CHoney::rawScore()const
{
    return this->m_rawscore;
}
double CHoney::fitness()const
{
    return this->m_fitness;
}
double CHoney::rfitness()const
{
    return this->m_rfitness;
}
const std::vector<double>& CHoney::code()const
{
    return this->m_code;
}
//set value
void CHoney::setOrigValue(double tmp)
{
    this->m_origValue=tmp;
}
void CHoney::setRawScore(double tmp)
{
    this->m_rawscore=tmp;
}
void CHoney::setFitness(double tmp)
{
    this->m_fitness=tmp;
}
void CHoney::setRfitness(double tmp)
{
    this->m_rfitness=tmp;
}
//add trail number
void CHoney::addTrail()
{
    this->m_trail=this->m_trail+1;
}
bool CHoney::JudgeUpdateHoney()
{
    if(this->m_trail==this->m_Parameter->limitNum()){
        this->init();
        return true;
    }else
        return false;
}
void CHoney::setTrail(size_t m)
{
    this->m_trail=m;
}
size_t CHoney::trail()const
{
    return this->m_trail;
}

double& CHoney::operator[](size_t index)
{
   //std::cout << "CHoney::operator[]-1!:" <<m_code.size()<<" "<<index<<std::endl;
    assert(index < m_code.size());

    return this->m_code[index];
}
double CHoney::operator[](std::string index_name)
{
    if(index_name=="rawScore")
	   return this->m_rawscore;
	else if(index_name=="fitness")
	   return this->m_fitness;
	else if(index_name=="origvalue")
	   return this->m_origValue;
	else{
	   //Log::Error<<" str of [] can not match! CHoney[]operator!\n";
	   boost::throw_exception(std::runtime_error("str of [] can not match! CHoney_[]operator!\n"));
	}
}
CHoney& CHoney::operator=(const CHoney& td)
{
    if(this != & td){
      this->m_fitness=td.fitness();
      this->m_rfitness=td.rfitness();
      this->m_origValue=td.origValue();
      this->m_rawscore=td.rawScore();
      this->m_trail=td.trail();
      const std::vector<double>& tmp=td.code();
      this->m_code.clear();
      for(size_t i=0;i<tmp.size();i++)
           this->m_code.push_back(tmp[i]);
    }
    return *this;
}
void CHoney::init()
{
    assert(this->m_Parameter!=nullptr);

    util::CRandomgenerator* Randomgenerator = new util::CRandomgenerator();
    double tmp;

    this->m_trail = 0;
    //std::vector<VarRangeStruct>& varRagSruct=this->m_Parameter->VarRange();
    if(this->m_code.size()>0)
       this->m_code.clear();
    //std::cout << "CHoney::init()-1!:" <<m_Parameter->varibleNum()<< std::endl;
    for(size_t i=0;i<m_Parameter->varibleNum();i++){
       // std::cout << "CHoney::init()-12! " <<(m_Parameter->upperValueAt(i)-m_Parameter->lowerValueAt(i))<< std::endl;
        tmp=(Randomgenerator->uniformRandom01(i))*(m_Parameter->upperValueAt(i)-m_Parameter->lowerValueAt(i))+m_Parameter->lowerValueAt(i);
       // std::cout << "CHoney::init()-13!" << std::endl;
        this->m_code.push_back(tmp);
    }
    //std::cout << "CHoney::init()-2 codesize: " <<m_code.size()<< std::endl;
    delete Randomgenerator;
}

}
