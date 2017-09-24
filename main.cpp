#include <iostream>
#include "IT2fuzzy.cpp"
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>


using namespace std;

int main()
{
membership baixolowerI = membership(0.0,2.5,2.5,5.0,0.0,1.0,1.0,0.0);
membership baixoupperI = membership(0.0,2.3,2.5,5.0,0.0,1.0,1.0,0.0);
I2membership baixoI = I2membership(&baixolowerI,&baixoupperI,INPUT,1);

membership baixolowerO = membership(0.0,2.5,2.5,5.0,0.0,1.0,1.0,0.0);
membership baixoupperO = membership(0.0,2.3,2.5,5.0,0.0,1.0,1.0,0.0);
I2membership baixoO = I2membership(&baixolowerO,&baixoupperO,OUTPUT,1);


Rule r1 = Rule(&baixoI,&baixoO,NULL);
Rule r2 = Rule(&baixoO,&baixoI,NULL);
Rules rules = Rules(&r1,&r2,NULL);
IT2fuzzy fuzzy = IT2fuzzy(&rules,1,1,0.0,1000.0);

baixoI.setIternalPertinence(2.1);
cout<<baixolowerI.pert<<endl;
cout<<baixoI.lower->pert<<endl;
cout<<r1.r_input[0]->lower->pert<<endl;
cout<<rules.rules[0]->r_input[0]->lower->pert<<endl;
cout<<fuzzy.ptr->rules[0]->r_input[0]->lower->pert<<endl;





    return 0;
}
