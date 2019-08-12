#ifndef CBEEBASE_H
#define CBEEBASE_H
#include<iostream>
namespace ABCZJUT{

class CHoney;
class CBeecolony;


class CBeebase
{
    public:
        typedef enum enum_position{
            Employed=0x51110,
              Looker=0x51220,
               Scout=0x51330,
                None=0x51440
        }BEE_POSITION;

        CBeebase(CBeecolony*,size_t index,BEE_POSITION pos=Scout);
        virtual ~CBeebase();

        BEE_POSITION position();
        size_t index();

        void setPosition(BEE_POSITION);
        void setIndex(size_t);
        CHoney* HoneyOfBeecolony();
        void setIndexOfLooker(size_t);
        CHoney* privateHoney();


        void SendBees();
        //
        void SendLookerBees();
        void SendEmployedBees();
        void SendScoutBees();

        void GreedySelection(); //  post-treatment after sending.


        double calc(double x1,double x2);

    private:
        CBeecolony* m_Beecolony;
        CHoney *m_honey;
        size_t m_index;     // index of Beecolony;

        size_t m_index_empBee; // index of looker in employed bees.
        BEE_POSITION m_position;

};


}
#endif // CBEEBASE_H
