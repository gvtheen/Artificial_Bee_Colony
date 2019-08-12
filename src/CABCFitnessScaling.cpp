#include <cmath>
#include "CABCFitnessScaling.h"
#include "CBeecolony.h"
#include "CHoney.h"

namespace ABCZJUT{

CABCFitnessScaling::CABCFitnessScaling(CBeecolony* bmp)
:m_pBeecolony(bmp)
{
    //ctor
}

CABCFitnessScaling::~CABCFitnessScaling()
{
    //dtor
}

void CABCFitnessScaling::run()
{
   //this->noScaling(m_pBeecolony);
   //this->linearScaling(this->m_pBeecolony);
   //this->powerLawScaling(this->m_pBeecolony);
   this->sigmaTruncScaling(this->m_pBeecolony);
}
void CABCFitnessScaling::noScaling(CBeecolony* p_beecolony)
{
    size_t popnum = p_beecolony->Count();
    p_beecolony->raw_statistic();
    for(size_t i=0;i<popnum;i++)
        ((*p_beecolony)[i]).setFitness(((*p_beecolony)[i]).rawScore());

}
void CABCFitnessScaling::linearScaling(CBeecolony* p_beecolony)
{
    double raw_min, raw_max, raw_avg;
    p_beecolony->raw_statistic();

    raw_min = (*p_beecolony)["minRaw"];
    raw_max = (*p_beecolony)["maxRaw"];
    raw_avg = (*p_beecolony)["avgRaw"];
    int a=0,b=0,delta=0;
    int c = p_beecolony->m_ABCParameter->ScaleLinearMultiplier;
    if(raw_avg==raw_max)
    {
       a = 1.0;
       b = 0.0;
    }else if( raw_min > ( c*raw_avg - raw_max/c - 1.0)){
       delta=raw_max-raw_avg;
       a = (c - 1.0) * raw_avg / delta;
       b = raw_avg*(raw_max - c*raw_avg)/delta;
    }else{
       delta = raw_avg - raw_min;
       a = raw_avg / delta;
       b = -1*raw_min * raw_avg / delta;
    }
    double temp_raw;
    size_t popnum = p_beecolony->Count();

    for(size_t i=0;i<popnum;i++)
    {
       temp_raw = ((*p_beecolony)[i]).rawScore();
       temp_raw = temp_raw*a + b;
       if(temp_raw<0)
          temp_raw=0;
       ((*p_beecolony)[i]).setFitness(temp_raw);
    }
}
void CABCFitnessScaling::sigmaTruncScaling(CBeecolony* p_beecolony)
{
    p_beecolony->raw_statistic();

    double c = p_beecolony->m_ABCParameter->ScaleSigmaTruncMultiplier;
    double raw_avg = (*p_beecolony)["avgRaw"];
    double raw_dev = (*p_beecolony)["rawDev"];

    size_t popnum = p_beecolony->Count();
    //std::vector <CGenome*> *p_genome=currentPopulation->m_pGpopulation;
    double temp_raw;
    for(size_t i=0;i<popnum;i++)
    {
       temp_raw = ((*p_beecolony)[i]).rawScore() - raw_avg;
       temp_raw = temp_raw + raw_dev*c;
       ((*p_beecolony)[i]).setFitness(temp_raw);
    }
}
void CABCFitnessScaling::powerLawScaling(CBeecolony* p_beecolony)
{
    p_beecolony->raw_statistic();

    double k =  p_beecolony->m_ABCParameter->ScalePowerLawFactor;
    size_t popnum = p_beecolony->Count();

    //std::vector <CGenome*> *p_genome=currentPopulation->m_pGpopulation;
    double temp_raw;
    for(size_t i=0;i<popnum;i++)
    {
       temp_raw = ((*p_beecolony)[i]).rawScore();
       temp_raw = std::pow(temp_raw,k);
       ((*p_beecolony)[i]).setFitness(temp_raw);
    }
}


}


