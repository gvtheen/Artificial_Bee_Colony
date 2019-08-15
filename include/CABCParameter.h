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
#ifndef CABCPARAMETER_H
#define CABCPARAMETER_H
#include <map>
#include <string>
#include <vector>
#include "ABC_define.h"
namespace ABCZJUT{

class CABCParameter
{
    public:
        CABCParameter();
        virtual ~CABCParameter();

        void defaultInit();

        std::vector<VarRangeStruct>& VarRange();
        void setVarRange(std::vector<VarRangeStruct>&);

        void   add_Curr_Generation();

        size_t PopulationNum();
        size_t limitNum();
        size_t foodNum();
        size_t EmployedBeesNum();
        size_t LookerBeesNum();
        size_t ScoutBeesNum();
        size_t currentGenerationNum();
        size_t varibleNum();

          bool IsStop();

        double upperValueAt(size_t index);
        double lowerValueAt(size_t index);

        const double ScaleLinearMultiplier     = 1.2;
        const double ScaleSigmaTruncMultiplier = 2.0;
        const double ScalePowerLawFactor       = 1.0005;
        const double ScaleBoltzMinTemp         = 1.0;
        const double ScaleBoltzFactor          = 0.05;
        const double ScaleBoltzStart           = 40.0;

        const double cr = 0.6;
        const double elpha = 2.0;
        const double bestLoc=3.0;


    protected:
        std::map<std::string, std::string>  *m_mapCmdString;
    private:
        std::vector<VarRangeStruct>     m_VarRangeofPopulation;

        size_t m_PopNum;        // Population num = EmployedBeesnum + ScoutBeesNum + LookerBeesNum
        size_t m_LimitNum;
        size_t m_FoodNum;       // EmployedBeesnum = m_FoodNum
        size_t m_ScoutBeesNum;  //coutBees number
        size_t m_LookerBeesNum;

        // m_PopNum = m_FoodNum(EmployedBeesnumber)+m_ScoutBees+LookerBees;
        size_t m_CurrGeneration;
        size_t m_generationNum;
};

}
#endif // CABCPARAMETER_H
