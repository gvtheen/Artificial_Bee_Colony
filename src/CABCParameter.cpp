#include <assert.h>
#include <iostream>

#include "CABCParameter.h"


namespace ABCZJUT{

CABCParameter::CABCParameter()
{
    this->m_VarRangeofPopulation.clear();
    this->defaultInit();
}

CABCParameter::~CABCParameter()
{
    if(m_mapCmdString!=nullptr)
        delete m_mapCmdString;
}
void CABCParameter::defaultInit()
{
    m_mapCmdString = new (std::map <std::string, std::string>);

    m_mapCmdString->insert(std::pair<std::string,std::string>("[ABC_Population_Size]", "25"));
    m_mapCmdString->insert(std::pair<std::string,std::string>("[ABC_Limit_Size]", "5"));
    m_mapCmdString->insert(std::pair<std::string,std::string>("[ABC_Food_Size]",  "10"));
    m_mapCmdString->insert(std::pair<std::string,std::string>("[ABC_ScoutBees_Size]", "5"));

    this->m_CurrGeneration=0;
    this->m_PopNum=30;
    this->m_FoodNum=11;
    this->m_ScoutBeesNum=8;
    this->m_generationNum=50;
    this->m_LookerBeesNum=11;
    this->m_LimitNum=5;

    this->m_VarRangeofPopulation.push_back(VarRangeStruct(-10,10,0.01));
    this->m_VarRangeofPopulation.push_back(VarRangeStruct(-10,10,0.01));

  //  std::cout<<"CABCParameter::defaultInit():"<<this->varibleNum()<<std::endl;
}
std::vector <VarRangeStruct>& CABCParameter::VarRange()
{
    return this->m_VarRangeofPopulation;
}

size_t CABCParameter::varibleNum()
{
    assert(m_VarRangeofPopulation.size()>0);

    return this->m_VarRangeofPopulation.size();

}
void CABCParameter::setVarRange(std::vector<VarRangeStruct>& tmp)
{
    assert(tmp.size()>0);

    if( m_VarRangeofPopulation.size()>0 )
        m_VarRangeofPopulation.clear();

    m_VarRangeofPopulation.assign(tmp.begin(),tmp.end());

}
void CABCParameter::add_Curr_Generation()
{
    this->m_CurrGeneration = this->m_CurrGeneration+1;
}
size_t CABCParameter::PopulationNum()
{
    return this->m_PopNum;
}
size_t CABCParameter::limitNum()
{
    return this->m_LimitNum;
}
size_t CABCParameter::foodNum()
{
    return this->m_FoodNum;
}
size_t CABCParameter::EmployedBeesNum()
{
    return this->m_FoodNum;
}
size_t CABCParameter::LookerBeesNum()
{
    return this->m_LookerBeesNum;
}
size_t CABCParameter::ScoutBeesNum()
{
    return this->m_ScoutBeesNum;
}
size_t CABCParameter::currentGenerationNum()
{
    return this->m_CurrGeneration;
}
double CABCParameter::upperValueAt(size_t index)
{
    assert(index<m_VarRangeofPopulation.size());

    return this->m_VarRangeofPopulation[index].max;
}
double CABCParameter::lowerValueAt(size_t index)
{
    assert(index<m_VarRangeofPopulation.size());

    return this->m_VarRangeofPopulation[index].min;
}
bool   CABCParameter::IsStop()
{
    return m_generationNum <= m_CurrGeneration? true:false;
}



}
