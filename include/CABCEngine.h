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
#ifndef CABCENGINE_H
#define CABCENGINE_H
#include "ABC_define.h"
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
        CABCEngine(CABCParameter*,EVALUATOR_FUN);
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

                   EVALUATOR_FUN   m_evalFun;


};

}
#endif // CABCENGINE_H
