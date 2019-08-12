#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED
struct VarRangeStruct{
	double min;
	double max;
	double accuracy;
    VarRangeStruct(double a,double b,double c){
       min=a;
       max=b;
       accuracy=c;
    }
};


#endif // DEFINE_H_INCLUDED
