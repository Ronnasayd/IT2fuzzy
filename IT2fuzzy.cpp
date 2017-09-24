#include "Rules.cpp"

class IT2fuzzy{
public:int qtdIN;
public:int qtdOUT;
Rules * ptr;
public:double initial_value;
public:double final_value;


public:IT2fuzzy(Rules *pt,int in, int out,double init, double fin){
    this->ptr = pt;
    this->qtdIN = in;
    this->qtdOUT = out;
    this->initial_value = init;
    this->final_value = fin;
}

};
