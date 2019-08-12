#ifndef CABCEVALUATOR_H
#define CABCEVALUATOR_H

namespace ABCZJUT{

class CBeebase;

class CABCEvaluator
{
    public:
        CABCEvaluator();
        virtual ~CABCEvaluator();

       // void run();
        void evaluate(CBeebase*,bool is_1st_run=false);

        double calc(double,double);

    protected:

    private:
       // CBeecolony* m_pBeecolony;
};

}
#endif // CABCEVALUATOR_H
