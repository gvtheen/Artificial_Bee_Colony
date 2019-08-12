#ifndef CRANDOMGENERATOR_H
#define CRANDOMGENERATOR_H
#define MNNN 10

namespace util{

class CRandomgenerator
{
    public:
        static unsigned int classcalled;
        CRandomgenerator();
        double uniformRandom01(int seedNum);
        int uniformRandomRandge(int start, int stop,int seedNum=1);
//        int    uniformRandomInt(int,int);
//        double uniformRandomReal(double,double);
        virtual ~CRandomgenerator();
    protected:
        unsigned int m_seedInt;
    private:
        //int m_seedNumber;
};

}
#endif // CRANDOMGENERATOR_H