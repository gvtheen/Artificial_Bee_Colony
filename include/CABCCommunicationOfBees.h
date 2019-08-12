#ifndef CABCUPDATEBEE_H
#define CABCUPDATEBEE_H

namespace ABCZJUT{
class CABCEngine;

class CABCCommunicationOfBees
{
    public:
        CABCCommunicationOfBees(CABCEngine*);
        virtual ~CABCCommunicationOfBees();

        void run();

    private:
        void EmployedBeeProcess();
        void LookerBeeProcess();
        void ScoutBeeProcess();

    private:
        CABCEngine   *m_pABCEngine;
};


}
#endif // CABCUPDATEBEE_H
