#ifndef CABCFITNESSSCALING_H
#define CABCFITNESSSCALING_H


namespace ABCZJUT{

class CBeecolony;

class CABCFitnessScaling
{
    public:
        CABCFitnessScaling(CBeecolony*);
        virtual ~CABCFitnessScaling();

        void run();

    protected:
        void linearScaling(CBeecolony*);
		void sigmaTruncScaling(CBeecolony*);
		void powerLawScaling(CBeecolony*);
		void noScaling(CBeecolony*);

    private:
        CBeecolony* m_pBeecolony;
};



}
#endif // CABCFITNESSSCALING_H
