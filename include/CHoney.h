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
#ifndef CHONEY_H
#define CHONEY_H
#include<vector>
#include "CABCParameter.h"
#include "ABC_define.h"

namespace ABCZJUT{

class CHoney
{
    public:
        CHoney();
        CHoney(CABCParameter*);
        CHoney(const CHoney&);
        virtual ~CHoney();

        CHoney* clone();
        double& operator[](size_t);
        double  operator[](std::string);
        CHoney& operator=(const CHoney&);

        double origValue()const;
        double rawScore()const;
        double fitness()const;
        double rfitness()const;
        size_t trail()const;
        const std::vector<double>& code()const;

        void init();

        void setOrigValue(double);
        void setRawScore(double);
        void setFitness(double);

        void setRfitness(double);

        void setTrail(size_t);
        void addTrail();
        bool JudgeUpdateHoney();

    public:
        CABCParameter* m_Parameter;

    private:
        std::vector<double> m_code;

    protected:

        double  m_rfitness;       // relative fitness ratio

        double  m_origValue;      // it is obtained from energy of DFT
		                                         // Importantly, only this value can be compared with those from parents, grandparents
        double  m_rawscore;       // it is obtained from conversion of m_origValue by using some formula.  Usually
		                                         // this conversion formula differed among the generations.
        double  m_fitness;        // m_fitness= the value after scalling treatment of m_rawscore
		                                         // statistic treatment of fitness, and it is used for selector, crosser, mutator
        size_t  m_trail;         //calculation number, which is used to compare with limit



};

}
#endif // CBEE_H
