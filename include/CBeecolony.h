#ifndef CNECTARSOURCE_H
#define CNECTARSOURCE_H
#include<vector>
#include "CHoney.h"
#include "CABCParameter.h"
#include "define.h"
namespace ABCZJUT{

class CBeecolony
{
    public:
        CBeecolony(CABCParameter*);
        virtual ~CBeecolony();

        CHoney* Honey(const size_t index);
        CHoney& operator[](const size_t);
        double  operator[](std::string);

        CABCParameter* ABCParameter();

        size_t Count();

        void init();
        void fitness_statistic();
        void raw_statistic();
        void ori_statistic();

        void sort_fitness();    // only be used in the initialization

        void convertOriToRaw();

        void standardOutput();
        double calc(double,double);
   public:
        CABCParameter   *m_ABCParameter;

    protected:

    private:
        friend class CBeebase;

        std::vector<CHoney*>    m_NectarSource;
        CHoney*                 m_pBestHoney;

             CHoney            *m_pMinRawCHoney;      // pointer of address of m_pGpopulation
		     CHoney            *m_pMaxRawCHoney;

             CHoney            *m_pMinFitCHoney;
		     CHoney            *m_pMaxFitCHoney;

		     CHoney            *m_pMaxOriCHoney;
		     CHoney            *m_pMinOriCHoney;

             double              m_MinRawScore;
		     double              m_MaxRawScore;
		     double              m_AvgRawScore;
		     double              m_DevrawScore;
		// analyse the fitness of current Population
		     double              m_MinFitness;
		     double              m_MaxFitness;
		     double              m_AvgFitness;

		     double              m_MinOriValue;
		     double              m_MaxOriValue;
};


}
#endif // CNECTARSOURCE_H
