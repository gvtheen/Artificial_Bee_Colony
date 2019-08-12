#ifndef CABCENGINE_H
#define CABCENGINE_H
#include<vector>

namespace ABCZJUT{

class CBeebase;
class CBeecolony;
class CABCParameter;
class CABCFitnessScaling;
class CABCEvaluator;
class CABCCommunicationOfBees;

class CABCEngine
{
    public:
        CABCEngine(CABCParameter*);
        virtual ~CABCEngine();

        void init();
        void evolve();

        void IdentifyBeeRole();

    protected:

    private:
        friend class CABCCommunicationOfBees;

        std::vector<CBeebase*>     m_Bees;
        CBeecolony*                m_pBeeColony;


        CABCEvaluator*             m_pEvaluator;
        CABCParameter*             m_pABCParameter;
        CABCFitnessScaling*        m_pFitnessScaling;
        CABCCommunicationOfBees*   m_pCommunicationOfBees;


};

}
#endif // CABCENGINE_H
