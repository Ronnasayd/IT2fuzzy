#include "IO.cpp"
#include<iostream>



class IT2fuzzy{
public:int qtdPoints;
Rules * ptr;
IT2inputs * inputs;
IT2outputs * outputs;



public:IT2fuzzy(Rules *pt, IT2inputs * inp, IT2outputs * outs, int points){
    this->ptr = pt;
    this->qtdPoints = points;
    this->inputs = inp;
    this->outputs = outs;


}

public:void fuzzyfy(float val,...){

std::vector<double> valores;
va_list lt;
va_start(lt,val);
float aux = val;
valores.push_back(aux);
for(unsigned int i = 0 ; i < this->inputs->finputs.size()-1;i++){
    aux = va_arg(lt,double);
    valores.push_back(aux);
}
va_end(lt);
for(unsigned int i = 0; i < this->inputs->finputs.size(); i++){
    for(unsigned int j = 0; j < this->inputs->finputs[i]->memberships.size(); j++)
    {
        this->inputs->finputs[i]->memberships[j]->setIternalPertinence(valores[i]);
    }
}
}


};
