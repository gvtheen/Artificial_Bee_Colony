/******************************************************************************
**
** Copyright (C) 2019-2031 Dr.Gui-lin Zhuang <glzhuang@zjut.edu.cn>
** All rights reserved.
**
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/
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
