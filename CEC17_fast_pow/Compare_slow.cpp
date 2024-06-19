#include <math.h>
#include "cec17_test_func.cpp"
#include <iostream>
#include <time.h>
#include <fstream>
#include <random>

using namespace std;
void cec17_test_func(double *, double *,int,int,int);
double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;
int GNVars;
int MaxFEval = 0;
double fopt[1];

int main()
{
    ofstream fout_t("time_complexity_slow.txt");
    //ofstream foutvals("vals_slow.txt");
    double* xopt;
    for(int i=0;i!=4;i++)
    {
        if(i == 0)
            GNVars = 10;
        if(i == 1)
            GNVars = 30;
        if(i == 2)
            GNVars = 50;
        if(i == 3)
            GNVars = 100;
        cout<<"D = "<<GNVars<<endl;
        //fout_t<<"D = "<<GNVars<<endl;
        xopt = new double[GNVars];
        unsigned t0=clock(),t1;            
        for(int func=1;func<=30;func++)
        {
            MaxFEval = 100000;
            t0=clock();                
            for(int j=0;j!=MaxFEval;j++)
            {                    
                for(int k=0;k!=GNVars;k++)                    
                    xopt[k] = double(rand())/double(RAND_MAX)*200.0-100.0;                    
                cec17_test_func(xopt, fopt, GNVars, 1, func);
                //foutvals<<fopt[0]<<endl;
            }
            t1=clock()-t0;
            cout<<func<<"\t"<<t1<<endl;
            fout_t<<func<<"\t"<<t1<<endl;
        }
        delete xopt;
    }    
	return 0;
}
